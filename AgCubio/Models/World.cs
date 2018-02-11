using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace AgCubio
{
    /// <summary>
    /// creates the world for the gui
    /// </summary>
    public class World
    {
        //sets the world hieght
        public readonly int WorldHeight = 1000;

        //sets the worlds weight
        public readonly int WorldWidth = 1000;

        //set time to update
        public readonly int Heartbeat = 25;

        //how fast cubes can move when small
        public readonly int TopSpeed = 5;

        //how fast the biggest cubes move
        public readonly int LowSpeed = 1;

        //how fast cubes lose mass
        public readonly int AttritionRate = 200;

        //food mass
        public readonly int FoodValue = 1;

        //starting player mass 

        public readonly int PlayerStartMass = 1000;

        //Amount of food in the world
        public readonly int MaxFood = 5000;

        //Mininmum split mass
        public readonly int MinSplitMass = 100;

        //How much distance to throw splitted cube
        public readonly int MaxSplitDistance = 50;

        //how many times a player can split
        public readonly int MaxSplit = 4;

        //how close cubes have to be in order for the larger to eat the smaller
        public readonly double AbsorbConstant = 1.25;

        //a random generator
        private static Random rand;

        //counter for the Uid
        private int countUid;

        //color counter 
        private int countColor;

        //Amount of virus per world
        public int MaxVirus = 10;

        //color variable
        private Color[] newColors;

        /// <summary>
        /// Declares a dictionary that has the cube.uid be the key and the cube be the value.  
        /// </summary>
        public Dictionary<int, Cube> cubeList;

        /// <summary>
        /// Sets the cubeList to a new dictionary.  
        /// </summary>
        public World()
        {
            cubeList = new Dictionary<int, Cube>();

            rand = new Random();

            countUid = 0;

            countColor = 0;

            newColors = new Color[] { Color.Red, Color.Blue, Color.Purple, Color.Pink, Color.Orange, Color.Black };
        }

        /// <summary>
        /// helper method that creates food to pupolate the world
        /// </summary>
        //public void CreateFood(int foodCount, int VirusCount)
        public Cube CreateFood()
        {
            Cube cube = new Cube();

            cube.team_id = 0;

            cube.uid = countUid++;

            cube.loc_x = rand.Next(0, WorldWidth);

            cube.loc_y = rand.Next(0, WorldHeight);

            cube.argb_color = ChooseColor();

            cube.Name = "";

            cube.Mass = 1;

            cube.food = true;

            cube.IsVirus = false;

            return cube; 
        }

        /// <summary>
        ///  Random color generator helper method
        /// </summary>
        /// <returns></returns>
        public int ChooseColor()
        {
            if (countColor == newColors.Length)
            {
                countColor = 0; 
            }
            int color = newColors[countColor].ToArgb();
            countColor++;           
            return color;
        }

        /// <summary>
        /// creates a player
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public Cube CreatePlayer(string name)
        {
            Cube cube = new Cube();

            cube.team_id = 0;

            cube.uid = countUid++;

            cube.loc_x = rand.Next(0, WorldWidth);

            cube.loc_y = rand.Next(0, WorldHeight);

            cube.Name = name;

            cube.argb_color = ChooseColor();

            cube.Mass = PlayerStartMass;

            cube.food = false;

            cube.IsVirus = false;

            cube.startOfCube = DateTime.Now;

            cube.maxMass = cube.Mass;

            cube.countOfEatenCubes = 0;

            cube.namesOfEatenPlayers = new List<string>();

            cube.highestRank = 0; 

            return cube;
        }

        /// <summary>
        /// creates viruses
        /// </summary>
        /// <returns></returns>
        public Cube CreateVirus()
        {
            Cube virus = new Cube();

            virus.uid = countUid++;

            virus.loc_x = rand.Next(0, WorldWidth);

            virus.loc_y = rand.Next(0, WorldHeight);

            virus.Mass = 200;

            virus.food = false;

            virus.IsVirus = true;

            virus.argb_color = Color.Green.ToArgb();

            virus.Name = ""; 

            return virus;
        }

        /// <summary>
        /// split cube helper method
        /// </summary>
        /// <param name="player"></param>
        /// <returns></returns>
        public Cube Split(Cube player)
        {
            Cube cube = new Cube();

            cube.team_id = player.team_id;

            cube.uid = countUid++;

            cube.loc_x =player.loc_x;

            cube.loc_y = player.loc_y;

            cube.Name = player.Name;

            cube.argb_color = player.argb_color;

            cube.Mass = player.Mass;

            cube.food = false;

            cube.IsVirus = false;

            cube.trackCube = DateTime.Now;

            player.trackCube = DateTime.Now;

            //added new stats 
            cube.startOfCube = DateTime.Now;

            cube.maxMass = cube.Mass;

            cube.countOfEatenCubes = 0;

            cube.namesOfEatenPlayers = new List<string>();

            cube.highestRank = player.highestRank;

            return cube;
        }
    }
}
