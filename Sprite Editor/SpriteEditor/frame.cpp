#include "frame.h"
#include <QColor>
#include <QRgb>
#include <QDebug>
#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QString>

/**
 * @brief Frame::Frame constructor
 */
Frame::Frame()
{
    frameSize = 8;
    SetBackground(frameSize);
    firstImage = QImage(512, 512, QImage::Format_ARGB32);
    firstImage.fill(QColor(0, 0, 0,0));
    imageFrames.push_back(firstImage);
}

void Frame::AddFrame()
{
    QImage newFrame = QImage(512, 512, QImage::Format_ARGB32);
    newFrame.fill(QColor(0, 0, 0, 0));
    imageFrames.push_back(newFrame);
}

void Frame::DeleteFrame(int index)
{
    imageFrames.erase(imageFrames.begin()+index);
}

void Frame::Save()
{

}

void Frame::FramesToGif()
{

}

void Frame::MakeGrid(int pixelSize)
{
    SetBackground(pixelSize);
}

void Frame::SetBackground(int size)
{
    int increment = 512.0/size;
    background = QImage(512, 512, QImage::Format_ARGB32);
    background.fill(QColor(0, 0, 0,0));

    backgroundPix = QPixmap::fromImage(background);
    backgroundScene = new QGraphicsScene();
    backgroundScene ->addPixmap(backgroundPix);
}

void Frame::SetGridSize(QString gridSize)
{
    QStringList split = gridSize.split("x");
    if (split[0] == "")
        frameSize = 8;
    else
        frameSize = split[0].toInt();
std::cout << frameSize;

}
