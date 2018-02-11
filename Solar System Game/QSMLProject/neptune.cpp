#include "neptune.h"
#include <souvenir.h>
#include <iostream>

Neptune::Neptune()
{
    NeptuneSouvenirs();
}

void Neptune::NeptuneSouvenirs()
{
    // Core sample
    std::string neptuneDescription1 = "It looks like this\n is a piece of the planets\n core, you should take\n a sample of this";
    n1 = Souvenir("Core Sample", ":/neptuneItems/neptuneCore.png", neptuneDescription1, true);

    //Unidentified object
    std::string neptuneDescription2 = "Hmm... we dont know\n what this can be. Great\n find you should definately\n bring a sample back\n home";
    n2 = Souvenir("Unidentified Object", ":/neptuneItems/neptuneIceParticles copy 2.png", neptuneDescription2, true);

    //Ice Particles
     std::string neptuneDescription3 = "This is just ice,\n we dont need a sample\n of this.";
     n3 =  Souvenir("Ice Particles", ":/neptuneItems/neptuneLiquidHydrogen.png", neptuneDescription3, false);


}
