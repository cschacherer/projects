#include "mercury.h"
#include <iostream>

Mercury::Mercury()
{
    MakeSouvenirs();
}

void Mercury::MakeSouvenirs()
{
    //Sample of the Mantle
    std::string description1 = "This is a piece of the\n mantle of the planet\n that has "
                           "chipped off\n you should keep\n it to analyse";
    m1 = Souvenir("Mantle Sample", ":/mercuryItems/mercuryMantle.png", description1, true);


    //Sample of the metal inner core
    std::string description2 = "It seems like this is\n a piece of metal of the\n planets core, "
                           "you should\n keep it to analyse";
    m2 = Souvenir("Metal Core Sample", ":/mercuryItems/mercuryMetalCore.png", description2, true);

    //Dirt
    std::string description5 = "This is only dirt nothing\n seems special about this "
                           "we \ndont need a sample.";
    m3 = Souvenir("Dirt", ":/mercuryItems/mercuryDirt.png", description5, false);


    //Sample of Outer Core
    std::string description4 = "This looks like a piece\n from the planets outer core "
                           "you should\n keep is to analyse";
    m4 = Souvenir("Outer Core Sample", ":/mercuryItems/moonCrustSample.png", description4, true);
}
