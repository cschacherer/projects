#include "mars.h"

#include <iostream>

Mars::Mars()
{
    //Soil Sample
    std::string description1 = "This is some of the planets\n soil";
    m1 = Souvenir("Soil Sample", ":/marsItems/marsSoil.png", description1, true);

    //Iron sample
    std::string description2 = "This looks like iron,\n maybe you should take\n some and compare it\n to Earth's iron";
    m2 = Souvenir("Iron Samples", ":/marsItems/marsIron.png", description2, false);

    //mars rover
    std::string description3 = "This rover is here to\n gather data about Mars.";
    m3 = Souvenir("Mars Rover", ":/marsItems/marsrover.png", description3, false);
}
