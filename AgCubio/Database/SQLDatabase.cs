using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;

namespace AgCubio
{
    /// <summary>
    /// SQL Database class to connect with Database
    /// </summary>
    public static class SQLDatabase
    {
        /// <summary>
        ///Connection Information
        /// </summary>
        public const string ConnectionString = "server=atr.eng.utah.edu;database=cs3500_schacher;uid=cs3500_schacher;password='PSWRD'";

        /// <summary>
        /// Updateding player info to database
        /// </summary>
        /// <param name="playerCube"></param>
        public static void AddPlayerToDatabase(Cube playerCube)
        {
            using (MySqlConnection connection = new MySqlConnection(ConnectionString))
            {
                try
                {
                    connection.Open();

                    string PlayerText = "INSERT INTO Players (Name, TimeOfDeath, TimeAlive, MaxMass, EatenCubes, Rank) VALUES (@Name, @TimeOfDeath, @TimeAlive, @MaxMass, @EatenCubes, @Rank)";
                    MySqlCommand PlayerCommand = connection.CreateCommand();
                    PlayerCommand.CommandText = PlayerText;
                    PlayerCommand.Parameters.AddWithValue("@Name", playerCube.Name);
                    PlayerCommand.Parameters.AddWithValue("@TimeOfDeath", playerCube.deathOfCube.ToString());
                    PlayerCommand.Parameters.AddWithValue("@TimeAlive", playerCube.timeAlive.ToString());
                    PlayerCommand.Parameters.AddWithValue("@MaxMass", playerCube.maxMass);
                    PlayerCommand.Parameters.AddWithValue("@EatenCubes", playerCube.countOfEatenCubes);
                    PlayerCommand.Parameters.AddWithValue("@Rank", playerCube.highestRank);

                    PlayerCommand.ExecuteNonQuery();

                    //adding to eaten names table
                    if (playerCube.namesOfEatenPlayers.Count > 0)
                    {
                        int newPlayerID = GetIDFromTable(playerCube, connection);

                        string EatenText = "INSERT INTO EatenNames (ID, Names) VALUES (@ID, @Names)";

                        HashSet<string> HashEatenNames = new HashSet<string>(playerCube.namesOfEatenPlayers) { };

                        foreach (string name in HashEatenNames)
                        {
                            MySqlCommand EatenCommand = connection.CreateCommand();
                            EatenCommand.CommandText = EatenText;
                            EatenCommand.Parameters.AddWithValue("@ID", newPlayerID);
                            EatenCommand.Parameters.AddWithValue("@Names", name);
                            EatenCommand.ExecuteNonQuery();
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }

        /// <summary>
        /// gGets Players ID from players Name
        /// </summary>
        /// <param name="playerCube"></param>
        /// <param name="connection"></param>
        /// <returns></returns>
        private static int GetIDFromTable(Cube playerCube, MySqlConnection connection)
        {
            string StringPlayerID;
            int PlayerID = -1;

            //Getting ID for Player
            string PlayerReadText = "SELECT ID FROM Players WHERE Name = @Name"; 
            MySqlCommand PlayerReadCommand = connection.CreateCommand();
            PlayerReadCommand.CommandText = PlayerReadText;
            PlayerReadCommand.Parameters.AddWithValue("@Name", playerCube.Name);

            // Execute the command and cycle through the DataReader object
            using (MySqlDataReader reader = PlayerReadCommand.ExecuteReader())
            {
                while (reader.Read())
                {
                    StringPlayerID = reader["ID"].ToString();
                    bool ConvertID = int.TryParse(StringPlayerID, out PlayerID);
                }
            }
            return PlayerID;
        }

        /// <summary>
        /// Reading info from the player table 
        /// </summary>
        /// <param name="commandText"></param>
        /// <returns></returns>
        public static string ReadFromDatabase(string commandText)
        {
            StringBuilder sb = new StringBuilder();

 
            sb.Append("<!DOCTYPE html> " +
                "<html>" +
                   "<head>" +
                       "<title>AgCubio Scores</title>" +
                             "<style>body{color: blue}" +
                              ".gameScores td{ border: 1px solid black; padding: 5px; text - align:center}" +
                              ".header{ font-weight: 900; font-size: 20px}</style>" +
                   "</head>" +
                   "<body>" +
                      "<h1> AgCubio Score Board</h1>" +
                      "<h4 ><a href = \"http://localhost:11100/players \">  Main Page</a></h4>" +
                           "<table class = gameScores>" +
                              "<tr class =\"header\">" +
                                 "<td>ID</td>" +
                                 "<td>Name</td>" +
                                 "<td>Time Of Death</td>" +
                                 "<td>Time Alive</td>" +
                                 "<td>Max Mass</td>" +
                                 "<td>Eaten Cubes</td>" +
                                 "<td>Rank</td></tr>");

            using (MySqlConnection Connection = new MySqlConnection(ConnectionString))
            {
                try
                {
                    Connection.Open();

                    MySqlCommand command = Connection.CreateCommand();

                    command.CommandText = commandText;

                    using (MySqlDataReader readtable = command.ExecuteReader())
                    {
                        while (readtable.Read())
                        {
                            sb.Append("<tr><td><a href =\"http://localhost:11100/eaten?id=" + readtable["ID"] + "\">").Append(readtable["ID"])
                              .Append("</a></td><td><a href =\"http://localhost:11100/games?player=" + readtable["Name"] + "\">")
                              .Append(readtable["Name"]).Append("</a></td><td>").Append(readtable["TimeOfDeath"]).Append("</td><td>")
                              .Append(readtable["TimeAlive"]).Append("</td><td>").Append(readtable["MaxMass"]).Append("</td><td>")
                              .Append(readtable["EatenCubes"]).Append("</td><td>").Append(readtable["Rank"]).Append("</td></tr>");
                        }

                    }

                    sb.Append("</table></body></html>");

                    return sb.ToString();
                }
                catch (Exception e)
                {
                    return e.ToString();
                }

            }

        }//end of ReadFromDatabase

        /// <summary>
        /// Reading data from both tables
        /// </summary>
        /// <param name="CommandText"></param>
        /// <param name="GameID"></param>
        /// <returns></returns>
        public static string ReadFromEatenNames(string CommandText, int GameID)
        {
            StringBuilder sb = new StringBuilder();

            //making player tables 
            sb.Append("<!DOCTYPE html> " +
                "<html>" +
                   "<head>" +
                       "<title>AgCubio Scores</title>" +
                             "<style>body{color: blue}" +
                              ".gameScores td{ border: 1px solid black; padding: 5px; text - align:center}" +
                              ".header{ font-weight: 900; font-size: 20px}</style>" +
                   "</head>" +
                   "<body>" +
                      "<h1>AgCubio Score Board</h1>" +
                      "<h4 ><a href = \"http://localhost:11100/players \">  Main Page</a></h4>" +
                       "<h3>Player Stats</h3>" +
                           "<table class = gameScores>" +
                              "<tr class =\"header\">" +
                                 "<td>ID</td>" +
                                 "<td>Name</td>" +
                                 "<td>Time Of Death</td>" +
                                 "<td>Time Alive</td>" +
                                 "<td>Max Mass</td>" +
                                 "<td>Eaten Cubes</td>" +
                                 "<td>Rank</td></tr>");


            using (MySqlConnection Connection = new MySqlConnection(ConnectionString))
            {
                try
                {
                    Connection.Open();

                    MySqlCommand PlayerID = Connection.CreateCommand();

                    PlayerID.CommandText = "SELECT * from Players WHERE ID = " + GameID;
                    using (MySqlDataReader readPlayer = PlayerID.ExecuteReader())
                    {
                        while (readPlayer.Read())
                        {
                            sb.Append("<tr><td><a href =\"http://localhost:11100/eaten?id=" + readPlayer["ID"] + "\">").Append(readPlayer["ID"])
                                  .Append("</a></td><td><a href =\"http://localhost:11100/games?player=" + readPlayer["Name"] + "\">")
                                  .Append(readPlayer["Name"]).Append("</a></td><td>").Append(readPlayer["TimeOfDeath"]).Append("</td><td>")
                                  .Append(readPlayer["TimeAlive"]).Append("</td><td>").Append(readPlayer["MaxMass"]).Append("</td><td>")
                                  .Append(readPlayer["EatenCubes"]).Append("</td><td>").Append(readPlayer["Rank"]).Append("</td></tr>");
                        }
                    }
                    sb.Append("</table>");

                    //making eaten players table
                    sb.Append("<h3>Eaten Players</h3>" +
                           "<table class = gameScores>" +
                              "<tr class =\"header\">" +
                                 "<td>Names</td></tr>");

                    MySqlCommand Eatencommand = Connection.CreateCommand();

                    Eatencommand.CommandText = CommandText;


                    using (MySqlDataReader readtable = Eatencommand.ExecuteReader())
                    {
                        while (readtable.Read())
                        {
                            sb.Append("<tr><td>").Append("<a href =\"http://localhost:11100/games?player=" + readtable["Names"] + "\">")
                              .Append(readtable["Names"]).Append("</a></td></tr>");
                        }

                    }

                    sb.Append("</table></body></html>");

                    return sb.ToString();
                }
                catch (Exception e)
                {
                    return e.ToString();
                }

            }
        }

    }
}
