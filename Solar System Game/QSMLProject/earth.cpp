#include "earth.h"

Earth::Earth()
{
   //e1(std::string, std::string, std::string, bool);
   MakeSouvenirs();
}

void Earth::MakeSouvenirs()
{
   //Water
   std::string earthDescription1 = " You will not be\n "
                                   "able to survive\n anywhere without\n water!";
   e1 = Souvenir("Water", ":/earthItems/earthWaterBottle.png", earthDescription1, true);

   //Comb
   std::string earthDescription2 = " There is no one\n"
                                   " to look good for\n in space!";
   e2 = Souvenir("Comb", ":/earthItems/earthComb.png", earthDescription2, false);

   //Ipod
   std::string earthDescription3 = " Is listening to music\n really that important? \n"
                                   " You will not have \n time to listen to music \n anyway.";
   e3 = Souvenir("Music", ":/earthItems/earthIPod.png", earthDescription3, false);

   //Cell
   std::string earthDescription4 = " Your cell phone will \n not work in outer space!";
   e4 = Souvenir("Cell Phone", ":/earthItems/earthCell.png", earthDescription4, false);

   // Fire/Lighter
   std::string earthDescription5 = " Causing a fire in \n space is very dangerous!\n";
   e5 = Souvenir("Lighter", ":/earthItems/earthLighter.png", earthDescription5, false);

   //Oxygen
   std::string earthDescription6 = " You need to breathe at all \n times so "
                               "you don't\n to die!";
   e6 = Souvenir("Oxygen", ":/earthItems/earthOxygen.png", earthDescription6, true);

   //Food
   std::string earthDescription7 = "Good thinking, you\n need food to survive!";
   e7 = Souvenir("Food", ":/earthItems/earthFood.png", earthDescription7, true);

   //Solar Powered Fm Reciever Radio
   std::string earthDescription8 = " It is very important that\n you"
                               " communicate with us\n so that we can help you.\n"
                               " We can help guide you\n on what things you\n"
                               " should collect from\n each planet.";
   e8 = Souvenir("Radio", ":/earthItems/earthRadio.png", earthDescription8, true);

   //Space blanket
   std::string earthDescription9 = "Other planets dont have perfect weather for us humans "
                               "like we do hear on our planet earth so it is vital that "
                               "you maintain warm on the nights with special space blanket";
   e9 = Souvenir("Blanket", ":/earthItems/earthSpaceBlanket.png", earthDescription9, true);

}
