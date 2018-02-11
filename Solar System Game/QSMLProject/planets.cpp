#include "planets.h"
#include "QDebug"
Planets::Planets()
{
    planetGravityList << -9.81 << -1.622 << -27 <<-3.7 << -8.87 << -3.711 << -24.79 << -10.44 << -8.69 << -11.15 << -0.62;

    planetNum = 1;
    planetImages.push_back(":/images/Earth.jpg");
    planetImages.push_back(":/images/moon.jpg");
    planetImages.push_back(":/images/sun.jpg");
    planetImages.push_back(":/images/mercury.png");
    planetImages.push_back(":/images/venus.jpg");
    planetImages.push_back(":/images/mar.jpg");
    planetImages.push_back(":/images/jupiter.png");
    planetImages.push_back(":/images/saturn.png");
    planetImages.push_back(":/images/uranus.png");
    planetImages.push_back(":/images/neptune.png");
    planetImages.push_back(":/images/pluto.png");
}

void Planets::mars()
{

}

void Planets::mercury()
{

}

void Planets::venus()
{

}

void Planets::earth()
{

}

void Planets::jupiter()
{

}

void Planets::saturn()
{

}

void Planets::uranus()
{

}

void Planets::neptune()
{

}

void Planets::moon()
{

}

void Planets::pushButton()
{
    qDebug()<<"In planets";
    emit pushButtonVisible();
    qDebug()<<"after";
}

QString Planets::getPlanet()
{

    if(planetNum>10)
    {
        planetNum=0;
    }
    return planetImages[planetNum];

}

void Planets::setPlanetNum()
{
    planetNum++;
}
