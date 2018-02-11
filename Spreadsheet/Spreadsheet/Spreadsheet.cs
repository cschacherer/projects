using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SpreadsheetUtilities;
using System.Text.RegularExpressions;
using System.Xml; 

namespace SS 
{  
    public class Spreadsheet : AbstractSpreadsheet
    {
        /// <summary>
        /// Holds all the dependencies of the spreadsheet's cells.  
        /// </summary>
        private DependencyGraph dg; 

        /// <summary>
        /// Holds the name of each cell and it's contents.  
        /// </summary>
        private Dictionary<string, Cell> sd;

        /// <summary>
        /// Changed represents whether something has been added to the spreadsheet.  Changed is false
        /// when the spreadsheet is first created, true when something is changed and goes back to false
        /// once the spreadsheet has been saved.  
        /// </summary>
        public override bool Changed { get; protected set; }

        /// <summary>
        /// Zero argument constructor 
        /// </summary>
        public Spreadsheet() : this(s => true, s => s, "default")
        {
        }

        /// <summary>
        /// Three argument constructor.  
        /// </summary>
        /// <param name="isValid"></param>
        /// <param name="normalize"></param>
        /// <param name="version"></param>
        public Spreadsheet(Func<string, bool> isValid, Func<string, string> normalize, string version) : base(isValid, normalize, version)
        {
            dg = new DependencyGraph();
            sd = new Dictionary<string, Cell>();
            Changed = false;
        }

        /// <summary>
        /// Four argument constructor, checks version and will load the cells in the file into this spreadsheet.  
        /// </summary>
        /// <param name="file"></param>
        /// <param name="isValid"></param>
        /// <param name="normalize"></param>
        /// <param name="version"></param>
        public Spreadsheet(String file, Func<string, bool> isValid, Func<string, string> normalize, string version) : base(isValid, normalize, version)
        {
            if (GetSavedVersion(file) != version) //Checks to see if version of file is same version as the parameter.  
            {
                throw new SpreadsheetReadWriteException("File versions do not match.");
            }
            dg = new DependencyGraph();
            sd = new Dictionary<string, Cell>();
            Changed = false;
            Load(file); //Puts all the cells of the file into this spreadsheet.      
        }


                /// <summary>
        /// Gets the contents of the cell with the same name. If name is null or invalid, it 
        /// throws an InvalidNameException.
        /// 
        /// Returns the contents of a cell, either a string, double or formula.  
        /// If it hasn't been assigned any, it returns an empty string.  
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public override object GetCellContents(string name)
        {          
            if (name == null || !ValidVariable(name) || !IsValid(name))//Checks to see if name is a valid variable or null.  
            {
                throw new InvalidNameException(); 
            }
            name = Normalize(name);
            if (sd.ContainsKey(name)) //Checks to see if it's in the Spreadsheet dictionary
            {
                return sd[name].Contents; 
            }
            return string.Empty; //Returns empty string because the name hasn't been assigned any content.  
        }

        /// <summary>
        /// Enumerates the names of all the non-empty cells in the spreadsheet by returning the Spreadsheet Dictionary's keys.  
        /// </summary>
        public override IEnumerable<string> GetNamesOfAllNonemptyCells()
        {
            return sd.Keys; //Returns Spreadsheet dictionary keys.  
        }

        /// <summary>
        /// Set the contents of a cell if it is a formula.  Checks to see if is has a circular exception and 
        /// if it does it returns it to the Dependency Graph before the cell tried to be added.  
        /// Returns the other cells that directly or indirectly depend on it.  
        /// </summary>
        /// <param name="name"></param>
        /// <param name="formula"></param>
        /// <returns></returns>
        protected override ISet<string> SetCellContents(string name, Formula formula)
        {
            Cell c = new Cell(formula, CheckValue); //Creates new cell with formula as the content
            sd[name] = c;  //Sets value of name to cell c
            DependencyGraph tempDG = new DependencyGraph(dg); //Creates a temporary dependency graph in case you have to revert back to it.        
            try
            {
                dg.ReplaceDependents(name, new HashSet<string>(formula.GetVariables())); //Change dg[name] dependents
                GetCellsToRecalculate(name); //See if there is a circular execption.  
            }
            catch(CircularException)
            {
                dg = tempDG; //Returns dependency graph to how it was before implementing the circular dependency.  
                throw new CircularException(); 
            }
            catch(FormulaFormatException)
            {
                throw new FormulaFormatException("Invalid variables in the formula");
            }
            return new HashSet<string>(GetCellsToRecalculate(name)); //Returns correct cell dependencies.  
        }

        /// <summary>
        /// Checks to see if string text is null or empty.  If it isn't then it adds it 
        /// to the the Spreadsheet.  Returns any cells that directly or indirectly depend on it.  
        /// </summary>
        /// <param name="name"></param>
        /// <param name="text"></param>
        /// <returns></returns>
        protected override ISet<string> SetCellContents(string name, string text)
        {
            //Test new repo
            if (text == null)
            {
                throw new ArgumentNullException(); 
            }
            else if (text == string.Empty)
            {
                //Won't add name to Spreadsheet dictionary.  
                if(sd.ContainsKey(name))
                {
                    sd.Remove(name); 
                }
                dg.ReplaceDependents(name, new HashSet<string>()); 
                return new HashSet<string>(GetCellsToRecalculate(name));
            }           
            else
            {
                //Add name and text to Spreadsheet dictionary
                Cell c = new Cell(text, CheckValue);
                sd[name] = c;
                dg.ReplaceDependents(name, new HashSet<string>());
                return new HashSet<string>(GetCellsToRecalculate(name));
            }        
        }

        /// <summary>
        /// Sets the contents of a cell to a double.  Returns any other cells that directly or indirectly 
        /// depend on it.  
        /// </summary>
        /// <param name="name"></param>
        /// <param name="number"></param>
        /// <returns></returns>
        protected override ISet<string> SetCellContents(string name, double number) 
        {  
            //Adds name and number value to Spreadsheet dictionary.  
            Cell c = new Cell(number, CheckValue);
            sd[name] = c;
            dg.ReplaceDependents(name, new HashSet<string>());
            return new HashSet<string>(GetCellsToRecalculate(name));
        }

        /// <summary>
        /// If name is null, throws an ArgumentNullException.
        /// Otherwise, if name isn't a valid cell name, throws an InvalidNameException.
        /// Returns an enumeration of dependents of the name. 
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        protected override IEnumerable<string> GetDirectDependents(string name)
        {
            if (name == null)
            {
                throw new ArgumentNullException(); 
            }
            name = Normalize(name);
            if (!ValidVariable(name) || !IsValid(name)) //Does not pass my variable test or any added variable test by user.  
            {
                throw new InvalidNameException();
            }   
            return dg.GetDependees(name); //Returns name's dependents in the Dependency Graph.  
        }


        /// <summary>
        /// Checks to see if the name variable is valid.  Returns true if it is valid and false if it is not.  
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private bool ValidVariable(string name)
        {
            bool valid = Regex.IsMatch(name, @"^([a-zA-Z]+\d+)$"); 
            return valid;
        }

//////////////////////////////////////////////////////////NEW FORMULAS FOR PS5\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

        /// <summary>
        /// Will load a string file and put in all the cells in the file into the new spreadsheet.  
        /// </summary>
        /// <param name="file"></param>
        public void Load(string file)
        {
            try
            {
                using (XmlReader reader = XmlReader.Create(file))
                {
                    string cellName = ""; //Declares cell's name to be used later
                    string cellContents = ""; //Declares cell's contents to be used later.  
                    while (reader.Read())
                    {
                        if(reader.IsStartElement()) //Checks to see if it is the start of an element
                        { 
                            switch(reader.Name) //Switch to the element's name
                            { 
                                case "spreadsheet": //Don't need to set version because it was already set in the constructor.  
                                    break; 
                                case "cell":
                                    break;
                                case "name":
                                    reader.Read();
                                    cellName = reader.Value;                               
                                    break;
                                case "contents":
                                    reader.Read(); 
                                    cellContents = reader.Value;
                                    SetContentsOfCell(cellName, cellContents);  //Puts cells from file into this spreadsheet.  
                                    break;                                                           
                            }
                        }
                    }
                }
            }
            //Catches various exceptions.  
            catch (System.IO.FileNotFoundException) 
            {
                throw new SpreadsheetReadWriteException("File was not found.");
            }
            catch (System.IO.DirectoryNotFoundException)
            {
                throw new SpreadsheetReadWriteException("Directory was not found.");
            }
            catch (ArgumentNullException)
            {
                throw new SpreadsheetReadWriteException("File was null.");
            }
            catch (System.Security.SecurityException)
            {
                throw new SpreadsheetReadWriteException("Was not able to access the file for security reasons.");
            }
            catch (UriFormatException)
            {
                throw new SpreadsheetReadWriteException("The file format was not valid.");
            }
            catch (InvalidOperationException)
            {
                throw new SpreadsheetReadWriteException("An asynchronous operation is already in progress.");
            }
            catch (XmlException)
            {
                throw new SpreadsheetReadWriteException("There was a problem reading the file.");
            }
        } //End of Load function.  


        // ADDED FOR PS5
        /// <summary>
        /// Returns what the version of the file is.  Throws a SpreadsheetReadWriteException if 
        /// something goes wrong opening, reading, or closing the file.  
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        public override string GetSavedVersion(string filename)
        {
            try
            {
                using (XmlReader reader = XmlReader.Create(filename))
                {
                    while (reader.Read())
                    {
                        reader.ReadToFollowing("spreadsheet"); //Read only until spreadsheet and then move to it's attribute "version"
                        if (reader.MoveToAttribute("version"))
                        {
                            return reader["version"]; //Returns value of "version"
                        }
                        else
                        {
                            throw new SpreadsheetReadWriteException("Version was not found."); 
                        }
                    }
                }
            }
            //Catches various exceptions.  
            catch(System.IO.FileNotFoundException)
            {
                throw new SpreadsheetReadWriteException("File was not found."); 
            }
            catch (System.IO.DirectoryNotFoundException)
            {
                throw new SpreadsheetReadWriteException("Directory was not found.");
            }
            catch (ArgumentNullException)
            {
                throw new SpreadsheetReadWriteException("File was null.");
            }
            catch (System.Security.SecurityException)
            {
                throw new SpreadsheetReadWriteException("Was not able to access the file for security reasons.");
            }
            catch (UriFormatException)
            {
                throw new SpreadsheetReadWriteException("The file format was not valid.");
            }
            catch(InvalidOperationException)
            {
                throw new SpreadsheetReadWriteException("An asynchronous operation is already in progress."); 
            }
            catch (XmlException)
            {
                throw new SpreadsheetReadWriteException("There was a problem reading the file.");
            }
            throw new SpreadsheetReadWriteException("Couldn't read file.");       
        } //End of GetSavedVersion function.  


        // ADDED FOR PS5
        /// <summary>
        /// Writes the contents of this spreadsheet to the named file using an XML format.
        /// The XML elements should be structured as follows:
        /// 
        /// <spreadsheet version="version information goes here">
        /// 
        /// <cell>
        /// <name>
        /// cell name goes here
        /// </name>
        /// <contents>
        /// cell contents goes here
        /// </contents>    
        /// </cell>
        /// 
        /// </spreadsheet>
        /// 
        /// There should be one cell element for each non-empty cell in the spreadsheet.  
        /// If the cell contains a string, it should be written as the contents.  
        /// If the cell contains a double d, d.ToString() should be written as the contents.  
        /// If the cell contains a Formula f, f.ToString() with "=" prepended should be written as the contents.
        /// 
        /// If there are any problems opening, writing, or closing the file, the method should throw a
        /// SpreadsheetReadWriteException with an explanatory message.
        /// </summary>
        public override void Save(string filename)
        {
            try
            {
                using (XmlWriter writer = XmlWriter.Create(filename))
                {
                    writer.WriteStartDocument();
                    writer.WriteStartElement("spreadsheet");
                    writer.WriteAttributeString("version", Version); //Version is attribute of "spreadsheet"

                    foreach (string key in sd.Keys) //Writes each cell in the spreadsheet.  
                    {
                        writer.WriteStartElement("cell");
                        writer.WriteElementString("name", key); //setting name
                        string keyContents;                       
                        if (sd[key].Contents is Formula)
                        {                           
                            keyContents = "= " + sd[key].Contents.ToString(); //Contents is formula 
                        }
                        else
                        {
                            keyContents = sd[key].Contents.ToString(); //Contents is string or double.  
                        }
                        writer.WriteElementString("contents", keyContents); //setting contents 
                        writer.WriteEndElement(); //End of cell 
                    }
                    writer.WriteEndElement(); //End of Spreadsheet
                    writer.WriteEndDocument(); //End of Document
                    writer.Close(); //Stop writer.  
                    Changed = false; 
                }
            }
            //Catches various exceptions.  
            catch (System.IO.FileNotFoundException)
            {
                throw new SpreadsheetReadWriteException("File was not found.");
            }
            catch (System.IO.DirectoryNotFoundException)
            {
                throw new SpreadsheetReadWriteException("Directory was not found.");
            }
            catch (ArgumentNullException)
            {
                throw new SpreadsheetReadWriteException("File was null.");
            }
            catch (System.Security.SecurityException)
            {
                throw new SpreadsheetReadWriteException("Was not able to access the file for security reasons.");
            }
            catch (UriFormatException)
            {
                throw new SpreadsheetReadWriteException("The file format was not valid.");
            }
            catch (InvalidOperationException)
            {
                throw new SpreadsheetReadWriteException("An asynchronous operation is already in progress.");
            }
        } //End of Save function.  


        // ADDED FOR PS5
        /// <summary>
        /// If name is null or invalid, throws an InvalidNameException.
        /// Else it returns the Value of a cell, which will be a string, double or FormulaError.  
        /// If it is not in the Spreadsheet Dictionary then it returns an empty string.  
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public override object GetCellValue(string name)
        {            
            if (name == null || !ValidVariable(Normalize(name)) || !IsValid(Normalize(name))) //Checks to make sure name is valid.  
            {
                throw new InvalidNameException(); 
            }
            name = Normalize(name);
            if (!sd.ContainsKey(name)) //If name isn't in Spreadsheet dictionary, returns an empty string.  
            {
                return string.Empty; 
            }
            return sd[name].Value; 
            //return sd[name].CalculateCellValue();  //Returns value of name (string, double, or Formula Error) 
        }


        /// <summary>
        /// This is used as the lookup function if the contents of a cell is a formula.  If the variable that it 
        /// tries to get a value for by using GetCellValue is not double, it is not valid variable and will throw 
        /// a new Argument exception that will become a FormulaError.  
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        private double CheckValue(string name) //Used to check value of variables in a formula to calculate cell's value.  
        {
            double solution; 
            if(double.TryParse(GetCellValue(name).ToString(), out solution)) //Sees if value of variable is a double.  
            {
                return solution; 
            }
            //If it can't be parsed into a number, throws an Argument Exception that the Formula library will catch and return a Formula Error.  
            throw new ArgumentException(); 
        }


        // ADDED FOR PS5
        /// <summary>
        /// If content is null, throws an ArgumentNullException.
        /// Otherwise, if name is null or invalid, throws an InvalidNameException.
        /// Otherwise, the content will be set as a double or string.  If there is an equals sign
        /// then it will become a formula.  Depending on what the contents is, it will be sent to SetCellContents to 
        /// be added to the Spreadsheet Dictionary.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="content"></param>
        /// <returns></returns>
        public override ISet<string> SetContentsOfCell(string name, string content)
        {
            if(content == null)
            {
                throw new ArgumentNullException(); 
            }
            else if (name == null || !ValidVariable(Normalize(name)) || !IsValid(Normalize(name))) //Checks to see if name is valid
            {
                throw new InvalidNameException(); 
            }
            name = Normalize(name); 
            Changed = true; //Will add to spreadsheet so changed is true.  
            HashSet<string> CellDependents; 
            //Content is double
            double x; 
            if (double.TryParse(content, out x))
            {
                CellDependents = new HashSet<string>(SetCellContents(name, x));  
                //return SetCellContents(name, x); 
            }
            //Content is formula
            else if (content != string.Empty && content[0] == '=')
            {
                content = content.Remove(0, 1);
                CellDependents = new HashSet<string>(SetCellContents(name, new Formula(content, Normalize, IsValid)));  
                //return SetCellContents(name, new Formula(content, Normalize, IsValid));
            }
            //Content is string
            else
            {
                CellDependents = new HashSet<string>(SetCellContents(name, content));
                //return SetCellContents(name, content); 
            }           
            foreach (string s in CellDependents)
            {
                if (sd.ContainsKey(s))
                {
                    if (sd[s].Contents is Formula)
                    {
                        //sd[s].CalculateCellValue();
                        sd[s].Value = (sd[s].Contents as Formula).Evaluate(CheckValue);
                    }

                }               
            }                       
            return CellDependents;             
        }


        /// <summary>
        /// Private class that is the value of the name(key in sd).  Holds the contents of what is in the cell which can be 
        /// a formula, double, or string and the value of the cell which is either a double or a string.  
        /// </summary>
        private class Cell
        {
            /// <summary>
            /// The contents of the cell will hold a double, string, or formula  
            /// </summary>
            public Object Contents { get; set; }

            /// <summary>
            /// The value of the formula will either be a double, string, or FormulaError
            /// </summary>
            public Object Value { get; set; }

            /// <summary>
            /// Holds the getValue function from the constructor so 
            /// </summary>
            public Func<string, double> lookupVariableValue; 

            /// <summary>
            /// Contructor of Cell, sets Contents and then evaluates them to get cell's Value.  
            /// </summary>
            /// <param name="contents"></param>
            /// <param name="getValue"></param>
            public Cell(object contents, Func<string, double> getValue)
            {
                this.Contents = contents;
                this.lookupVariableValue = getValue;
                //Contents is a formula 
                if (Contents is Formula)
                {
                    Formula f = Contents as Formula;
                    Value = f.Evaluate(lookupVariableValue);
                }
                //Contents is a double or string.  
                else
                {
                    Value = Contents;
                }
            }

            /// <summary>
            /// Will recalculate the cell value from the most recent variables. 
            /// </summary>
            /// <returns></returns>
            public object CalculateCellValue()
            {
                //Contents is a formula 
                if (Contents is Formula)
                {
                    Formula f = Contents as Formula;
                    Value = f.Evaluate(lookupVariableValue);
                    return Value; 
                }
                //Contents is a double or string.  
                else
                {
                    Value = Contents;
                    return Value; 
                }
            }
        }//End of private Cell class
   
    } //End of Spreadsheet class
} //End of namespace
