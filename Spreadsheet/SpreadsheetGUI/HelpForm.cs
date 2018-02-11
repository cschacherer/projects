using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SpreadsheetUtilities;
using System.IO;

namespace SS
{
    public partial class HelpForm : Form
    {
        /// <summary>
        /// Help form constructor 
        /// </summary>
        public HelpForm()
        {
            InitializeComponent();
            FirstText(); 
        }

        /// <summary>
        /// General button text 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            FirstText(); 
        }

        /// <summary>
        /// The first text the user will see for Help.  
        /// </summary>
        private void FirstText()
        {
            richTextBox2.Text = "\nWelcome to our Spreadsheet! Here are some general tips to help you navigate.\n" +
                "\nWrite in the Content textbox and press 'Enter' on your keyboard to add content to cell.  Content can be a number, string or formula.  \n\n"
                 + "To delete or clear a cell, hit the 'Delete' key or use the 'Backspace' key and press 'Enter'.\n\n" +
                 "Click on a cell to see it's value and content. Once clicked, it will be highlighted.\n\n" +
                 "Moving the cursor around will easily show what cell your mouse is on with a highlight.\n\n";
        }

        /// <summary>
        /// FAQ text 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            richTextBox2.Text = 
                "\nQ: How can I change a cell's contents and value?\n" +
                "A: Enter the new contents in the Content textbox and hit the 'Enter' key.\n\n" + "Q: How do I delete content from a cell?\n" + 
                "A: You can either click on the cell and hit 'Delete' or leave the Content textbox empty and hit 'Enter'.\n\n" +
                "Q: How open do I open new file?\n" + "A: Use 'Ctrl' + 'N' key or use the 'New' button under file\n\n" + 
                "Q: How open do I open an existing file?\n" + "A: Use 'Ctrl' + 'O' key or use the 'Open' button under file\n\n" + 
                "Q: How open do I save a file?\n" + "A: Use 'Ctrl' + 'S' key or use the 'Save' button under file\n\n" + 
                "Q: How open do I close a file?\n" + "A: Use 'Ctrl' + 'C' key or use the 'Close' button under file\n\n" + 
                "Q: How can I get back to this Help menu?\n" + "A: You can either click on the Help button at the top of the spreadsheet or use 'Ctrl' + 'H' key";
        }

        /// <summary>
        /// Contact Us text 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            richTextBox2.Text = "\nIf this was not helpfull and you need more assistance\n\n" + "Contact Conner and Faith at:  "
                + "University of Utah\n\n" + "Hours: Tuesdays & Thursdays\n\n" + "Time: 2.00pm - 3.20pm\n\n" + "BLDG: WEB L104\n\n";
        }

    
     
    }
}
