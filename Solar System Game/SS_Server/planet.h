#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <souvenir.h>
#include <vector>

class Planet
{
public:
    Planet(std::string, int);
    std::string name;
    std::vector<Souvenir > objects;
    int level;
};

#endif // PLANET_H
