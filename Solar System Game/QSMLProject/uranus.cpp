#include "uranus.h"

#include <iostream>

Uranus::Uranus()
{
      //A sample from the core
      std::string description1 = "It looks like this is\n a piece of the planets \ncore";
      u1 = Souvenir("Core Sample", ":/uranusItems/uranusCore.png", description1, true);

      //Unidentified object
      std::string description2 = "Hmm... we dont know what\n this can be. It could be\n interesting to bring back\n home.";
      u2 = Souvenir("Unidentified Object", ":/uranusItems/uranusLiquidHydrogen.png", description2, true);

      //Ice Particles
      std::string description3 = "These are just common ice\n particles";
      u3 = Souvenir("Ice Particles", ":/uranusItems/uranusIceParticles copy 3.png", description3, false);

}
