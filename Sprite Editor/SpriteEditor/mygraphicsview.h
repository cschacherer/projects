#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H


#include <QMouseEvent>
#include <QGraphicsView>
#include <QObject>
#include <iostream>

#include <QGraphicsEffect>

class MyGraphicsView : public QGraphicsView   //, public QObject
{
    Q_OBJECT
public:
    MyGraphicsView(int);

    bool selected;
    int placement;

    void mouseReleaseEvent(QMouseEvent *event);
    ~MyGraphicsView();

    QGraphicsColorizeEffect *highlight;

    void DestroyHighlight();

signals:
    void SelectionSignal(int);
};


#endif // MYGRAPHICSVIEW_H
