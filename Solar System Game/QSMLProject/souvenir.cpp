#include "souvenir.h"
#include <QGraphicsSceneHoverEvent>

Souvenir::Souvenir(std::string name, std::string souvenir, std::string description, bool important)
{
   souvenirName = name;
   souvenirImage = souvenir;
   souvenirDescription = description;
   itemImportant = important;
}

Souvenir::Souvenir()
{
   souvenirName = "";
   souvenirImage = "";
   souvenirDescription = "";
   itemImportant = false;
}

Souvenir::Souvenir(Souvenir const &souv)
{

}

Souvenir& Souvenir::operator=(const Souvenir &a)
{
    this->souvenirName = a.souvenirName;
    this->souvenirImage = a.souvenirImage;
    this->souvenirDescription = a.souvenirDescription;
    this->itemImportant = a.itemImportant;
}

Souvenir::~Souvenir()
{
   //delete ;
}


void Souvenir::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    emit HoverTextSignal(souvenirName, souvenirDescription);
}

//QString Souvenir::getSouvenirName()
//{
//   return souvenirName;
//}

//QString Souvenir::getImagePath() const
//{
//   return souvenirImage;
//}

//QString Souvenir::getSouvenirDescription()
//{
//   return souvenirDescription;
//}

//bool Souvenir::getIfImportant()
//{
//   return itemImportant;
//}


