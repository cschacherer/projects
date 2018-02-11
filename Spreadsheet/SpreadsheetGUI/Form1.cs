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
    public partial class Form1 : Form
    {
        /// <summary>
        /// Creates a new spreadsheet to hold the cell's contents and values.  
        /// </summary>
        private Spreadsheet s = new Spreadsheet(s => true, s => s.ToUpper(), "ps6");

        /// <summary>
        /// Declares a private variable for filename
        /// </summary>
        private string filename;

        /// <summary>
        /// Declares private variable to hold the selected column's place 
        /// </summary>
        private int column;

        /// <summary>
        /// Declares private variable to hold the selected row's place 
        /// </summary>
        private int row;

        /// <summary>
        /// Default constructor 
        /// </summary>
        public Form1()
        {           
            InitializeComponent();
            NameTextBox.Text = GetCellName().ToString();
            spreadsheetPanel1.SelectionChanged += DisplaySelection;
        }

        /// <summary>
        /// Contructor with filepath parameter to store files when opening a new Form. 
        /// </summary>
        /// <param name="filePath"></param>
        public Form1(string filePath)
        {
            InitializeComponent();
            NameTextBox.Text = GetCellName().ToString();
            filePath = filename;
            spreadsheetPanel1.SelectionChanged += DisplaySelection;
        }

        /// <summary>
        /// Displays the Form GUI and updates the values and contents of it for the user.  
        /// </summary>
        /// <param name="ss"></param>
        private void DisplaySelection(SpreadsheetPanel ss)
        {
            try
            {
                spreadsheetPanel1.GetSelection(out column, out row);

                //Cets cell name and puts it in textbox
                string cellName = GetCellName();
                NameTextBox.Text = cellName;

                //puts contents in textbox
                ContentTextBox.Text = s.GetCellContents(cellName).ToString(); //puts cell's contents in contentbox 

                //puts values in textbox
                string value = cellValue(cellName).ToString();
                if (value == "SpreadsheetUtilities.FormulaError")
                {
                    ValueTextBox.Text = "Formula Error";
                }
                else
                {
                    ValueTextBox.Text = value;
                }
                spreadsheetPanel1.SetValue(column, row, value);

                //Updates values in each cell on the GUI
                UpdateCells();            
            }
            catch (Exception e)
            {
                throw e;                     
            }
        }

        /// <summary>
        /// Goes through each cell and updates it's value for the GUI 
        /// </summary>
        private void UpdateCells()
        {
            HashSet<string> hashNames = new HashSet<string>(s.GetNamesOfAllNonemptyCells());
            foreach (string cell in hashNames)
            {
                GetAddressOfCell(cell);
                spreadsheetPanel1.SetValue(column, row, cellValue(cell).ToString());
            }
        }

        /// <summary>
        /// Gets the row and column of the cell address using ascii.  
        /// </summary>
        /// <param name="name"></param>
        private void GetAddressOfCell(string name)
        {
            char letter = name[0];
            column = letter - 65;
            name = name.Remove(0, 1);
            int.TryParse(name, out row);
            row -= 1;           
        }

        /// <summary>
        /// Gets the cell name based on the selected row and column.  
        /// </summary>
        /// <returns></returns>
        private string GetCellName()
        {
            spreadsheetPanel1.GetSelection(out column, out row);
            column += 65;
            row += 1;
            char c = (char)column;
            string cellName = c.ToString() + row.ToString();
            return cellName; 
        }

        /// <summary>
        /// Gets the cell value for the selected column and row 
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private string cellValue(string name)
        {
            spreadsheetPanel1.GetSelection(out column, out row);  
            object val = s.GetCellValue(name); 
            return val.ToString();           
        }

        /// <summary>
        /// Opens a new form by clicking File and then New. 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NewForm(); 
        }

        /// <summary>
        /// Creates and shows a new form.  
        /// </summary>
        private void NewForm()
        {
            SpreadSheetApplicationContext.getAppContext().DisplayForm(new Form1());
        }

        /// <summary>
        /// Open an existing file by clicking File and Open.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFile(); 
        }

        /// <summary>
        /// Opens a new spreadsheet form.  
        /// </summary>
        private void OpenFile()
        {
            OpenFileDialog openSS = new OpenFileDialog();
            openSS.InitialDirectory = "c:\\";
            openSS.Filter = "Spreadsheet File (*.sprd)| *.sprd | All Files (*.*)|*.*";
            openSS.DefaultExt = "sprd";

            DialogResult r = openSS.ShowDialog();
            if (r == DialogResult.OK)
            {
                filename = openSS.FileName;
                try
                {
                    Form1 temp = new Form1(openSS.FileName);
                    temp.s = new Spreadsheet(filename, s => true, s => s.ToUpper(), "ps6");
                    SpreadSheetApplicationContext.getAppContext().DisplayForm(temp);

                    HashSet<string> HashNames = new HashSet<string>(temp.s.GetNamesOfAllNonemptyCells());
                    foreach (string cell in HashNames)
                    {
                        GetAddressOfCell(cell);
                        temp.spreadsheetPanel1.SetValue(column, row, cellValue(cell).ToString());
                    }
                    temp.DisplaySelection(temp.spreadsheetPanel1);

                }
                catch (IOException)
                {
                    MessageBox.Show("Cannot open File");
                }
            }
        }

        /// <summary>
        /// Saves the file by clicking File and Save.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFile(); 
        }

        /// <summary>
        /// Saves a file to the users computer.  
        /// </summary>
        private void SaveFile()
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Spreadsheet File (*.sprd)| *.sprd | All Files (*.*)|*.*";
            saveFileDialog1.ShowDialog();

            if (saveFileDialog1.FileName != "")
            {
                s.Save(saveFileDialog1.FileName);
                filename = saveFileDialog1.FileName;
            }
        }

        /// <summary>
        /// Closes the file.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CloseFile(); 
        }

        private void CloseFile()
        {
            if (!(s.Changed))
                Close();
            else
            {
                DialogResult result = MessageBox.Show("Do you want to save changes?", "Close Spreadsheet",
                MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                if (result == DialogResult.Yes)
                {
                    saveToolStripMenuItem.PerformClick();
                }
                else if (result == DialogResult.No)
                {
                    Close();
                }
                else if (result == DialogResult.Cancel)
                {
                    return;
                }
            }
        }

        /// <summary>
        /// These create hot keys for creating a new file, opening a file, saving a file, 
        /// and opening the help menu
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void spreadsheetPanel1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.N && e.Modifiers == Keys.Control)
            {
                NewForm();
                e.SuppressKeyPress = true;
            }
            else if (e.KeyCode == Keys.O && e.Modifiers == Keys.Control)
            {
                OpenFile();
                e.SuppressKeyPress = true;
            }
            else if (e.KeyCode == Keys.S && e.Modifiers == Keys.Control)
            {
                SaveFile();
                e.SuppressKeyPress = true;
            }
            else if (e.KeyCode == Keys.H && e.Modifiers == Keys.Control)
            {
                ShowHelp(); 
                e.SuppressKeyPress = true;
            }
            else if (e.KeyCode == Keys.C && e.Modifiers == Keys.Control)
            {
                CloseFile();
                e.SuppressKeyPress = true;
            }
        }

        /// <summary>
        /// If Enter or Delete is presssed, will handle those events by adding or 
        /// deleting cells.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ContentTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Return)
            {
                if (!backgroundWorker1.IsBusy)
                    backgroundWorker1.RunWorkerAsync();
                e.SuppressKeyPress = true;
            }
            //if delete is pressed while a cell is highlighted, it will be deleted.  
            else if (e.KeyCode == Keys.Delete)
            {
                spreadsheetPanel1.GetSelection(out column, out row);
                string cellName = GetCellName();
                string oldContent = s.GetCellContents(cellName).ToString();
                try
                {
                    s.SetContentsOfCell(cellName, string.Empty);
                    DisplaySelection(spreadsheetPanel1);              
                }
                catch (Exception ex)
                {
                    s.SetContentsOfCell(cellName, oldContent);
                    DisplaySelection(spreadsheetPanel1);
                    MessageBox.Show(ex.ToString());
                }
            }
            else if (e.KeyCode == Keys.N && e.Modifiers == Keys.Control)
            {
                NewForm();
                e.SuppressKeyPress = true;
            }
            else if (e.KeyCode == Keys.O && e.Modifiers == Keys.Control)
            {
                OpenFile();
                e.SuppressKeyPress = true;
            }
            else if (e.KeyCode == Keys.S && e.Modifiers == Keys.Control)
            {
                SaveFile();
                e.SuppressKeyPress = true;
            }
            else if (e.KeyCode == Keys.H && e.Modifiers == Keys.Control)
            {
                ShowHelp(); 
                e.SuppressKeyPress = true;
            }
            else if (e.KeyCode == Keys.C && e.Modifiers == Keys.Control)
            {
                CloseFile();
                e.SuppressKeyPress = true;
            }

        }

        /// <summary>
        /// Shows the Help window if you click on Help.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void helpToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            ShowHelp(); 
        }

        /// <summary>
        /// Shows the Help menu.  
        /// </summary>
        private void ShowHelp()
        {
            HelpForm help = new HelpForm();
            help.Show();
        }

        /// <summary>
        /// Background worker that executes the SetContentsOfCell instruction.  
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            spreadsheetPanel1.GetSelection(out column, out row);
            string cellName = GetCellName();
            string oldContent = s.GetCellValue(cellName).ToString();
            string newContent = ContentTextBox.Text;
            try
            {
                //if ContentTextBox has nothing in it and return in pressed, the cell will be removed 
                //if ContentTextBox has something in it and return is pressed, will set the cell to the contents
                //pressing enter is now the only way to set content to a cell.  
                s.SetContentsOfCell(cellName, newContent);
                Invoke(new Action(() =>
                {
                    DisplaySelection(spreadsheetPanel1);
                }));
            }
            catch (Exception ex)
            {
                s.SetContentsOfCell(cellName, oldContent);
                              
                Invoke(new Action(() =>
                {
                    DisplaySelection(spreadsheetPanel1);
                    if (ex is FormulaFormatException)
                    {
                        MessageBox.Show("Formula Format Error");
                    }
                    else if (ex is CircularException)
                    {
                        MessageBox.Show("Circular Dependency Error");
                    }
                    else if (ex is ArgumentNullException)
                    {
                        MessageBox.Show("Cannot put a null value in a cell.");
                    }
                    else if (ex is InvalidNameException)
                    {
                        MessageBox.Show("Invalid cell name");
                    }
                    else
                    {
                        MessageBox.Show(ex.ToString());
                    }
                })); 
            }
        }  

    }//End of Form1 class

}//End of Namespace
