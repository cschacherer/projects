#include "venus.h"

Venus::Venus()
{
   MakeSouvenirs();
}

void Venus::MakeSouvenirs()
{
    //Sample from the magnetic field
    std::string description1 = "We detect you are in the\n magnetic field you\n should pick it up so\n that "
                           "we can figure\n what it is back home";
    v1 = Souvenir("Magnetic Field Sample", ":/venusItems/venusMagneticFieldSample.png", description1, true);

    //Sample from rocky mantle
    std::string description2 = "This looks like a sample\n from the rocky mantle of\n the planet. You "
                           "should get a\n sample";
    v2 = Souvenir("Rocky Mantle Sample", ":/venusItems/venusRockyMantle.png", description2, true);

    //Dirt
    std::string description3 = "This is only dirt nothing\n seems special about this\n "
                           "we dont need a sample.";
    v3 = Souvenir("Dirt", ":/venusItems/venusDirt.png", description3, false);
}
