#ifndef FRAME_H
#define FRAME_H
#include <QObject>
#include <QVector>
#include <QImage>
#include <QGraphicsScene>


class Frame : public QObject
{
    Q_OBJECT

public:
    Frame();
    QVector<QImage> imageFrames;
    int framesPerSecond;
    QImage firstImage;
    QImage background;
    QPixmap backgroundPix;
    QGraphicsScene *backgroundScene;
    int frameSize;
    void SetBackground(int size);
    void SetGridSize(QString);

public slots:
    void AddFrame();
    void DeleteFrame(int index);
    void Save();
    void FramesToGif();
    void MakeGrid(int pixelSize);
};

#endif // FRAME_H
