#include "jupiter.h"
#include <souvenir.h>
#include <iostream>

Jupiter::Jupiter()
{
    JupiterSouvenirs();
}

void Jupiter::JupiterSouvenirs()
{
    //A sample from the core
    std::string description1 = "It looks like this is\n a piese of the\n planets core, you\n should take a sample\n of this";
    j1 = Souvenir("Core Sample", ":/jupiterItems/jupiterCore.png", description1, true);

    //Unidentified Object
    std::string description2 = "Hmm... we dont know\n what this can be.\n Great find you should\n definately bring a\n sample back home";
    j2 = Souvenir("Unidentified Object", ":/jupiterItems/jupiterLiquidMetalicHydrogen.png", description2, true);

    //Ice particles
    std::string description3 = "This is just ice,\n we dont need a sample\n of this.";
    j3 = Souvenir("Ice Particles", ":/jupiterItems/jupiterIceParticles.png", description3, false);

}
