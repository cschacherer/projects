#ifndef SOUVENIR_H
#define SOUVENIR_H
#include <QString>
//#include <QImage>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <iostream>

class Souvenir :  public QObject, public QGraphicsPixmapItem

{
   Q_OBJECT
public:
   explicit Souvenir(std::string name, std::string souvenir, std::string description, bool important);
    Souvenir ();
    Souvenir(Souvenir const &souv);
    Souvenir& operator=(const Souvenir &a);
   ~Souvenir();

    QGraphicsPixmapItem* pixmapItem;

    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);



    //The name of the souvenir
    std::string souvenirName;
    //The actual image of the souvenir
    std::string souvenirImage;
    //Description of what the item is
    std::string souvenirDescription;
    //Checks if the item is worth keeping or not
    bool itemImportant;


signals:
    void HoverTextSignal(std::string, std::string);

};


//QVector<Souvenir> classes;
//classes.push_back(Souvenir(1.0));
//classes.push_back(Souvenir(2.0));
//classes.push_back(Souvenir(3.0));

#endif // SOUVENIR_H


