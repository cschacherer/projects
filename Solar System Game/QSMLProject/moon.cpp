#include "moon.h"
#include <QDebug>

Moon::Moon()
{
    //Sample from the Near side
    std::string description1 = "This is a near\n side sample of\n the moon."
                               " It\n is the side\n of the moon\n that we can\n see, "
                               "you\n can tell that\n you are in\n the near side\n beacuse "
                               "this rock\n is smoother then\n that of the far\n side.";
    m1 = Souvenir("Near side sample", ":/moonItems/moonNearSide.png", description1, true);


    //Sample from the Far side
    std::string description2 = "This is a sample\n of the far\n side of the moon.\n "
                               "It's the side\n of the moon\n that is facing\n away "
                               "from Earth\n if you look at\n the rock it is\n bumpier"
                               " then the\n niear side rocks";
    m2 = Souvenir("Far side sample", ":/moonItems/moonFarSide.png", description2, true);


    //Sample of Maria
    std::string description3 = "This componant is\n called 'maria' you\n should "
                           "it is\n present on the\n near side of\n the moon";
    m3 = Souvenir("Maria sample", ":/moonItems/moonMaria.png", description3, true);

    //Sample of Dirt
    std::string description4 = "This is only\n dirt we dont\n need a sample\n of this";
    m4 = Souvenir("Dirt", ":/moonItems/moonDirt.png", description4, false);

    //The Flag
    std::string description5 = "This is the flag\n that was set\n here by Neil\n Armstrong"
                               " and Buzz\n Aldrin the first\n time we came\n to the moon\n"
                               " in 1969.";
    m5 = Souvenir("American Flag", ":/moonItems/moonFlag.png", description5, false);
}
