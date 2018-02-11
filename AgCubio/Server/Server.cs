using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using System.Timers;
using Newtonsoft.Json;
using System.Windows;
using System.Drawing;

namespace AgCubio
{
    public class Server
    {
        //World instance
        private World world;

        //Dicitonary to keep track of sockects and the players
        private Dictionary<Socket, Cube> AllSockets;

        //timer to update world
        private Timer timer;

        //all players dictionary
        private Dictionary<int, Cube> PlayerDictionary;

        //splitted cubes dictionary
        private Dictionary<int, HashSet<Cube>> SplitDictionary;

        //food counter
        private int foodCount;

        //virus counter 
        private int VirusCount;

        //teamid counter
        private int TeamIDCount = 0;

        //split counter
        private int splitCount = 0;

        //storing the X location of the mouse
        private double mouseLocX;

        //storing the Y location of the mouse
        private double mouseLocY;

        private Dictionary<int, Cube> HighestRanks;

        /// <summary>
        /// A server constructor
        /// </summary>
        public Server()
        {

            Start();
        }

        /// <summary>
        /// starts the world
        /// </summary>
        private void Start()
        {
            world = new World();
            PlayerDictionary = new Dictionary<int, Cube>();
            AllSockets = new Dictionary<Socket, Cube>();
            SplitDictionary = new Dictionary<int, HashSet<Cube>>();
            HighestRanks = new Dictionary<int, Cube>();

            foodCount = 0;
            VirusCount = 0;

            world = new World();
            timer = new Timer();
            //(1 second/25 heartbeats) * 1000 = 40 miliseconds
            timer.Interval = (double)(1.0 / world.Heartbeat * 1000);
            //the heartbeats of the world new timer and set seconds to update
            timer.Elapsed += Timer_Elapsed;

            lock (world)
            {
                if (foodCount < world.MaxFood)
                {
                    for (int i = foodCount; i < world.MaxFood; i++)
                    {
                        Cube food = world.CreateFood();
                        world.cubeList.Add(food.uid, food);
                    }
                }
                if (VirusCount < world.MaxVirus)
                {
                    for (int i = VirusCount; i < world.MaxVirus; i++)
                    {
                        Cube virus = world.CreateVirus();
                        world.cubeList.Add(virus.uid, virus);
                    }
                }
            }
            foodCount = world.MaxFood;
            VirusCount = world.MaxVirus;

            timer.Start();

            //Awaiting Network client connections
            NetworkingCode.Server_Awaiting_Client_Loop(Handle_New_Client_Connections, 11000);
            NetworkingCode.Server_Awaiting_Client_Loop(Web_Browser_Connection, 11100);


        }

        /// <summary>
        /// timer event to keep track of the time for each updates
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Update();
        }

        /// <summary>
        /// this handles every client connections
        /// </summary>
        /// <param name="state"></param>
        public void Handle_New_Client_Connections(PreservedState state)
        {
            //set up a message to let us know that a client has connected to the server 
            Console.WriteLine("A new client has connected to the server.");

            //set up a callback to recieve the player name
            state.State_Callback = Recieve_Player_Name;

            //Request more data
            NetworkingCode.i_want_more_data(state);
        }

        /// <summary>
        /// sends out the player name after the first contact
        /// </summary>
        /// <param name="state"></param>
        public void Recieve_Player_Name(PreservedState state)
        {
            if (NetworkingCode.IsConnected(state.State_Socket))
            {
                //recieve player name from view
                string stringData = state.data.ToString();
                int EndName = stringData.IndexOf('\n');
                string name = stringData.Substring(0, EndName);
                state.data.Remove(0, EndName + 1);

                //create player cube and send to client
                Cube PlayerCube = world.CreatePlayer(name);

                //change callback
                state.State_Callback = Handle_Data_from_Client;

                lock (world)
                {
                    //Add to world and player dictionary
                    world.cubeList.Add(PlayerCube.uid, PlayerCube);
                    PlayerDictionary.Add(PlayerCube.uid, PlayerCube);

                    //adds the socket and the socket's player to a dictionary to keep track of the player for each socket 
                    AllSockets.Add(state.State_Socket, PlayerCube);

                    //Seriliaze player cube
                    string message = JsonConvert.SerializeObject(PlayerCube);
                    NetworkingCode.Send(state.State_Socket, message + "\n");

                    //update World
                    UpdateWorld();
                }
                //starts the timer for the server to begin Updating 
                //timer.Start();

                //ask for more data 
                NetworkingCode.i_want_more_data(state);
            }
            else
            {
                lock (world)
                {
                    AllSockets.Remove(state.State_Socket);
                    if (AllSockets.Count == 0)
                    {
                        //Awaiting Network client connections
                        Start();
                    }
                }
            }

        }

        /// <summary>
        /// Handles every request from the client
        /// </summary>
        /// <param name="state"></param>
        public void Handle_Data_from_Client(PreservedState state)
        {
            if (NetworkingCode.IsConnected(state.State_Socket))
            {
                int MessageEnd;
                lock (world)
                {
                    //getting message from the client and desecting the message to respond accordingly
                    while ((MessageEnd = state.data.ToString().IndexOf('\n')) >= 0)
                    {
                        //message recived 
                        string message = state.data.ToString().Substring(0, MessageEnd);
                        state.data.Remove(0, MessageEnd + 1);

                        string[] positionArray = message.Split(' ');

                        string xpos = positionArray[1];
                        string ypos = positionArray[2];

                        //geting mouse location
                        xpos = xpos.Remove(xpos.Length - 1);
                        ypos = ypos.Remove(ypos.Length - 1);

                        double mouse_x;
                        double mouse_y;

                        bool Double_x = double.TryParse(xpos, out mouse_x);
                        bool Double_y = double.TryParse(ypos, out mouse_y);

                        mouseLocX = mouse_x;
                        mouseLocY = mouse_y;

                        Cube Updated_player = AllSockets[state.State_Socket];

                        //handles move requests 
                        if (message.Substring(1, 4) == "move")
                        {
                            //will decrease the speed as the mass gets bigger, speed starts at 50
                            double playerSpeed = 1000 / (Updated_player.Mass * 0.5);
                            //double playerSpeed = 1;

                            if (!(Updated_player.team_id == 0))
                            {
                                foreach (Cube SplitCubes in SplitDictionary[Updated_player.team_id])
                                {
                                    MoveCube(mouse_x, mouse_y, SplitCubes, playerSpeed);
                                }
                            }
                            else
                            {
                                MoveCube(mouse_x, mouse_y, Updated_player, playerSpeed);
                                AllSockets[state.State_Socket] = Updated_player;
                            }
                        }

                        //handling split request
                        else if (message.Substring(1, 5) == "split")
                        {
                            //loop through to see get split 20 times
                            if (splitCount > world.MaxSplit)
                            {
                                splitCount = 0;
                            }
                            else
                            {
                                //splitting and ensuring team id is assigned
                                splitCount++;
                                if ((Updated_player.Mass > world.MinSplitMass) && splitCount <= world.MaxSplit)
                                {
                                    if (Updated_player.team_id == 0)
                                    {
                                        TeamIDCount++;
                                        Updated_player.team_id = TeamIDCount;
                                        Updated_player.Mass = Updated_player.Mass / 2;

                                        Cube SplittedCube = world.Split(Updated_player);
                                        SplitTheCube(mouse_x, mouse_y, SplittedCube);
                                        SplitDictionary.Add(Updated_player.team_id, new HashSet<Cube>() { SplittedCube, Updated_player });
                                    }

                                    //else if player already splitted
                                    else
                                    {
                                        HashSet<Cube> NewSplitCubes = new HashSet<Cube>();
                                        foreach (Cube OldCube in SplitDictionary[Updated_player.team_id])
                                        {
                                            OldCube.Mass = OldCube.Mass / 2;
                                            Cube SplittedCube = world.Split(OldCube);
                                            SplitTheCube(mouse_x, mouse_y, SplittedCube);
                                            NewSplitCubes.Add(SplittedCube);
                                            NewSplitCubes.Add(OldCube);
                                        }
                                        SplitDictionary[Updated_player.team_id] = NewSplitCubes;
                                    }// end else
                                }//end if
                            }//end else
                        }//end if                      
                    }// end while
                } //end lock
                NetworkingCode.i_want_more_data(state);
            }
            else
            {
                //Removes socket from list if no information is coming in 
                lock (world)
                {
                    PlayerDictionary.Remove(AllSockets[state.State_Socket].uid);
                    world.cubeList.Remove(AllSockets[state.State_Socket].uid);
                    if (AllSockets[state.State_Socket].team_id != 0)
                    {
                        SplitDictionary.Remove(AllSockets[state.State_Socket].team_id);
                    }
                    //adding dead player to database 
                    SQLDatabase.AddPlayerToDatabase(AllSockets[state.State_Socket]); 

                    AllSockets.Remove(state.State_Socket);
                    if (AllSockets.Count == 0)
                    {
                        //Awaiting Network client connections
                        NetworkingCode.Server_Awaiting_Client_Loop(Handle_New_Client_Connections, 11000);
                    }
                }
            }
        }

        /// <summary>
        /// helper method for splitting the cubes
        /// </summary>
        /// <param name="mouse_x"></param>
        /// <param name="mouse_y"></param>
        /// <param name="SplittedCube"></param>
        private void SplitTheCube(double mouse_x, double mouse_y, Cube SplittedCube)
        {
            if (mouse_x < SplittedCube.loc_x)
            {
                SplittedCube.loc_x -= world.MaxSplitDistance;
                if (mouse_x > SplittedCube.loc_x)
                {
                    SplittedCube.loc_x = mouse_x;
                }
                if ((SplittedCube.loc_x - SplittedCube.Width / 2) < 0)
                {
                    SplittedCube.loc_x = 0 + SplittedCube.Width / 2;
                }
            }

            else if (mouse_x > SplittedCube.loc_x)
            {
                SplittedCube.loc_x += world.MaxSplitDistance;
                if (mouse_x < SplittedCube.loc_x)
                {
                    SplittedCube.loc_x = mouse_x;
                }
                if ((SplittedCube.loc_x + SplittedCube.Width / 2) > world.WorldWidth)
                {
                    SplittedCube.loc_x = world.WorldWidth - SplittedCube.Width / 2;
                }
            }

            if (mouse_y < SplittedCube.loc_y)
            {
                SplittedCube.loc_y -= world.MaxSplitDistance;

                if (mouse_y > SplittedCube.loc_y)
                {
                    SplittedCube.loc_y = mouse_y;
                }
                if ((SplittedCube.loc_y - SplittedCube.Width / 2) < 0)
                {
                    SplittedCube.loc_y = 0 + SplittedCube.Width / 2;
                }
            }
            else if (mouse_y > SplittedCube.loc_y)
            {
                SplittedCube.loc_y += world.MaxSplitDistance;

                if (mouse_y < SplittedCube.loc_y)
                {
                    SplittedCube.loc_y = mouse_y;
                }
                if ((SplittedCube.loc_y + SplittedCube.Width / 2) > world.WorldHeight)
                {
                    SplittedCube.loc_y = world.WorldHeight + SplittedCube.Width / 2;
                }
            }
        }

        /// <summary>
        /// Helper method to move cube towards the mouse
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="cube"></param>
        /// <param name="speed"></param>
        public void MoveCube(double x, double y, Cube cube, double speed)
        {
            if (x > cube.loc_x)
            {
                cube.loc_x += speed;
                if ((cube.loc_x + (cube.Width / 2)) > world.WorldWidth)
                {
                    cube.loc_x = world.WorldWidth - (cube.Width / 2);
                }
            }
            else if (x < cube.loc_x)
            {
                cube.loc_x -= speed;
                if ((cube.loc_x - (cube.Width / 2)) < 0)
                {
                    cube.loc_x = 0 + cube.Width / 2;
                }
            }
            if (y > cube.loc_y)
            {
                cube.loc_y += speed;
                if ((cube.loc_y + cube.Width / 2) > world.WorldHeight)
                {
                    cube.loc_y = world.WorldHeight - cube.Width / 2;
                }
            }
            else if (y < cube.loc_y)
            {
                cube.loc_y -= speed;
                if ((cube.loc_y - cube.Width / 2) < 0)
                {
                    cube.loc_y = 0 + cube.Width / 2;
                }
            }
            world.cubeList[cube.uid] = cube;
            PlayerDictionary[cube.uid] = cube;
        }

        /// <summary>
        /// Sends all the cubes in the world dictionary to the client 
        /// </summary>
        /// <param name="state"></param>
        //private void UpdateWorld(PreservedState)
        private void UpdateWorld()
        {
            foreach (Cube cube in world.cubeList.Values)
            {
                foreach (Socket socket in AllSockets.Keys)
                {
                    string message = JsonConvert.SerializeObject(cube);
                    NetworkingCode.Send(socket, message + "\n");
                }
            }
        }

        /// <summary>
        /// sending a single cube to update the world of either a player or a dead cube
        /// </summary>
        /// <param name="cube"></param>
        private void SendCube(Cube cube)
        {
            foreach (Socket socket in AllSockets.Keys)
            {
                string message = JsonConvert.SerializeObject(cube);
                NetworkingCode.Send(socket, message + "\n");
            }
        }

        /// <summary>
        /// updates the world on all changes
        /// </summary>
        private void Update()
        {
            List<Cube> eatenCubes = new List<Cube>();

            lock (world)
            {
                if (foodCount < world.MaxFood)
                {
                    for (int i = foodCount; i < world.MaxFood; i++)
                    {
                        Cube food = world.CreateFood();
                        world.cubeList.Add(food.uid, food);
                        foodCount++;
                        SendCube(food);

                    }
                }
                if (VirusCount < world.MaxVirus)
                {
                    for (int i = VirusCount; i < world.MaxVirus; i++)
                    {
                        Cube virus = world.CreateVirus();
                        world.cubeList.Add(virus.uid, virus);
                        VirusCount++;
                        SendCube(virus);

                    }
                }

                foreach (Cube playerCube in PlayerDictionary.Values)
                {
                    double Player_Top = playerCube.loc_y - (playerCube.Width / 2);
                    double Player_Bottom = playerCube.loc_y + (playerCube.Width / 2);
                    double Player_Left = playerCube.loc_x - (playerCube.Width / 2);
                    double Player_Right = playerCube.loc_x + (playerCube.Width / 2);

                    foreach (Cube cube in world.cubeList.Values)
                    {
                        if ((playerCube.uid != cube.uid))
                        {
                            if ((Player_Left < cube.loc_x) && (cube.loc_x < Player_Right) && (Player_Top < cube.loc_y)
                                && (cube.loc_y < Player_Bottom))
                            {
                                //beginning of team split check 
                                if ((playerCube.team_id > 0 && playerCube.team_id == cube.team_id))
                                {
                                    //setting the timer to the current time to check split time
                                    TimeSpan timerLapse = DateTime.Now - playerCube.trackCube;

                                    //if time not up to 5s bounce off each other
                                    if (timerLapse.TotalSeconds < 5)
                                    {
                                        double Cube_Top = cube.loc_y - (cube.Width / 2);
                                        double Cube_Bottom = cube.loc_y + (cube.Width / 2);
                                        double Cube_Left = cube.loc_x - (cube.Width / 2);
                                        double Cube_Right = cube.loc_x + (cube.Width / 2);

                                        if (Cube_Top < Player_Bottom)
                                        {
                                            double result = Player_Bottom - Cube_Top;
                                            cube.loc_y += result;
                                            if (cube.loc_y + (cube.Width / 2) > world.WorldHeight)
                                            {
                                                cube.loc_y = world.WorldHeight - (cube.Width / 2);
                                            }
                                        }

                                        else if (Cube_Bottom > Player_Top)
                                        {
                                            double result = Cube_Bottom - Player_Top;
                                            cube.loc_y -= result;
                                            if (cube.loc_y - (cube.Width / 2) < 0)
                                            {
                                                cube.loc_y = 0 + (cube.Width / 2);
                                            }
                                        }

                                        if (Cube_Right > Player_Left)
                                        {
                                            double result = Cube_Right - Player_Left;
                                            cube.loc_x -= result;
                                            if (cube.loc_x - (cube.Width / 2) < 0)
                                            {
                                                cube.loc_x = 0 + (cube.Width / 2);
                                            }
                                        }

                                        else if (Cube_Left < Player_Right)
                                        {
                                            double result = Player_Right - Cube_Left;
                                            cube.loc_x += result;
                                            if (cube.loc_x + (cube.Width / 2) > world.WorldWidth)
                                            {
                                                cube.loc_x = world.WorldWidth - (cube.Width / 2);
                                            }
                                        }

                                        foreach (Cube s in SplitDictionary[cube.team_id])
                                        {
                                            if (cube.uid == s.uid)
                                            {
                                                s.loc_x = cube.loc_x;
                                                s.loc_y = cube.loc_y;
                                            }
                                        }
                                    }

                                    //merge team cubes after time elapse
                                    else
                                    {
                                        //have to make sure that the 'cube' isn't the main player cube otherwise it will get eaten by one of 
                                        //it's own splits 
                                        if (!AllSockets.Values.Contains(cube))
                                        {
                                            playerCube.Mass += cube.Mass;
                                            cube.Mass = 0;

                                            //checks to see if the merged player cube's mass is greater than it's maxMass and if it is changes it
                                            if (playerCube.Mass > playerCube.maxMass)
                                            {
                                                playerCube.maxMass = playerCube.Mass;
                                            }

                                            //adding splitted cube's stats to player cube's                                        
                                            playerCube.countOfEatenCubes += cube.countOfEatenCubes;

                                            if (cube.namesOfEatenPlayers.Count > 0)
                                            {
                                                foreach (string name in cube.namesOfEatenPlayers)
                                                {
                                                    playerCube.namesOfEatenPlayers.Add(name);
                                                }
                                            }

                                            //trying to fix bug where player will merge together and get bigger than world 
                                            if (playerCube.Width >= world.WorldHeight || playerCube.Width >= world.WorldWidth)
                                            {
                                                playerCube.Mass = Math.Pow(playerCube.Mass, 0.5);
                                            }

                                            SplitDictionary[cube.team_id].Remove(cube);
                                            eatenCubes.Add(cube);

                                            if (SplitDictionary[playerCube.team_id].Count <= 1)
                                            {
                                                SplitDictionary.Remove(playerCube.team_id);
                                                playerCube.team_id = 0;
                                            }
                                            SendCube(cube);
                                        }
                                    }
                                } //end of function if two cubes are on the same team

                                //eating food and viruses
                                else
                                {
                                    if (cube.IsVirus == true)
                                    {
                                        VirusHit(playerCube);
                                        VirusCount--;
                                    }
                                    //eating food and other players and checking to make sure the player doesn't get larger than the world.  
                                    else
                                    {
                                        playerCube.Mass += cube.Mass;
                                        cube.Mass = 0;

                                        //checks to see if player's mass now is greater than it's max mass and if it is, changes it
                                        if (playerCube.Mass > playerCube.maxMass)
                                        {
                                            playerCube.maxMass = playerCube.Mass;
                                        }

                                        //trying to fix bug where the player will grow bigger than the world 
                                        if (playerCube.Width >= world.WorldHeight || playerCube.Width >= world.WorldWidth)
                                        {
                                            playerCube.Mass = Math.Pow(playerCube.Mass, 0.5);
                                        }
                                        //adds dead cube to a list to be taken off of player or world dictionary
                                        eatenCubes.Add(cube);

                                        //adds 1 to count of cubes eaten for the player
                                        playerCube.countOfEatenCubes++;

                                        //adds name of eaten player to player's playersEaten list.  
                                        if (cube.food != true)
                                        {
                                            playerCube.namesOfEatenPlayers.Add(cube.Name);
                                            cube.deathOfCube = DateTime.Now;
                                            cube.timeAlive = cube.deathOfCube - cube.startOfCube;

                                            //send dead cube to database now? 
                                        }
                                        SendCube(cube);
                                    }
                                }
                            }
                        }
                    } //end of going through world with player

                    //handles Attrition
                    if (playerCube.Mass > world.AttritionRate)
                    {
                        //double n = Math.Pow(playerCube.Mass, 1.2) / 10000;
                        double n = Math.Pow(playerCube.Mass, 1.3) / 10000; //Gets rid of more mass to prevent huge cubes that swallow up the world.  
                        playerCube.Mass = playerCube.Mass - n;
                    }

                    //Sends player cube to all sockets 
                    SendCube(playerCube);
                } //end of going through playerDictionary


                //for splitted cubes to help with ranking 
                int splittedCubesTeamID;
                double totalMassOfPlayer;

                //hasSet stores splitted cubes and update world
                foreach (HashSet<Cube> cubeHashSet in SplitDictionary.Values)
                {
                    totalMassOfPlayer = 0;
                    splittedCubesTeamID = 0;

                    foreach (Cube splittedCube in cubeHashSet)
                    {
                        splittedCubesTeamID = splittedCube.team_id; //keeps track of what team id we are on 

                        double splittedCube_Top = splittedCube.loc_y - (splittedCube.Width / 2);
                        double splittedCube_Bottom = splittedCube.loc_y + (splittedCube.Width / 2);
                        double splittedCube_Left = splittedCube.loc_x - (splittedCube.Width / 2);
                        double splittedCube_Right = splittedCube.loc_x + (splittedCube.Width / 2);

                        foreach (Cube cube in world.cubeList.Values)
                        {
                            if ((splittedCube_Left < cube.loc_x) && (cube.loc_x < splittedCube_Right) &&
                                (splittedCube_Top < cube.loc_y) && (cube.loc_y < splittedCube_Bottom))
                            {
                                if (splittedCube.team_id != cube.team_id)
                                {
                                    splittedCube.Mass += cube.Mass;
                                    cube.Mass = 0;

                                    //checks to see if splitted cube's mass is greater than it's maxMass and update maxMass if it is. 
                                    if (splittedCube.Mass > splittedCube.maxMass)
                                    {
                                        splittedCube.maxMass = splittedCube.Mass;
                                    }

                                    //updates count of food eated
                                    splittedCube.countOfEatenCubes++;

                                    //adds dead cube to list to be taken out of world and/or player list
                                    eatenCubes.Add(cube);

                                    //player has eaten another player
                                    if (cube.IsVirus != true && cube.Name != string.Empty)
                                    {
                                        splittedCube.namesOfEatenPlayers.Add(cube.Name);
                                        cube.deathOfCube = DateTime.Now;
                                        cube.timeAlive = cube.deathOfCube - cube.startOfCube;

                                        //send cube to database now? 
                                    }
                                    SendCube(cube);
                                }
                            }

                        }
                        SendCube(splittedCube);
                        //keeps track of players total mass; 
                        totalMassOfPlayer += splittedCube.Mass;
                    }
                    //sets maxMass of player if player is split up 
                    foreach (Cube player in AllSockets.Values)
                    {
                        if (splittedCubesTeamID == player.team_id)
                        {
                            if (totalMassOfPlayer > player.maxMass)
                            {
                                player.maxMass = totalMassOfPlayer;

                                //updates other list with players new max mass value
                                world.cubeList[player.uid].maxMass = player.maxMass;
                                PlayerDictionary[player.uid].maxMass = player.maxMass;
                            }
                        }
                    }
                }

                //goes through high list ranking 
                if (AllSockets.Count >= 1)
                {
                    List<Cube> playerMaxMassList = new List<Cube>();
                    foreach (Cube player in AllSockets.Values)
                    {
                        playerMaxMassList.Add(player);
                    }
                    if (playerMaxMassList.Count == 1)
                    {
                        //HighestRanks = new Dictionary<int, Cube>(); 
                        HighestRanks[1] = playerMaxMassList[0];

                        world.cubeList[playerMaxMassList[0].uid].highestRank = 1;
                        PlayerDictionary[playerMaxMassList[0].uid].highestRank = 1;

                    }
                    else
                    {
                        //sorts cubes by thier maxMass 
                        playerMaxMassList.Sort(delegate (Cube x, Cube y)
                        {
                            return x.maxMass.CompareTo(y.maxMass);
                        });
                        //if list is less than 5, sets number of times it will add a person to the high rank 
                        int numOfRanks;
                        if (playerMaxMassList.Count >= 5)
                        {
                            numOfRanks = 5;
                        }
                        else
                        {
                            numOfRanks = playerMaxMassList.Count;
                        }
                        //puts highest maxMasses in the high rank dictionary
                        for (int i = 1; i <= numOfRanks; i++)
                        {
                            HighestRanks[i] = playerMaxMassList[i - 1];
                            if (playerMaxMassList[playerMaxMassList.Count - i].highestRank < i)
                            {
                                playerMaxMassList[i - 1].highestRank = i;
                            }
                            if (playerMaxMassList[playerMaxMassList.Count - i].Mass != 0)
                            {
                                world.cubeList[playerMaxMassList[playerMaxMassList.Count - i].uid].highestRank = i;
                                PlayerDictionary[playerMaxMassList[playerMaxMassList.Count - i].uid].highestRank = i;
                            }

                        }
                    }
                }


                //deletes eaten cubes from player dictionary and world list 
                foreach (Cube deadCube in eatenCubes)
                {
                    if (PlayerDictionary.ContainsKey(deadCube.uid))
                    {
                        PlayerDictionary.Remove(deadCube.uid);



                        if (AllSockets.Values.Contains(deadCube))
                        {
                            Socket temp = new Socket(SocketType.Stream, ProtocolType.Tcp);
                            foreach (KeyValuePair<Socket, Cube> playerCube in AllSockets)
                            {
                                if (playerCube.Value.uid == deadCube.uid)
                                {
                                    SendCube(deadCube);

                                    //adding dead player to database 
                                    SQLDatabase.AddPlayerToDatabase(deadCube); 

                                    //Close socket
                                    temp = playerCube.Key;
                                    playerCube.Key.Close();
                                }
                            }
                            AllSockets.Remove(temp);  
                        }
                    }
                    if (world.cubeList.ContainsKey(deadCube.uid))
                    {
                        if (deadCube.food == true)
                        {
                            foodCount--;
                        }
                        world.cubeList.Remove(deadCube.uid);
                    }
                }
            }
        }

        /// <summary>
        /// splits a player if they absorb a virus
        /// </summary>
        /// <param name="Player"></param>
        private void VirusHit(Cube Player)
        {
            if (Player.team_id == 0)
            {
                TeamIDCount++;
                Player.team_id = TeamIDCount;
                Player.Mass = Player.Mass / 2;

                Cube SplittedCube = world.Split(Player);
                SplitTheCube(mouseLocX, mouseLocY, SplittedCube);
                SplitDictionary.Add(Player.team_id, new HashSet<Cube>() { SplittedCube, Player });

                for (int i = 0; i < 2; i++)
                {
                    HashSet<Cube> NewSplitCubes = new HashSet<Cube>();
                    foreach (Cube OldCube in SplitDictionary[Player.team_id])
                    {
                        OldCube.Mass = OldCube.Mass / 2;
                        SplittedCube = world.Split(OldCube);
                        SplitTheCube(mouseLocX, mouseLocY, SplittedCube);
                        NewSplitCubes.Add(SplittedCube);
                        NewSplitCubes.Add(OldCube);
                    }
                    SplitDictionary[Player.team_id] = NewSplitCubes;
                }
            }
        }

        /// <summary>
        ///Creating a first contact with the Web browser
        /// </summary>
        /// <param name="state"></param>
        public void Web_Browser_Connection(PreservedState state)
        {
            state.State_Callback = Stat_Request;
            NetworkingCode.i_want_more_data(state);

        }
        /// <summary>
        ///Process requests from the Web Browser 
        /// </summary>
        /// <param name="state"></param>
        public void Stat_Request(PreservedState state)
        {
            int RequestEnd = state.data.ToString().IndexOf('\n');

            string page = "";

            string message = state.data.ToString().Substring(0, RequestEnd - 1);
            state.data.Remove(0, RequestEnd + 2);

            
            if (message == "GET /players HTTP/1.1")
            {
                string commandText = "SELECT * from Players";
                page = SQLDatabase.ReadFromDatabase(commandText);

            }

            else if (message.Substring(0, 18) == "GET /games?player=")
            {
                string[] GetNameArray = message.Substring(18).Split(' ');

                string name = GetNameArray[0];

                string commandText = "SELECT * FROM Players WHERE Name = '" + name + "'";

                page = SQLDatabase.ReadFromDatabase(commandText);
            }

            else if (message.Substring(0, 14) == "GET /eaten?id=")
            {
                string[] GetNameArray = message.Substring(14).Split(' ');

                string StringGameID = GetNameArray[0];

                int GameID;

                bool BoolGameID =  int.TryParse(StringGameID, out GameID);

                string commandText = "SELECT * FROM EatenNames WHERE ID = " + StringGameID;

                page = SQLDatabase.ReadFromEatenNames(commandText, GameID);

            }

            else
            {
                page = "<!DOCTYPE html><html><title> Error </title><body><h5>Error:</h5><p> Cannot connect to server,"
                    + " check URL</p></body></html> ";
            }
            NetworkingCode.Send(state.State_Socket, page);

        }
        /// <summary>
        /// Runs the server
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            new Server();
            Console.Read();
        }
    }
}
