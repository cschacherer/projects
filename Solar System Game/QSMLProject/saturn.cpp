#include "saturn.h"

#include <iostream>

Saturn::Saturn()
{
    //A sample from the core
    std::string description1 = "It looks like this\n is a piese of the planets\n core.";
    s1 = Souvenir("Core Sample", ":/saturnItems/saturnCore.png", description1, true);

    //Unidentified object
    std::string description2 = "Hmm... we dont know what\n this can be.";
    s2 = Souvenir("Unidentified Object", ":/saturnItems/saturnLiquidHydrogen.png", description2, true);

    //Ice Particles
    std::string description3 = "This is just ice.";
    s3 = Souvenir("Ice Particles", ":/saturnItems/saturnIceParticles copy 4.png", description3, false);

}
