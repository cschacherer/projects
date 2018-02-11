#include "mygraphicsview.h"

#include <QMouseEvent>
#include <iostream>
#include <QGraphicsEffect>


MyGraphicsView::MyGraphicsView(int framePlacement)
{
    this->setBackgroundBrush(QImage(":/background/BackgroundPicture/background.png"));
    this->setCacheMode(QGraphicsView::CacheBackground);

    selected = false;
    placement = framePlacement;
    highlight = new QGraphicsColorizeEffect;
}

MyGraphicsView::~MyGraphicsView()
{
    delete highlight;
}


void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    selected = true;



//    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect;
//    //color->setColor(QColor(0, 0, 255, 150));
//    opacity ->setOpacity(0.3);
//    this -> setGraphicsEffect(opacity);

//    highlight->setColor(QColor(0, 0, 255, 150));
//    highlight->setStrength(0.8);
//    this -> setGraphicsEffect(highlight);

    emit SelectionSignal(placement);
}


void MyGraphicsView::DestroyHighlight()
{
    delete highlight;
}
