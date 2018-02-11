using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;
using AgCubio;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using MySql.Data.MySqlClient;

namespace NetworkTesting
{
    [TestClass]
    public class NetworkTesting
    {
        /// <summary>
        /// Tests to make sure deserialization works.  
        /// </summary>
        [TestMethod]
        public void JasonDeserialization1()
        {
            Cube cube = new Cube();

            string message = "{\"loc_x\":427.0,\"loc_y\":147.0,\"argb_color\":-13245842,\"uid\":5863,\"team_id\":0,\"food\":true,\"Name\":\"\",\"Mass\":1.0}";
            cube = JsonConvert.DeserializeObject<Cube>(message);
            Assert.AreEqual(cube.loc_x, 427.0);
        }

        /// <summary>
        /// Same as above.  
        /// </summary>
        [TestMethod]
        public void JasonDeserialization2()
        {
            Cube cube = new Cube();

            string message = "{\"loc_x\":427.0,\"loc_y\":147.0,\"argb_color\":-13245842,\"uid\":5863,\"team_id\":0,\"food\":true,\"Name\":\"\",\"Mass\":1.0}";
            cube = JsonConvert.DeserializeObject<Cube>(message);
            Assert.AreEqual(cube.loc_y, 147.0);
        }

        /// <summary>
        /// Tests to make sure that it will register that the color is different. 
        /// </summary>
        [TestMethod]
        public void colorTest()
        {
            Cube cube = new Cube();

            string message = "{\"loc_x\":427.0,\"loc_y\":147.0,\"argb_color\":-13245842,\"uid\":5863,\"team_id\":0,\"food\":true,\"Name\":\"\",\"Mass\":1.0}";
            cube = JsonConvert.DeserializeObject<Cube>(message);
            Assert.AreNotEqual(cube.argb_color, "Blue");
        }

        /// <summary>
        /// See if it will add a cube to the world list.  
        /// </summary>
        [TestMethod]
        public void WorldTest()
        {
            World world = new World();
            Cube cube = new Cube();

            string message = "{\"loc_x\":427.0,\"loc_y\":147.0,\"argb_color\":-13245842,\"uid\":5863,\"team_id\":0,\"food\":true,\"Name\":\"\",\"Mass\":1.0}";
            cube = JsonConvert.DeserializeObject<Cube>(message);
            world.cubeList.Add(cube.uid, cube);

            Assert.AreEqual(world.cubeList[cube.uid], cube);
            Assert.AreEqual(world.cubeList[5863].Name, world.cubeList[cube.uid].Name);


        }

        /// <summary>
        /// Test to make sure it will register if a cube is not equal.  
        /// </summary>
        [TestMethod]
        public void worldTest()
        {
            World world = new World();
            Cube cube = new Cube();

            string message = "{\"loc_x\":427.0,\"loc_y\":147.0,\"argb_color\":-13245842,\"uid\":5863,\"team_id\":0,\"food\":true,\"Name\":\"\",\"Mass\":1.0}";
            cube = JsonConvert.DeserializeObject<Cube>(message);
            world.cubeList.Add(cube.uid, cube);

            Assert.AreNotEqual(4543, cube.uid);


        }

        /// <summary>
        /// Tests to see if we can remove a cube from the world list.  
        /// </summary>
        [TestMethod]
        public void RemoveTest()
        {
            World world = new World();
            Cube cube = new Cube();

            Cube cube2 = new Cube();

            string message = "{\"loc_x\":427.0,\"loc_y\":147.0,\"argb_color\":-13245842,\"uid\":5863,\"team_id\":0,\"food\":true,\"Name\":\"\",\"Mass\":1.0}";
            string message2 = "{\"loc_x\":345.0,\"loc_y\":456.0,\"argb_color\":-13245842,\"uid\":4564,\"team_id\":0,\"food\":false,\"Name\":\"Faith\",\"Mass\":30}";
            cube = JsonConvert.DeserializeObject<Cube>(message);
            cube2 = JsonConvert.DeserializeObject<Cube>(message2);


            world.cubeList.Add(cube.uid, cube);
            world.cubeList.Add(cube2.uid, cube2);

            world.cubeList.Remove(cube.uid);

            Assert.AreEqual(world.cubeList.Count, 1);


        }

        /// <summary>
        /// Test to see if we can replace a cube in the dictionary.  
        /// </summary>
        [TestMethod]
        public void ReplaceTest()
        {
            World world = new World();
            Cube cube = new Cube();

            Cube cube2 = new Cube();

            string message = "{\"loc_x\":427.0,\"loc_y\":147.0,\"argb_color\":-13245842,\"uid\":5863,\"team_id\":0,\"food\":true,\"Name\":\"\",\"Mass\":1.0}";
            string message2 = "{\"loc_x\":345.0,\"loc_y\":456.0,\"argb_color\":-13245842,\"uid\":4564,\"team_id\":0,\"food\":false,\"Name\":\"Faith\",\"Mass\":30}";
            cube = JsonConvert.DeserializeObject<Cube>(message);
            cube2 = JsonConvert.DeserializeObject<Cube>(message2);


            world.cubeList.Add(cube.uid, cube);
            world.cubeList.Add(cube2.uid, cube2);

            world.cubeList[cube.uid] = cube2;

            Assert.AreEqual(world.cubeList[cube.uid].loc_y, cube2.loc_y);


        }


        /// <summary>
        ///Ensuring the the cube class creates cubes according to constructor
        /// </summary>
        [TestMethod]

        public void TestCube()
        {

            World world = new World();

            Cube cubes = new Cube(012, 001, 12.5, 140, -4564656, "", 1, true, false);

            Assert.AreEqual(001, cubes.uid);
            Assert.AreNotEqual(4546546, cubes.argb_color);
        }


        /// <summary>
        /// testing the world class
        /// </summary>
        [TestMethod]

        public void TestWorld()
        {

            World world = new World();

            Cube cubes = new Cube(012, 001, 12.5, 140, -4564656, "", 1, true, false);
            world.cubeList.Add(cubes.uid, cubes);

            Assert.AreEqual(001, cubes.uid);
        }

        ManualResetEvent mre1 = new ManualResetEvent(false);

        /// <summary>
        /// testing the network class 
        /// </summary>
        [TestMethod]
        public void TestNetwork()
        {
            Server server = new AgCubio.Server();

            TcpClient client = new TcpClient("localhost", 11000);
            NetworkingCode.Send(client.Client, "Fancy\n");

            byte[] buffer = new byte[1024];
            client.GetStream().BeginRead(buffer, 0, 1024, AssertionCallback, new Tuple<byte[], TcpClient>(buffer, client));
            if (mre1.WaitOne(10000))
                Assert.Fail();

        }
        /// <summary>
        /// assertion class for the network testing class
        /// </summary>
        /// <param name="ar"></param>
        private void AssertionCallback(IAsyncResult ar)
        {

            System.Text.UTF8Encoding encode = new System.Text.UTF8Encoding();
            Tuple<byte[], TcpClient> state = ar.AsyncState as Tuple<byte[], TcpClient>;
            int nbytes = state.Item2.GetStream().EndRead(ar);
            // convert "nbytes" bytes from the buffer into a string
            string bytes = nbytes.ToString();

            // if statement: about that string
            //if the string matches what you expect:
            if (bytes == "Fancy")
            {
                mre1.Set();
            }
            // do nothing, let the TestNetwork thread call Assert.Fail
            else { }
        }

        /// <summary>
        /// Testing the create food method
        /// </summary>
        //[TestMethod]
        //public void CreateFood()
        //{
        //    World w = new World();
        //    int foodcount = 0;
        //    int virus = 0;

        //    world.CreateFood(foodcount, virus);

        //    Assert.AreEqual(5010, w.cubeList.Values.Count);
        //    Assert.AreNotEqual(0, w.cubeList.Count);

        //}

        /// <summary>
        ///Testing the create new player helper methos
        /// </summary>
        [TestMethod]
        public void CreatePlayer()
        {
            World w = new World();
            
            string Player1 = "Lee";

            w.CreatePlayer(Player1);

            foreach (Cube c in w.cubeList.Values)
            {
                Assert.AreEqual("", c.Name);
            }

        }

        [TestMethod]
        public void AddToDabase()
        {
            string ConnectionString = "server=atr.eng.utah.edu;database=cs3500_schacher;uid=cs3500_schacher;password='PSWRD'";

          
            Cube cube = new Cube(2, 4455, 454,778, 9879879, "Joe", 4854, false, false);
            cube.maxMass = 654656;
            cube.startOfCube = DateTime.Now;
            cube.deathOfCube = DateTime.Now;
            cube.timeAlive = cube.deathOfCube - cube.startOfCube;
            cube.countOfEatenCubes = 5;
            cube.highestRank = 5;


            using (MySqlConnection connect = new MySqlConnection(ConnectionString))
            {
                try
                {

                    connect.Open();
                    SQLDatabase.AddPlayerToDatabase(cube);
                    string PlayerReadText = "SELECT ID FROM Players WHERE Name = @Name";
                    MySqlCommand PlayerReadCommand = connect.CreateCommand();
                    PlayerReadCommand.CommandText = PlayerReadText;
                    PlayerReadCommand.Parameters.AddWithValue("@Name", cube.Name);

                    string Maxmass = "";

                    using (MySqlDataReader read = PlayerReadCommand.ExecuteReader())
                    {
                        Maxmass = read["MaxMass"].ToString();

                    }
                    Assert.AreEqual("654656", Maxmass);
                }
                catch
                {

                }
            }
        }


        [TestMethod]
        public void AddToDabase1()
        {
            string ConnectionString = "server=atr.eng.utah.edu;database=cs3500_schacher;uid=cs3500_schacher;password='PSWRD'";


            Cube cube = new Cube(2, 4455, 454, 778, 9879879, "Joe", 4854, false, false);
            cube.maxMass = 654656;
            cube.startOfCube = DateTime.Now;
            cube.deathOfCube = DateTime.Now;
            cube.timeAlive = cube.deathOfCube - cube.startOfCube;
            cube.countOfEatenCubes = 5;
            cube.highestRank = 5;


            using (MySqlConnection connect = new MySqlConnection(ConnectionString))
            {
                try
                {

                    connect.Open();
                    SQLDatabase.AddPlayerToDatabase(cube);
                    string PlayerReadText = "SELECT ID FROM Players WHERE Name = @Name";
                    MySqlCommand PlayerReadCommand = connect.CreateCommand();
                    PlayerReadCommand.CommandText = PlayerReadText;
                    PlayerReadCommand.Parameters.AddWithValue("@Name", cube.Name);

                    string HighestRank = "";

                    using (MySqlDataReader read = PlayerReadCommand.ExecuteReader())
                    {
                        HighestRank = read["Rank"].ToString();

                    }
                    Assert.AreEqual("5", HighestRank);
                }
                catch
                {

                }
            }
        }

        [TestMethod]
        public void AddToDabase2()
        {
            string ConnectionString = "server=atr.eng.utah.edu;database=cs3500_schacher;uid=cs3500_schacher;password='PSWRD'";


            Cube cube = new Cube(2, 4455, 454, 778, 9879879, "Joe", 4854, false, false);
            cube.maxMass = 654656;
            cube.startOfCube = DateTime.Now;
            cube.deathOfCube = DateTime.Now;
            cube.timeAlive = cube.deathOfCube - cube.startOfCube;
            cube.countOfEatenCubes = 5;
            cube.highestRank = 5;


            using (MySqlConnection connect = new MySqlConnection(ConnectionString))
            {
                try
                {

                    connect.Open();
                    SQLDatabase.AddPlayerToDatabase(cube);
                    string PlayerReadText = "SELECT ID FROM Players WHERE Name = @Name";
                    MySqlCommand PlayerReadCommand = connect.CreateCommand();
                    PlayerReadCommand.CommandText = PlayerReadText;
                    PlayerReadCommand.Parameters.AddWithValue("@Name", cube.Name);

                    string Name = "";

                    using (MySqlDataReader read = PlayerReadCommand.ExecuteReader())
                    {
                        Name = read["Name"].ToString();

                    }
                    Assert.AreEqual("Joe", Name);
                }
                catch
                {

                }
            }
        }

    }

}
