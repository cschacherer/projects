using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Drawing;
using Newtonsoft.Json;

namespace AgCubio
{
    /// <summary>
    /// Cube class that will hold info from the server.  
    /// </summary>
    [JsonObject(MemberSerialization.OptIn)]
    public class Cube
    {
        [JsonProperty]
        public int team_id;

        [JsonProperty]
        public int uid;

        [JsonProperty]
        public double loc_x;

        [JsonProperty]
        public double loc_y;

        [JsonProperty]
        public int argb_color;

        [JsonProperty]
        public string Name;

        [JsonProperty]
        public double Mass;

        [JsonProperty]
        public bool food;

        public bool IsVirus;

        public DateTime trackCube;
        
        //will record when player became alive so we know how long it was alive for stats
        public DateTime startOfCube;

        //will record when player died for stats
        public DateTime deathOfCube;

        public TimeSpan timeAlive; 

        //will hold the biggest size of the player for stats 
        public double maxMass;

        //will hold number of cubes the player ate
        public int countOfEatenCubes;

        //will hold names of players the player ate
        public List<string> namesOfEatenPlayers;

        //will hold the highest rank the player achieved while they were alive
        public int highestRank; 

        public double Width
        {
            get { return Math.Pow(Mass, 0.65); } 
            private set { Mass = value * value; }
        }

        /// <summary>
        /// Contructor that constructs a cube.  
        /// </summary>
        [JsonConstructor]
        public Cube()
        {

        }

        public Cube(int TeamID, int UID, double LocX, double LocY, 
            int Color, string name, double mass, bool Food, bool Virus)
        {
            team_id = TeamID;
            uid = UID;
            loc_x = LocX;
            loc_y = LocY;
            argb_color = Color;
            Name = name;
            Mass = mass;
            food = Food;
            IsVirus = Virus;

        }

    }


}
