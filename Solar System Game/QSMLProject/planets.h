#ifndef PLANETS_H
#define PLANETS_H
#include <QVector>
#include "souvenir.h"
#include <QObject>
#include <QString>
#include <string>
class Planets: public QObject
{
    Q_OBJECT
public:
    Planets();

    QVector<float> planetGravityList;
    QVector<Souvenir> souvenirs;
    QVector<QString> planetImages;
    void earth();
    void mars();
    void mercury();
    void venus();
    void moon();
    void saturn();
    void jupiter();
    void uranus();
    void neptune();
    void pushButton();
    void setPlanetNum();
    QString getPlanet();

private:
      QVector<Souvenir> marsSouvenirs;
      QVector<Souvenir> moonSouvenirs;
      QVector<Souvenir> mercurySouvenirs;
      QVector<Souvenir> venusSouvenirs;
      QVector<Souvenir> earthSouvenirs;
      QVector<Souvenir> jupiterSouvenirs;
      QVector<Souvenir> saturnSouvenirs;
      QVector<Souvenir> urenusSouvenirs;
      QVector<Souvenir> neptuneSouvenirs;
      int planetNum; //Earth = 0 ... Pluto = 8;
signals:
      void pushButtonVisible();
};

#endif // PLANETS_H
