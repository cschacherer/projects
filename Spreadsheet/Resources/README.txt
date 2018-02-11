"I certify that the work to create this GUI was done entirely by myself and my partner - Conner Schacherer, Faith Oladele" 

11/4/15
For this project we created a Spreadsheet GUI.  We had trouble implementing it at first and understanding how the GUI thread worked 
but as we worked on the assignment more we gained more knowledge about it and how it worked.  In our Spreadsheet, a user can enter in 
a double, string or formula in a cell by writing in the Content textbox and pressing Enter.  That is the only way to enter data into
our spreadsheet, we decided not to add a button to add content because we figured most people would just use Enter.  Also for entering
content, a formula must be added by putting an equals sign in front of it. Also, for adding a formula with cells in it, putting "= a1" 
is the same as "= A1".  

The Value text box shows the string or double value of the contents, the cell also shows the value of the contents as well. If you 
change the contents of a cell that is part of a formula of another cell, the cells will update to reflect the new value.

We also have a File menu that will show a New, Open, Save, or Close that will help the user.  If the user creates a new Form and 
closes the original, the new Form will not go away.  We also have a Help form to give instructions and answer any expected questions. 

We tried to do more GUI testing but we kept running into errors so we don't have as many as we would like.  For some reason if we 
entered a formula into our Content text box, the GUI testing code wouldn't register that we hit Enter to set the selected cell 
to that value so would have to manually go in and change that code which would take a lot of time.  Also anytime we clicked 
on something other than the GUI spreadsheet, like an OpenFileDialog or a MessageBox, it would create an error.  Also we had 
more tests but I ended up having to change the Target Framework of our Application to a higher version which broke all of 
our previous GUI tests.  So we wish we could have tested on the GUI tester more, but we did do a lot of manual testing to
make sure our spreadsheet worked how it was supposed too.  

Special Features: 
We changed the colors of the spreadsheet and added icons to the File menu and Help button to make it look more professional 
and aesthetically pleasing.  Also, if you select a cell, it will become highlighted in a dark blue to help the user see what cell 
is selected.  Also the cell that the mouse is hovering over will be a highlighted.  We also added hot keys to mimic clicking on New, 
Open, Save and Help.  New Form = Ctrl and N, Open Form = Ctrl and O, Save Form = Ctrl and S, Help = Ctrl and H, Close = Ctrl and C.
We also put our spreadsheet into an installer so you could load it on someone's computer.  We also added a function to where if you press "Delete", 
whatever cell is highlighted will be deleted, unless it causes an error, in that case the cell contents will stay the same.  We also
created a new Form for our Help section.  We also created an installer for our spreadsheet, but we did have a malfunction where it 
wouldn't let us use an icon for our installer.  