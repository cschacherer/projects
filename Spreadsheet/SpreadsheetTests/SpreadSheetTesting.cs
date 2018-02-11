using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;
using SS;
using SpreadsheetUtilities;
using System.IO;
using System.Threading;
using System.Xml; 

namespace SpreadsheetTests
{
    
    [TestClass]
    public class SpreadSheetTesting
    {
        /// <summary>
        /// Test to see if a double will set properly and be able to get it back.  
        /// </summary>
        [TestMethod]
        public void SetContentTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("A1", "5.0");
            Assert.AreEqual(5.0, s.GetCellContents("A1")); 
        }

        /// <summary>
        /// Test to see if a string will set properly and be able to get it back.  
        /// </summary>
        [TestMethod]
        public void SetContentTest2()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("b35", "dog");
            Assert.AreEqual("dog", s.GetCellContents("b35"));
        }

        /// <summary>
        /// Test to see if a formula will set properly and be able to get it back.  
        /// </summary>
        [TestMethod]
        public void SetContentTest3()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("cc4", " = 3 + 4");
            Assert.AreEqual(" = 3 + 4" , s.GetCellContents("cc4"));
        }

        /// <summary>
        /// Test to see if a formula with a variable inside it will set properly and be able to get it back.  
        /// </summary>
        [TestMethod]
        public void SetContentTest4()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("A4", "4");     
            s.SetContentsOfCell("d0", "= A4 + 4");
            Assert.AreEqual(new Formula("A4 + 4"), s.GetCellContents("d0"));
        }

        /// <summary>
        /// Test to see if a error will be caught if there is an invalid variable within the formula.  
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(FormulaFormatException))]
        public void SetContentTest5()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("ea1", "= 6B - 1");
            Assert.AreEqual(new Formula("6B - 1"), s.GetCellContents("ea1"));
        }

        /// <summary>
        /// Test to see if a error will be caught if there is an invalid name.   
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(InvalidNameException))]
        public void SetContentTest6()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("e3e4", " = 1");
        }

        /// <summary>
        /// Test to see if a error will be caught if the name is null
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(InvalidNameException))]
        public void SetContentTest7()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell(null, "cat");
        }

        /// <summary>
        /// Test to see if it will not cause an error if it calls a variable in a function before the variable has been named.   
        /// </summary>
        [TestMethod]
        public void SetContentTest8()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("b55", "= 9 - G8");
        }

        /// <summary>
        /// Test to see if it will pass a stress test.   
        /// </summary>
        [TestMethod]
        public void SetContentTest9()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("b55", "=(((((2+3*1)/(7e-5+2-4))*5+.0005e+92)-8.2)*3.14159) * ((2+3.1)-.00000000008)");
        }

        /// <summary>
        /// Test to see if it will pass a stress test.   
        /// </summary>
        [TestMethod]
        public void SetContentTest10()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("a1", "=7e-5+2");
        }

        /// <summary>
        /// Test to see if a error will be caught if the content is null.  
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentNullException))]
        public void SetContentTest11()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("h22", null);
        }

        /// <summary>
        /// Test to see if a error will be caught if there is a circular dependency.  
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(CircularException))]
        public void SetContentTest12()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("h22", "=   10    + 10");
            s.SetContentsOfCell("c20", "=h22 +        1");
            s.SetContentsOfCell("h22", "=         c20 * 80"); 
        }

        /// <summary>
        /// Test to see if it will correctly not make something a formula if there is a space between the equals.  
        /// </summary>
        [TestMethod]
        public void SetContentTest13()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("h22", "                    =10 + 10");
            Assert.AreEqual("                    =10 + 10", s.GetCellValue("h22")); 
        }

        /// <summary>
        /// Test to see if it will override a Spreadsheet dictionary key with a new value.    
        /// </summary>
        [TestMethod]
        public void SetContentTest14()
        {
            AbstractSpreadsheet s = new Spreadsheet();         
            s.SetContentsOfCell("a2", "5.0");
            s.SetContentsOfCell("a2", "Five");
            s.SetContentsOfCell("a2", "= 5 + 5");
            s.SetContentsOfCell("B3", "1.0");
            s.SetContentsOfCell("a2", "= 5 + B3");
            Assert.AreEqual(6.0, s.GetCellValue("a2")); 
        }

        /// <summary>
        /// Test to see if it will catch a null exception.    
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(ArgumentNullException))]
        public void SetContentTest15()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("a2", null);           
        }

        /// <summary>
        /// Test to see if it will catch an empty string and not put it in the dictionary.    
        /// </summary>
        [TestMethod]
        public void SetContentTest16()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("e1", "puppy"); 
            s.SetContentsOfCell("e5", string.Empty);
            HashSet<string> test = new HashSet<string>() { "e1" };
            HashSet<string> names = new HashSet<string>(s.GetNamesOfAllNonemptyCells());
            Assert.AreEqual(test.ToString(), names.ToString()); 
        }


        /// <summary>
        /// Test to see if it will get the value of a double.    
        /// </summary>
        [TestMethod]
        public void GetValueTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("a21", "40.9");
            Assert.AreEqual(40.9, s.GetCellValue("a21")); 
        }

        /// <summary>
        /// Test to see if it will get the value of a string.    
        /// </summary>
        [TestMethod]
        public void GetValueTest2()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("bB4", "california");
            Assert.AreEqual("california", s.GetCellValue("bB4"));
        }

        /// <summary>
        /// Test to see if it will get the value of a correct formula.    
        /// </summary>
        [TestMethod]
        public void GetValueTest3()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("c5", "= 3 + 7");
            Assert.AreEqual(10.0, s.GetCellValue("c5"));
        }

        /// <summary>
        /// Test to see if it will get the value of a formula with correct variables.    
        /// </summary>
        [TestMethod]
        public void GetValueTest4()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("zz35", "= 5 + 5");
            s.SetContentsOfCell("a1", "= zz35 + 5"); 
            Assert.AreEqual(15.0, s.GetCellValue("a1"));
        }

        /// <summary>
        /// Test to see if it will get the value of a formula with multiple correct variables.    
        /// </summary>
        [TestMethod]
        public void GetValueTest5()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("zz35", "= 5 + 5");
            s.SetContentsOfCell("a1", "= zz35 + 5");
            s.SetContentsOfCell("RED35", "= a1 + zz35"); 
            Assert.AreEqual(25.0, s.GetCellValue("RED35"));
        }

        /// <summary>
        /// Test to see if it will get an error to find the value of a formula with empty variables.    
        /// </summary>
        [TestMethod]
        public void GetValueTest6()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("dog700", "= 15 + b5");
            Assert.IsInstanceOfType(s.GetCellValue("dog700"), typeof(FormulaError));
        }

        /// <summary>
        /// Test to see if it will get an error if you try to divide by zero.    
        /// </summary>
        [TestMethod]
        public void GetValueTest7()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("er45", "= 15/0");
            Assert.IsInstanceOfType(s.GetCellValue("er45"), typeof(FormulaError));
        }

        /// <summary>
        /// Test to see if it will get an error if you try to divide by zero.    
        /// </summary>
        [TestMethod]
        public void GetValueTest8()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("a7", "0"); 
            s.SetContentsOfCell("e8", "=3/a7");
            Assert.IsInstanceOfType(s.GetCellValue("e8"), typeof(FormulaError));
        }

        //////////////NORMALIZE AND ISVALID METHODS
        public bool IsValidMethod(string var)
        {
            return true; 
        }

        public string NormalizeMethod(string var)
        {
            return var; 
        }


        /// <summary>
        /// Test to see if it won't have an error if you put in the four parameters.   
        /// </summary>
        [TestMethod]
        public void XMLReaderTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/Documents/PS5_XMLReaderTest1.xml", IsValidMethod, NormalizeMethod, "default");
            Assert.AreEqual("cat", s.GetCellValue("a1")); 
        }

        /// <summary>
        /// Test to see if it will have an error if you put a file with the wrong version.   
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void XMLReaderTest2()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/Documents/PS5_XMLReaderTest2.txt", IsValidMethod, NormalizeMethod, "default");
        }

        /// <summary>
        /// Test to see if it will have an error if you put a file with no version.   
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void XMLReaderTest3()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/Documents/PS5_XMLReaderTest3.txt", IsValidMethod, NormalizeMethod, "default");
        }

        /// <summary>
        /// Test to see if it will have an error if you put a file with the wrong filepath.   
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void XMLReaderTest3_1()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/PS5_XMLReaderTest3.txt", IsValidMethod, NormalizeMethod, "default");
        }

        /// <summary>
        /// Test to see if it will have an error if you put a file that is blank.   
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void XMLReaderTest4()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/Documents/PS5_XMLReaderTest4.txt", IsValidMethod, NormalizeMethod, "default");
        }

        /// <summary>
        /// Test to see if it will have an error if you have different string file version and string version .   
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void XMLReaderTest5()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/Documents/PS5_XMLReaderTest5.txt", IsValidMethod, NormalizeMethod, "1.0");
        }

        /// <summary>
        /// Test to see if it will have not an error if version is something other than default.   
        /// </summary>
        [TestMethod]
        public void XMLReaderTest6()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/Documents/PS5_XMLReaderTest6.txt", IsValidMethod, NormalizeMethod, "1.2");
            Assert.AreEqual("cat", s.GetCellValue("a1"));
        }

        /// <summary>
        /// Test to see if save if the spreadsheet is empty and only the constructor has been called.   
        /// </summary>
        [TestMethod]
        public void SaveTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet(IsValidMethod, NormalizeMethod, "default");
            s.Save("C:/Users/Conner/Documents/PS5_SaveTest1Text"); 
            s.Save("C:/Users/Conner/Documents/PS5_SaveTest1XML");              
        }

        /// <summary>
        /// Test to see if save if the spreadsheet is has one cell.   
        /// </summary>
        [TestMethod]
        public void SaveTest2()
        {
            AbstractSpreadsheet s = new Spreadsheet(IsValidMethod, NormalizeMethod, "default");
            s.SetContentsOfCell("a1", "cat"); 
            s.Save("C:/Users/Conner/Documents/PS5_SaveTest2XML.xml");
        }

        /// <summary>
        /// Test to see if save if the spreadsheet is has multiple different cells.   
        /// </summary>
        [TestMethod]
        public void SaveTest3()
        {
            AbstractSpreadsheet s = new Spreadsheet(IsValidMethod, NormalizeMethod, "default");
            s.SetContentsOfCell("a1", "cat");
            s.SetContentsOfCell("bbb333", "567");
            s.SetContentsOfCell("c20", "= bbb333 + 1");
            s.SetContentsOfCell("d6", "= 10 + 15"); 
            s.Save("C:/Users/Conner/Documents/PS5_SaveTest3.xml");
        }

        /// <summary>
        /// Test to catch errors, null file.  
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void SaveTest4()
        {
            AbstractSpreadsheet s = new Spreadsheet(IsValidMethod, NormalizeMethod, "default");
            s.SetContentsOfCell("a1", "cat");
            s.SetContentsOfCell("bbb333", "567");
            s.SetContentsOfCell("c20", "= bbb333 + 1");
            s.SetContentsOfCell("d6", "= 10 + 15");
            s.Save(null);
        }

        /// <summary>
        /// Test to catch errors, wrong format.
        /// </summary>
        [TestMethod]
        public void SaveTest5()
        {
            AbstractSpreadsheet s = new Spreadsheet(IsValidMethod, NormalizeMethod, "default");
            s.SetContentsOfCell("a1", "cat");
            s.SetContentsOfCell("bbb333", "567");
            s.SetContentsOfCell("c20", "= bbb333 + 1");
            s.SetContentsOfCell("d6", "= 10 + 15");
            s.Save("C:/Users/Conner/Documents/PS5_SaveTest3.pdf");
        }

        /// <summary>
        /// Test to catch errors.  File Not Found 
        /// </summary>
        [TestMethod]
        public void SaveTest6()
        {
            AbstractSpreadsheet s = new Spreadsheet(IsValidMethod, NormalizeMethod, "default");
            s.SetContentsOfCell("a1", "cat");
            s.SetContentsOfCell("bbb333", "567");
            s.SetContentsOfCell("c20", "= bbb333 + 1");
            s.SetContentsOfCell("d6", "= 10 + 15");
            s.Save("C:/Users/Conner/PS5_SaveTest3.xml");
        }

        /// <summary>
        /// Test to see if save if it will catch an file not found error   
        /// </summary>
        [TestMethod]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void SaveTest7()
        {
            AbstractSpreadsheet s = new Spreadsheet("fjdkddd", IsValidMethod, NormalizeMethod, "default");
        }

        /// <summary>
        /// Test loading once cell.  
        /// </summary>
        [TestMethod()]
        public void LoadTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/Documents/PS5_SaveTest2XML.xml", IsValidMethod, NormalizeMethod, "default");
            Assert.AreEqual("cat", s.GetCellValue("a1"));
        }

        /// <summary>
        /// Test loading once cell.  
        /// </summary>
        [TestMethod()]
        public void LoadTest2()
        {
            AbstractSpreadsheet s = new Spreadsheet("C:/Users/Conner/Documents/PS5_SaveTest3.xml", IsValidMethod, NormalizeMethod, "default");
            //s.SetContentsOfCell("a1", "cat");
            //s.SetContentsOfCell("bbb333", "567");
            //s.SetContentsOfCell("c20", "= bbb333 + 1");
            //s.SetContentsOfCell("d6", "= 10 + 15");
            s.SetContentsOfCell("e5", "= d6 - 10");
            Assert.AreEqual(15.0, s.GetCellValue("e5")); 
        }

        /// <summary>
        /// Test loading errors, ArgumentNullException
        /// </summary>
        [TestMethod()]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void LoadTest3()
        {
            AbstractSpreadsheet s = new Spreadsheet(null, IsValidMethod, NormalizeMethod, "default");
        }

        /// <summary>
        /// Test loading errors, File not found
        /// </summary>
        [TestMethod()]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void LoadTest4()
        {
            AbstractSpreadsheet s = new Spreadsheet("fjdls", IsValidMethod, NormalizeMethod, "default");
        }

        /// <summary>
        /// Test loading once cell.  
        /// </summary>
        [TestMethod()]
        public void ChangedTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet(IsValidMethod, NormalizeMethod, "default");
            Assert.AreEqual(false, s.Changed);
            s.SetContentsOfCell("ee44", "dog");
            Assert.AreEqual(true, s.Changed);
            s.Save("C:/Users/Conner/Documents/ChangedTest.xml");
            Assert.AreEqual(false, s.Changed);
            s.SetContentsOfCell("e4", "3");
            Assert.AreEqual(true, s.Changed);
            s.Save("C:/Users/Conner/Documents/ChangedTest.xml");
            Assert.AreEqual(false, s.Changed);
            s.SetContentsOfCell("eee444", "= 3 + 3");
            Assert.AreEqual(true, s.Changed);
            s.Save("C:/Users/Conner/Documents/ChangedTest.xml");
            Assert.AreEqual(false, s.Changed);
        }

        /// <summary>
        /// Check to make sure a it will return an empty string if the name is not assigned for GetCellContents.    
        /// </summary>
        [TestMethod()]
        public void ContentTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            Assert.AreEqual("", s.GetCellContents("e4")); 
        }

        /// <summary>
        /// Check to make sure a it will return an error if name is null for GetCellContents.    
        /// </summary>
        [TestMethod()]
        [ExpectedException(typeof(InvalidNameException))]
        public void ContentTest2()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            Assert.AreEqual("", s.GetCellContents(null));
        }

        /// <summary>
        /// Check to make sure a it will return an error if name is not a valid variable for GetCellContents.    
        /// </summary>
        [TestMethod()]
        [ExpectedException(typeof(InvalidNameException))]
        public void ContentTest3()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            Assert.AreEqual("", s.GetCellContents("77a"));
        }

        /// <summary>
        /// Check to make sure a it will return a double, string or formula for GetCellContents.    
        /// </summary>
        [TestMethod()]
        public void ContentTest4()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("y67", "goat");
            s.SetContentsOfCell("AE2", "90.5");
            s.SetContentsOfCell("f3", "= 4 * 4"); 
            Assert.AreEqual("goat", s.GetCellContents("y67"));
            Assert.AreEqual(90.5, s.GetCellContents("AE2"));
            Assert.AreEqual("4*4", s.GetCellContents("f3").ToString());
        }

        /// <summary>
        /// See if it will get the correct names of cells 
        /// </summary>
        [TestMethod()]
        public void GetNamesTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("t6", "1");
            s.SetContentsOfCell("err5", "sheep");
            s.SetContentsOfCell("ces1994", "= 8/8");
            HashSet<string> test = new HashSet<string>() { "t6", "err5", "ces1994" };
            HashSet<string> names = new HashSet<string>(s.GetNamesOfAllNonemptyCells());                  
            Assert.AreEqual(test.ToString(),names.ToString()); 
        }

        /// <summary>
        /// See if it will return an empty ienumerable if there is nothing in the cells.  
        /// </summary>
        [TestMethod()]
        public void GetNamesTest2()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            HashSet<string> test = new HashSet<string>();
            HashSet<string> names = new HashSet<string>(s.GetNamesOfAllNonemptyCells());
            Assert.AreEqual(test.ToString(), names.ToString());
        }

    }
    






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




    /// <summary>
    ///This is a test class for SpreadsheetTest and is intended
    ///to contain all SpreadsheetTest Unit Tests
    ///</summary>
    [TestClass()]
    public class GradingTests
    {


        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Additional test attributes
        // 
        //You can use the following additional attributes as you write your tests:
        //
        //Use ClassInitialize to run code before running the first test in the class
        //[ClassInitialize()]
        //public static void MyClassInitialize(TestContext testContext)
        //{
        //}
        //
        //Use ClassCleanup to run code after all tests in a class have run
        //[ClassCleanup()]
        //public static void MyClassCleanup()
        //{
        //}
        //
        //Use TestInitialize to run code before running each test
        //[TestInitialize()]
        //public void MyTestInitialize()
        //{
        //}
        //
        //Use TestCleanup to run code after each test has run
        //[TestCleanup()]
        //public void MyTestCleanup()
        //{
        //}
        //
        #endregion

        // Verifies cells and their values, which must alternate.
        public void VV(AbstractSpreadsheet sheet, params object[] constraints)
        {
            for (int i = 0; i < constraints.Length; i += 2)
            {
                if (constraints[i + 1] is double)
                {
                    Assert.AreEqual((double)constraints[i + 1], (double)sheet.GetCellValue((string)constraints[i]), 1e-9);
                }
                else
                {
                    Assert.AreEqual(constraints[i + 1], sheet.GetCellValue((string)constraints[i]));
                }
            }
        }


        // For setting a spreadsheet cell.
        public IEnumerable<string> Set(AbstractSpreadsheet sheet, string name, string contents)
        {
            List<string> result = new List<string>(sheet.SetContentsOfCell(name, contents));
            return result;
        }

        // Tests IsValid
        [TestMethod()]
        public void IsValidTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("A1", "x");
        }

        [TestMethod()]
        [ExpectedException(typeof(InvalidNameException))]
        public void IsValidTest2()
        {
            AbstractSpreadsheet ss = new Spreadsheet(s => s[0] != 'A', s => s, "");
            ss.SetContentsOfCell("A1", "x");
        }

        [TestMethod()]
        public void IsValidTest3()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("B1", "= A1 + C1");
        }

        [TestMethod()]
        [ExpectedException(typeof(FormulaFormatException))]
        public void IsValidTest4()
        {
            AbstractSpreadsheet ss = new Spreadsheet(s => s[0] != 'A', s => s, "");
            ss.SetContentsOfCell("B1", "= A1 + C1");
        }

        // Tests Normalize
        [TestMethod()]
        public void NormalizeTest1()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("B1", "hello");
            Assert.AreEqual("", s.GetCellContents("b1"));
        }

        [TestMethod()]
        public void NormalizeTest2() 
        {
            AbstractSpreadsheet ss = new Spreadsheet(s => true, s => s.ToUpper(), "");
            ss.SetContentsOfCell("B1", "hello");
            Assert.AreEqual("hello", ss.GetCellContents("b1"));
        }

        [TestMethod()]
        public void NormalizeTest3()
        {
            AbstractSpreadsheet s = new Spreadsheet();
            s.SetContentsOfCell("a1", "5");
            s.SetContentsOfCell("A1", "6");
            s.SetContentsOfCell("B1", "= a1");
            Assert.AreEqual(5.0, (double)s.GetCellValue("B1"), 1e-9);
        }

        [TestMethod()]
        public void NormalizeTest4()
        {
            AbstractSpreadsheet ss = new Spreadsheet(s => true, s => s.ToUpper(), "");
            ss.SetContentsOfCell("a1", "5");
            ss.SetContentsOfCell("A1", "6");
            ss.SetContentsOfCell("B1", "= a1");
            Assert.AreEqual(6.0, (double)ss.GetCellValue("B1"), 1e-9);
        }

        // Simple tests
        [TestMethod()]
        public void EmptySheet()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            VV(ss, "A1", "");
        }


        [TestMethod()]
        public void OneString()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            OneString(ss);
        }

        public void OneString(AbstractSpreadsheet ss)
        {
            Set(ss, "B1", "hello");
            VV(ss, "B1", "hello");
        }


        [TestMethod()]
        public void OneNumber()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            OneNumber(ss);
        }

        public void OneNumber(AbstractSpreadsheet ss)
        {
            Set(ss, "C1", "17.5");
            VV(ss, "C1", 17.5);
        }


        [TestMethod()]
        public void OneFormula()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            OneFormula(ss);
        }

        public void OneFormula(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "4.1");
            Set(ss, "B1", "5.2");
            Set(ss, "C1", "= A1+B1");
            VV(ss, "A1", 4.1, "B1", 5.2, "C1", 9.3);
        }


        [TestMethod()]
        public void Changed()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            Assert.IsFalse(ss.Changed);
            Set(ss, "C1", "17.5");
            Assert.IsTrue(ss.Changed);
        }


        [TestMethod()]
        public void DivisionByZero1()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            DivisionByZero1(ss);
        }

        public void DivisionByZero1(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "4.1");
            Set(ss, "B1", "0.0");
            Set(ss, "C1", "= A1 / B1");
            Assert.IsInstanceOfType(ss.GetCellValue("C1"), typeof(FormulaError));
        }

        [TestMethod()]
        public void DivisionByZero2()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            DivisionByZero2(ss);
        }

        public void DivisionByZero2(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "5.0");
            Set(ss, "A3", "= A1 / 0.0");
            Assert.IsInstanceOfType(ss.GetCellValue("A3"), typeof(FormulaError));
        }



        [TestMethod()]
        public void EmptyArgument()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            EmptyArgument(ss);
        }

        public void EmptyArgument(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "4.1");
            Set(ss, "C1", "= A1 + B1");
            Assert.IsInstanceOfType(ss.GetCellValue("C1"), typeof(FormulaError));
        }


        [TestMethod()]
        public void StringArgument()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            StringArgument(ss);
        }

        public void StringArgument(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "4.1");
            Set(ss, "B1", "hello");
            Set(ss, "C1", "= A1 + B1");
            Assert.IsInstanceOfType(ss.GetCellValue("C1"), typeof(FormulaError));
        }


        [TestMethod()]
        public void ErrorArgument()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            ErrorArgument(ss);
        }

        public void ErrorArgument(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "4.1");
            Set(ss, "B1", "");
            Set(ss, "C1", "= A1 + B1");
            Set(ss, "D1", "= C1");
            Assert.IsInstanceOfType(ss.GetCellValue("D1"), typeof(FormulaError));
        }


        [TestMethod()]
        public void NumberFormula1()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            NumberFormula1(ss);
        }

        public void NumberFormula1(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "4.1");
            Set(ss, "C1", "= A1 + 4.2");
            VV(ss, "C1", 8.3);
        }


        [TestMethod()]
        public void NumberFormula2()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            NumberFormula2(ss);
        }

        public void NumberFormula2(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "= 4.6");
            VV(ss, "A1", 4.6);
        }


        // Repeats the simple tests all together
        [TestMethod()]
        public void RepeatSimpleTests()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            Set(ss, "A1", "17.32");
            Set(ss, "B1", "This is a test");
            Set(ss, "C1", "= A1+B1");
            OneString(ss);
            OneNumber(ss);
            OneFormula(ss);
            DivisionByZero1(ss);
            DivisionByZero2(ss);
            StringArgument(ss);
            ErrorArgument(ss);
            NumberFormula1(ss);
            NumberFormula2(ss);
        }

        // Four kinds of formulas
        [TestMethod()]
        public void Formulas()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            Formulas(ss);
        }

        public void Formulas(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "4.4");
            Set(ss, "B1", "2.2");
            Set(ss, "C1", "= A1 + B1");
            Set(ss, "D1", "= A1 - B1");
            Set(ss, "E1", "= A1 * B1");
            Set(ss, "F1", "= A1 / B1");
            VV(ss, "C1", 6.6, "D1", 2.2, "E1", 4.4 * 2.2, "F1", 2.0);
        }

        [TestMethod()]
        public void Formulasa()
        {
            Formulas();
        }

        [TestMethod()]
        public void Formulasb()
        {
            Formulas();
        }


        // Are multiple spreadsheets supported?
        [TestMethod()]
        public void Multiple()
        {
            AbstractSpreadsheet s1 = new Spreadsheet();
            AbstractSpreadsheet s2 = new Spreadsheet();
            Set(s1, "X1", "hello");
            Set(s2, "X1", "goodbye");
            VV(s1, "X1", "hello");
            VV(s2, "X1", "goodbye");
        }

        [TestMethod()]
        public void Multiplea()
        {
            Multiple();
        }

        [TestMethod()]
        public void Multipleb()
        {
            Multiple();
        }

        [TestMethod()]
        public void Multiplec()
        {
            Multiple();
        }

        // Reading/writing spreadsheets
        [TestMethod()]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void SaveTest1()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            ss.Save("q:\\missing\\save.txt");
        }

        [TestMethod()]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void SaveTest2()
        {
            AbstractSpreadsheet ss = new Spreadsheet("q:\\missing\\save.txt", s => true, s => s, "");
        }

        [TestMethod()]
        public void SaveTest3()
        {
            AbstractSpreadsheet s1 = new Spreadsheet();
            Set(s1, "A1", "hello");
            s1.Save("save1.txt");
            s1 = new Spreadsheet("save1.txt", s => true, s => s, "default");
            Assert.AreEqual("hello", s1.GetCellContents("A1"));
        }

        [TestMethod()]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void SaveTest4()
        {
            using (StreamWriter writer = new StreamWriter("save2.txt"))
            {
                writer.WriteLine("This");
                writer.WriteLine("is");
                writer.WriteLine("a");
                writer.WriteLine("test!");
            }
            AbstractSpreadsheet ss = new Spreadsheet("save2.txt", s => true, s => s, "");
        }

        [TestMethod()]
        [ExpectedException(typeof(SpreadsheetReadWriteException))]
        public void SaveTest5()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            ss.Save("save3.txt");
            ss = new Spreadsheet("save3.txt", s => true, s => s, "version");
        }

        [TestMethod()]
        public void SaveTest6()
        {
            AbstractSpreadsheet ss = new Spreadsheet(s => true, s => s, "hello");
            ss.Save("save4.txt");
            Assert.AreEqual("hello", new Spreadsheet().GetSavedVersion("save4.txt"));
        }

        
        [TestMethod()]
        public void SaveTest7()
        {
            using (XmlWriter writer = XmlWriter.Create("save5.txt"))
            {
                writer.WriteStartDocument();
                writer.WriteStartElement("spreadsheet");
                writer.WriteAttributeString("version", "");

                writer.WriteStartElement("cell");
                writer.WriteElementString("name", "A1");
                writer.WriteElementString("contents", "hello");
                writer.WriteEndElement();

                writer.WriteStartElement("cell");
                writer.WriteElementString("name", "A2");
                writer.WriteElementString("contents", "5.0");
                writer.WriteEndElement();

                writer.WriteStartElement("cell");
                writer.WriteElementString("name", "A3");
                writer.WriteElementString("contents", "4.0");
                writer.WriteEndElement();

                writer.WriteStartElement("cell");
                writer.WriteElementString("name", "A4");
                writer.WriteElementString("contents", "= A2 + A3");
                writer.WriteEndElement();

                writer.WriteEndElement();
                writer.WriteEndDocument();
            }
            AbstractSpreadsheet ss = new Spreadsheet("save5.txt", s => true, s => s, "");
            VV(ss, "A1", "hello", "A2", 5.0, "A3", 4.0, "A4", 9.0);
        }

        [TestMethod()]
        public void SaveTest8()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            Set(ss, "A1", "hello");
            Set(ss, "A2", "5.0");
            Set(ss, "A3", "4.0");
            Set(ss, "A4", "= A2 + A3");
            ss.Save("save6.txt");
            using (XmlReader reader = XmlReader.Create("save6.txt"))
            {
                int spreadsheetCount = 0;
                int cellCount = 0;
                bool A1 = false;
                bool A2 = false;
                bool A3 = false;
                bool A4 = false;
                string name = null;
                string contents = null;

                while (reader.Read())
                {
                    if (reader.IsStartElement())
                    {
                        switch (reader.Name)
                        {
                            case "spreadsheet":
                                Assert.AreEqual("default", reader["version"]);
                                spreadsheetCount++;
                                break;

                            case "cell":
                                cellCount++;
                                break;

                            case "name":
                                reader.Read();
                                name = reader.Value;
                                break;

                            case "contents":
                                reader.Read();
                                contents = reader.Value;
                                break;
                        }
                    }
                    else
                    {
                        switch (reader.Name)
                        {
                            case "cell":
                                if (name.Equals("A1")) { Assert.AreEqual("hello", contents); A1 = true; }
                                else if (name.Equals("A2")) { Assert.AreEqual(5.0, Double.Parse(contents), 1e-9); A2 = true; }
                                else if (name.Equals("A3")) { Assert.AreEqual(4.0, Double.Parse(contents), 1e-9); A3 = true; }
                                else if (name.Equals("A4")) { contents = contents.Replace(" ", ""); Assert.AreEqual("=A2+A3", contents); A4 = true; }
                                else Assert.Fail();
                                break;
                        }
                    }
                }
                Assert.AreEqual(1, spreadsheetCount);
                Assert.AreEqual(4, cellCount);
                Assert.IsTrue(A1);
                Assert.IsTrue(A2);
                Assert.IsTrue(A3);
                Assert.IsTrue(A4);
            }
        }
        

        // Fun with formulas
        [TestMethod()]
        public void Formula1()
        {
            Formula1(new Spreadsheet());
        }
        public void Formula1(AbstractSpreadsheet ss)
        {
            Set(ss, "a1", "= a2 + a3");
            Set(ss, "a2", "= b1 + b2");
            Assert.IsInstanceOfType(ss.GetCellValue("a1"), typeof(FormulaError));
            Assert.IsInstanceOfType(ss.GetCellValue("a2"), typeof(FormulaError));
            Set(ss, "a3", "5.0");
            Set(ss, "b1", "2.0");
            Set(ss, "b2", "3.0");
            VV(ss, "a1", 10.0, "a2", 5.0);
            Set(ss, "b2", "4.0");
            VV(ss, "a1", 11.0, "a2", 6.0);
        }

        [TestMethod()]
        public void Formula2()
        {
            Formula2(new Spreadsheet());
        }
        public void Formula2(AbstractSpreadsheet ss)
        {
            Set(ss, "a1", "= a2 + a3");
            Set(ss, "a2", "= a3");
            Set(ss, "a3", "6.0");
            VV(ss, "a1", 12.0, "a2", 6.0, "a3", 6.0);
            Set(ss, "a3", "5.0");
            VV(ss, "a1", 10.0, "a2", 5.0, "a3", 5.0);
        }

        [TestMethod()]
        public void Formula3()
        {
            Formula3(new Spreadsheet());
        }
        public void Formula3(AbstractSpreadsheet ss)
        {
            Set(ss, "a1", "= a3 + a5");
            Set(ss, "a2", "= a5 + a4");
            Set(ss, "a3", "= a5");
            Set(ss, "a4", "= a5");
            Set(ss, "a5", "9.0");
            VV(ss, "a1", 18.0);
            VV(ss, "a2", 18.0);
            Set(ss, "a5", "8.0");
            VV(ss, "a1", 16.0);
            VV(ss, "a2", 16.0);
        }

        [TestMethod()]
        public void Formula4()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            Formula1(ss);
            Formula2(ss);
            Formula3(ss);
        }

        [TestMethod()]
        public void Formula4a()
        {
            Formula4();
        }


        [TestMethod()]
        public void MediumSheet()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            MediumSheet(ss);
        }

        public void MediumSheet(AbstractSpreadsheet ss)
        {
            Set(ss, "A1", "1.0");
            Set(ss, "A2", "2.0");
            Set(ss, "A3", "3.0");
            Set(ss, "A4", "4.0");
            Set(ss, "B1", "= A1 + A2");
            Set(ss, "B2", "= A3 * A4");
            Set(ss, "C1", "= B1 + B2");
            VV(ss, "A1", 1.0, "A2", 2.0, "A3", 3.0, "A4", 4.0, "B1", 3.0, "B2", 12.0, "C1", 15.0);
            Set(ss, "A1", "2.0");
            VV(ss, "A1", 2.0, "A2", 2.0, "A3", 3.0, "A4", 4.0, "B1", 4.0, "B2", 12.0, "C1", 16.0);
            Set(ss, "B1", "= A1 / A2");
            VV(ss, "A1", 2.0, "A2", 2.0, "A3", 3.0, "A4", 4.0, "B1", 1.0, "B2", 12.0, "C1", 13.0);
        }

        [TestMethod()]
        public void MediumSheeta()
        {
            MediumSheet();
        }


        [TestMethod()]
        public void MediumSave()
        {
            AbstractSpreadsheet ss = new Spreadsheet();
            MediumSheet(ss);
            ss.Save("save7.txt");
            ss = new Spreadsheet("save7.txt", s => true, s => s, "default");
            VV(ss, "A1", 2.0, "A2", 2.0, "A3", 3.0, "A4", 4.0, "B1", 1.0, "B2", 12.0, "C1", 13.0);
        }

        [TestMethod()]
        public void MediumSavea()
        {
            MediumSave();
        }


        // A long chained formula.  If this doesn't finish within 60 seconds, it fails.
        [TestMethod()]
        public void LongFormulaTest()
        {
            object result = "";
            Thread t = new Thread(() => LongFormulaHelper(out result));
            t.Start();
            t.Join(60 * 1000);
            if (t.IsAlive)
            {
                t.Abort();
                Assert.Fail("Computation took longer than 60 seconds");
            }
            Assert.AreEqual("ok", result);
        }

        public void LongFormulaHelper(out object result)
        {
            try
            {
                AbstractSpreadsheet s = new Spreadsheet();
                s.SetContentsOfCell("sum1", "= a1 + a2");
                int i;
                int depth = 49;
                for (i = 1; i <= depth * 2; i += 2)
                {
                    s.SetContentsOfCell("a" + i, "= a" + (i + 2) + " + a" + (i + 3));
                    s.SetContentsOfCell("a" + (i + 1), "= a" + (i + 2) + "+ a" + (i + 3));
                }
                s.SetContentsOfCell("a" + i, "1");
                s.SetContentsOfCell("a" + (i + 1), "1");
                Assert.AreEqual(Math.Pow(2, depth + 1), (double)s.GetCellValue("sum1"), 1.0);
                s.SetContentsOfCell("a" + i, "0");
                Assert.AreEqual(Math.Pow(2, depth), (double)s.GetCellValue("sum1"), 1.0);
                s.SetContentsOfCell("a" + (i + 1), "0");
                Assert.AreEqual(0.0, (double)s.GetCellValue("sum1"), 0.1);
                result = "ok";
            }
            catch (Exception e)
            {
                result = e;
            }
        }

    }
}
