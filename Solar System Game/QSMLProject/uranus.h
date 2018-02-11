#ifndef URANUS_H
#define URANUS_H

#include "souvenir.h"
#include <QGraphicsPixmapItem>

class Uranus
{
public:
    Uranus();

    Souvenir u1;
    Souvenir u2;
    Souvenir u3;

    QGraphicsPixmapItem *pixItem;
};

#endif // URANUS_H
