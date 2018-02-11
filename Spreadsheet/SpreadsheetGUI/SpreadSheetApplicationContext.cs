using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SS
{
    public class SpreadSheetApplicationContext : ApplicationContext
    {

        private int SheetCount = 0;

        // Use as singleton
        private static SpreadSheetApplicationContext appContext;

        /// <summary>
        /// Private constructor
        /// </summary>
        private SpreadSheetApplicationContext()
        {
        }

        /// <summary>
        /// Returns the one DemoApplicationContext.
        /// </summary>
        public static SpreadSheetApplicationContext getAppContext()
        {
            if (appContext == null)
            {
                appContext = new SpreadSheetApplicationContext();
            }
            return appContext;
        }


        /// <summary>
        /// Display a new Spreadsheet Form
        /// </summary>
        /// <param name="form"></param>
        public void DisplayForm(Form form)
        {
            SheetCount++;

            form.FormClosed += (o, e) => { if (--SheetCount <= 0) ExitThread(); };

            form.Show();
        }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            SpreadSheetApplicationContext appContext = SpreadSheetApplicationContext.getAppContext();
            appContext.DisplayForm(new Form1());
            Application.Run(appContext);
        }
    }
}
