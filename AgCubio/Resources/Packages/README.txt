Partners: Conner Schacherer & Faith Oladele.
Date: November 19th, 2015.
 
"I certify that the work to create this project was done entirely by myself and my partner - Conner Schacherer, Faith Oladele"
 
The Model - World/Cube Class
 
We decided to combine both class as they were both little classes, and then we created a cube dictionary in the  world class to 
store all cubes the server sends and also erase duplicity.
 
NetworkingCode/PreservedSate Class
 
Creating this class at first was a bit of a challenge, because we didn’t understand what the callbacks were meant
for and how to preserve the state. I have to admit the Asynchronous client Socket example on the MSDN was a great help,
and then we slowly begin to understand the concept and of course with help from the TAs as well.
 
Since both the NetworkingCode class is meant to act dependently with no relation to the world class, but updates the
world via the GUI, we created a delegate in the preserve stated as well as in the network class which is accessed in by the view
 
The View
 
This was where we had major issues, at first we couldn’t get the split key to work, the code just breaks without actually 
reaching our split method. Although now it seem to split only on the demo server but not visible in our GUI, we still 
cannot figure out why it was breaking our code, because suddenly it just seem to work, with no major code changes from us.
Well after many other code changes the split seems to break again, and the TAs cannot figure it out either.
 
Scaling was not necessarily hard to implement but we struggled with centering the world and making it rotate centered on the player.
 
We also have issues with the buffering, our theory at the time was maybe there was a lot of people using the server at the 
same time. But that doesn’t seem right because other people’s GUI seems to be working just fine at I presume the regular speed. 
We also ensure that doublebuffer was set to true that didn’t really seem to fix our buffering problems. As of now when we hit
the connect button, we have to resize the window before our world appears.
 
Additionally while consuming food we never really see our player go over the food, it seems like the food is been consumed before
the player reaches the food , and we believe that this might be as a result of our weird buffering. It was advised that we change 
from storing our data in a string to a stringBuilder. We realized that the server is sending the the wrong width, it is not the 
sending the square root of the mass and specified in the instructions
 
Testing:::

We tested our models (cube/world) class to ensure everything was implemented correctly.
 
Added features:
 
We added a quit button to the world GUI to ensure that the player can disconnect gracefully if they decide not to play anymore. 
Although you would have to hover over it with the mouse for the button to be visble once the game begins, we tried using button, 
panels but that didnt fix it, so we decided to use a meny strip instead.

We also added a world background that would give player a sense of moving around the world. We had to come up with a background
that would not distract from the game itself, but also give a pleasant view.

A how to play button was created,  to explained to the users the mechanisms of the game.

A message box that notifies the Users when they die. We attempted to add a play again button, but considering the limited time 
we decided to work on our testing.


**************************************

PS8 - AgCubio Server

Partners: Conner Schacherer & Faith Oladele.

Date: December 3rd, 2015.

**************************************


"I certify that the work to create this project was done entirely by myself and my partner - Conner Schacherer, Faith Oladele"
 
The Model - World/Cube Class
 
In the PS8 we seperated both classes for clarity. 
we add added another constructor and also check for virus in the cube class

In the world class we added variables as specified and then created food, virus and a split method

NetworkingCode/PreservedSate Class

Networkingcode and preservedstated class remained almost the same as the client server except with the addition of the method
specify in the assignment and an additional helper method to check connectivity. We also added a socket state to track every
socket connecting to the network, because unlike the client we need to ensure that every message sent to the client must be 
going back to the correct client.

Server

In the server we had a constructor method where we instantiated all of our dictionaries and other objects. We communicated directly 
with the world and the networking code. Getting the palyer to move was pretty easy after we go the move request from the client. The most 
time spent was on the split request, we relized that we needed the mouse position as well as the player position to split the player. Also 
we had to keep track of every splitted cube and ensured that they move toward the mouse, but every initial split was thrown at a certain 
speed toward the mouse. We had a difficult time getting the time now and making sure the player cubes bounce off of each other, so we had
to check all sides of the player cubes in our hashset to very that they were not over lapping before the due time. Although our splitting 
is not quite there, we sometimes eat ourselves even after we update the world on the merge. We didnt quite get the cubes to recognize 
themselves as a team, even when we have the check to verify. 

The Virus will only split a cube if it has not been splitted yet. Although players should not be able to absorb the virus that is something 
we are aware of and hope to fix in the nearest future.

the update function was quite large and we tried to create several helper methods to reduce it complexity and aids understanding. 
The Attrition was a quick implementation and was done by getting every player mass greater than 200 and have them decrease by raising 
the player mass to 1.2 and dividing by 1000, so that they loose mass according to their mass.


Testing:::

Testing was a bit of a challenge because we could not quit figure out how to test for the networkingcode in time to finish before the due
time.


**************************************

PS9 - AgCubio Database

Partners: Conner Schacherer & Faith Oladele.

Date: December 9th, 2015.

**************************************


"I certify that the work to create this project was done entirely by myself and my partner - Conner Schacherer, Faith Oladele"

:::Server:::

The update function was changed to include the new player stats, which includes adding a new dictionary to keep track of high 
rank. To keep track of the highest rank we get the biggest Mass, we included functionality that allows max mass to be gotten 
from its splitted cubes.

We added two new methods to our server class, one that handles the web browser's connection and the other processes the 
web browser request. 

In earlier version when one player closes their socket, if we try to open a new game the information been sent is so slow
or it would not work, but we fixed it by looping through the socket dictionary to ensure that every socket was connected 
and if it wasnt we would gracefully close the socket and remove the players from the world dictionary and update the world.

:::NetworkingCode:::

We ensured that the connect method could take more than one port.

We also ensure that all data was sent by modifying our sendCallBack method. We did this by checking to ensure everything 
was sent else we call send again and send the remainder of the data.

:::SQLDatabase:::

We made a fucntion to insert a player's stats in the database everytime they either got eaten or closed thier connection.  I 
had trouble at first figuring out how to insert the data correctly because my column names were two words and the database 
didn't recognize them, but once I changed all the column names to one word, our insert fuction worked.  I also created a helper 
method to read the Player database and return an ID based on a name.  

We then created two functions to read the Player database and return all the information and also read the Player database but 
only return information for one name and/or one game.  We added links to make it easier to browse throught the scores.  

We also added CSS styling to make our web page of high scores look more presentable by changing the text color and size and 
adding borders between the tables to make them easier to read.  

:::Model:::

We changed the Cube class to handle the new player stats by adding DateTimes to measure when the cube was created and died and 
then we subtracted the two to put in the Timespan of how long our cube was alive.  We also added a count to measure how much 
food/other players a player ate and another list to keep track of all the names the player ate.  Also a int to hold the player's 
highest rank and a double to hold it's maximum mass achieved.  

:::Testing:::

We tried to test in the cade lab but we ran into some problems, the system just would not let us test and this has been the case
anytime we try using the cade lab machines since the beginning of Agcubio project. This time the error message was
'TE.ProcessHost.Managed[v4.17-S84] has stopped working' and we tried to test and since we could not work around that, we couldnt
tell if the test were working, but we tested our database manually multiple times to make sure that the dead players updates to the 
database.