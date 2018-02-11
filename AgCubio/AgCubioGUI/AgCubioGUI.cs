using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;


namespace AgCubio
{
    /// <summary>
    /// Form that graphically show what the Agcubio Server sends us 
    /// </summary>
    public partial class AgCubioGUI : Form      
    {
        /// <summary>
        /// Declares a world class to hold our cubes 
        /// </summary>
        private World world;

        /// <summary>
        /// Holds our state..
        /// </summary>
        private PreservedState pstate;

        /// <summary>
        /// Declares our scale width to multiply all of our cubes with 
        /// </summary>
        private double scale_width;

        /// <summary>
        /// Declares an object that is the form's player.
        /// </summary>
        private Cube player;

        /// <summary>
        /// Declares a dictionary to hold the team id's 
        /// </summary>
        Dictionary<int, Cube> teamID = new Dictionary<int, Cube>();

        DateTime timer = DateTime.Now;
        double totalTime = 0; 

        /// <summary>
        /// Our constructor initializes everything.  
        /// </summary>
        public AgCubioGUI()
        {
            InitializeComponent();
            world = new World();
            Server_Name.Text = "localhost";
            this.DoubleBuffered = true;
            this.Width =1000;
            this.Height = 600;
            this.Focus();
            //timer.Start(); 
        }

        /// <summary>
        /// Paints all of our cubes and player stats
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AgCubioGUI_Paint(object sender, PaintEventArgs e)
        {

            SendMousePosition();
            int x, y;
            MousePos(out x, out y);
            
            int vp_width = this.Width / 2;
            int vp_height = this.Height / 2;

            int c_width = (int)(this.Width - scale_width * player.Width) / 2;
            int c_height = (int)(this.Height - scale_width * player.Width) / 2;

            lock (world)
            {
                if (player.uid >= 0 && world.cubeList.Count > 0)
                {
                    foreach (KeyValuePair<int, Cube> s in world.cubeList)
                    {
                        Brush mybrush = new SolidBrush(Color.FromArgb(s.Value.argb_color));

                        int s_width = (int)(s.Value.loc_x * scale_width - player.loc_x * scale_width) + vp_width;
                        int s_height = (int)(s.Value.loc_y * scale_width - player.loc_y * scale_width) + vp_height;

                        if (s.Key == player.uid)
                        {
                            e.Graphics.FillRectangle(mybrush, new Rectangle((int)(c_width), (int)(c_height),
                                (int)(player.Width * scale_width), (int)(player.Width * scale_width)));
                        }
                        else
                        {
                            if (s.Value.food == true)
                            {
                                e.Graphics.FillRectangle(mybrush, new Rectangle((int)(s_width), (int)(s_height),
                                (int)(s.Value.Width * scale_width * 3), (int)(s.Value.Width * scale_width * 3)));
                            }
                            else
                            {
                                e.Graphics.FillRectangle(mybrush, new Rectangle((int)(s_width), (int)(s_height),
                                (int)(s.Value.Width * scale_width), (int)(s.Value.Width * scale_width)));
                            }
                            
                        }
                    
                    }                                  
                }
            }

            //Draw name on player
            Point playerPoint = new Point((int)(c_width + ((player.Width * scale_width) / 2) - 13), (int)(c_height + ((player.Width * scale_width) / 2) ));
            e.Graphics.DrawString(player.Name, new Font("Arial", (int)(12)), Brushes.Yellow, playerPoint);

            //Draw player location 
            //e.Graphics.DrawString((("Player Coordinate: " + (int)player.loc_x * (int)scale_width + ", " + ((int)player.loc_y * (int)scale_width)).ToString()),
            //    new Font("Arial", 18), Brushes.White, new Point(0, 30));

            e.Graphics.DrawString(("Player Coordinate: " + (int)player.loc_x + ", " + (int)player.loc_y),
                 new Font("Arial", 18), Brushes.White, new Point(0, 30));

            //Draw player Mass 
            e.Graphics.DrawString((("Mass: " + (int)player.Mass).ToString()), new Font("Arial", 18), Brushes.White, new Point(0, 60));

            //Draw player Width 
            e.Graphics.DrawString((("Width: " + (int)player.Width).ToString()), new Font("Arial", 18), Brushes.White, new Point(0, 90));     

            //draw mouse coordinates for test 
            e.Graphics.DrawString((("Mouse Position: " + x.ToString() + ", " + y.ToString())), new Font("Arial", 18), Brushes.White, new Point(0, 120));

            TimeSpan elapsedSeconds = DateTime.Now - timer;
            //stop adding time if player has died.  
            if (player.Mass != 0)
            {
                totalTime += elapsedSeconds.Seconds;
            }            
            e.Graphics.DrawString(("Time: " + totalTime), new Font("Arial", 18), Brushes.White, new Point(0, 150 ));

            Invalidate();
        }


        /// <summary>
        /// A function that calculates the scale width based on the size do the player
        /// </summary>
        /// <param name="player"></param>
        private void ScaleWidth(Cube player) //form's width? 
        {
            if (!(player.team_id == 0))
            {
                scale_width = this.Width / (player.Width * (15));
            }
            else
            {
                scale_width = this.Width / (player.Width * 10);
            }
        }

        /// <summary>
        /// Function that gets our mouse position relative to the form 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        private void MousePos(out int x, out int y)
        {
            Point pos = PointToClient(Cursor.Position);
            //x = pos.X;
            //y = pos.Y;
            //s.Value.loc_x* scale_width -player.loc_x * scale_width) +vp_width
            x = (int)(pos.X + player.loc_x - (this.Width / 2));
            y = (int)(pos.Y + player.loc_y - (this.Height / 2)); 
        }


        /// <summary>
        /// Callback that sends our name to the server 
        /// </summary>
        /// <param name="state"></param>
        public void First_Contact_Callback(PreservedState state)
        {
            pstate = state;
            NetworkingCode.Send(pstate.State_Socket, Name_Textbox.Text + "\n");
            state.State_Callback = Received_Player_Callback;
            NetworkingCode.i_want_more_data(state);
        }

        /// <summary>
        /// Callback that sets our player that we get from the server 
        /// </summary>
        /// <param name="state"></param>
        public void Received_Player_Callback(PreservedState state)
        {
            string stringData = state.data.ToString(); 
            int EndPlayer = stringData.IndexOf('\n');
            string message = stringData.Substring(0, EndPlayer);
            state.data.Remove(0, EndPlayer + 1); 

            player = JsonConvert.DeserializeObject<Cube>(message);
            world.cubeList.Add(player.uid, player);
            this.Paint += AgCubioGUI_Paint;

            state.State_Callback = Data_Received_Callback;
            NetworkingCode.i_want_more_data(state);
        }

        /// <summary>
        /// Callback that goes through all of the data from the server and turns it into cubes.  
        /// </summary>
        /// <param name="state"></param>
        public void Data_Received_Callback(PreservedState state)
        {
            lock (world)
            {
                int End;
                while ((End = state.data.ToString().IndexOf('\n')) >= 0)
                {
                    string message = state.data.ToString().Substring(0, End);
                    state.data.Remove(0, End + 1); 

                    Cube rebuilt = JsonConvert.DeserializeObject<Cube>(message);
                    if (rebuilt.Mass == 0 && rebuilt.uid == player.uid)
                    {
                        player = rebuilt;
                        world.cubeList.Remove(player.uid);
                        MessageBox.Show("You Died!");
                    }
                    else if (rebuilt.Mass == 0)
                    {
                        world.cubeList.Remove(rebuilt.uid);
                    }
                    else
                    {
                        if (rebuilt.uid == player.uid)
                        {
                            player = rebuilt;                           
                            world.cubeList[player.uid] = rebuilt;
                            ScaleWidth(player);
                        }
                        else
                        {
                            world.cubeList[rebuilt.uid] = rebuilt;
                        }
                    }
                }

            }
            NetworkingCode.i_want_more_data(state);
        }


        /// <summary>
        /// Sends our mouse postion to the server 
        /// </summary>
        public void SendMousePosition()
        { 
            int xpos, ypos;
            MousePos(out xpos, out ypos);
            NetworkingCode.Send(pstate.State_Socket, "(move, " + xpos + ", " + ypos + ")\n"); //do we have to add the "\n" or not?
            Invalidate();
        }


        /// <summary>
        /// Sends out split request to the server 
        /// </summary>
        public void SendSplit()
        {
            int xpos, ypos;
            MousePos(out xpos, out ypos);
            if (!(SignInPanel.Visible == true))
            {
                NetworkingCode.Send(pstate.State_Socket, "(split, " + xpos + ", " + ypos + ")\n");
            }            
        }




        /// <summary>
        /// Connects to the server 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void connectButton_Click(object sender, EventArgs e)
        {
            SignInPanel.Hide();
            NetworkingCode.Connect_to_Server(First_Contact_Callback, Server_Name.Text);
        }


        /// <summary>
        /// tries to send a split request
        /// No matter what we tried to use to have the form register that the space key was pressed NOTHING HAPPENED.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void KeyDownForm(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space)
            {
                SendSplit();
            }
        }


        /// <summary>
        /// Closes the form, tried to add a dialog box that would ask if they really wanted to quit, but whenever we tried to implement that
        /// the form froze.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //DialogResult result = MessageBox.Show("Are you sure you want to quit?", "Close AgCubio",
            //MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            //if (result == DialogResult.Yes)
            //{
                this.Close();
            //}
        }

        /// <summary>
        /// Helpful textbox to show how to play the game.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void How_To_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Move your mouse around the screen to eat food and other players that are smaller than you.  Try not to get eaten by soemeone bigger than you.");
        }
    }
}
