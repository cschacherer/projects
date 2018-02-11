#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <iostream>
#include <QStyle>
#include <QPushButton>
#include <QDebug>
#include <QScrollArea>
#include <QMouseEvent>
#include <mygraphicsview.h>
#include <QGraphicsOpacityEffect>
#include <QDialog>
#include <QColorDialog>
#include <QPen>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QString>
#include <QFile>
#include <QPainter>
#include <QInputDialog>
#include <sstream>
#include <QMessageBox>
#include <QException>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //select grid size
    QStringList options=(QStringList()<<"8x8"<<"16x16"<<"32x32"<<"64x64");
    QInputDialog inputDialog;
    inputDialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
    inputDialog.setComboBoxItems(options);
    //    inputDialog.setLabelText("Select the size of the drawing grid:");
    //    if(!inputDialog.exec())
    //        this->close();
    bool ok;
    QString text = inputDialog.getItem(this, tr("QInputDialog::getItem()"),tr("Grid:"), options, 0, false, &ok);
    if (ok && !text.isEmpty())
        gridSize=text;

    frames.SetGridSize(gridSize);
    gridSquareSize = 512/frames.frameSize;
    //connect to frames class
    Frame *framesPointer = &frames;

    ui->ImageView->setBackgroundBrush(QImage(":/background/BackgroundPicture/background.png"));
    ui->ImageView->setCacheMode(QGraphicsView::CacheBackground);
    ui->ImageView->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->ImageView->setScene(frames.backgroundScene);
    ui->ImageView->setWindowFlags(Qt::FramelessWindowHint);
    ui->ImageView->setAttribute(Qt::WA_TranslucentBackground);

    ui->Preview->setBackgroundBrush(QImage(":/background/BackgroundPicture/background.png"));
    ui->Preview->setCacheMode(QGraphicsView::CacheBackground);

    //sets up the first frame once the program is opened.
    frameCount = 0;
    brushSize = 1;
    SetFrameView(frameCount);
    framesVector[0]->selected = true;
    selectedFrame = frameCount;

    //set up frame layout
    ui ->FrameLayout -> addWidget(framesVector[frameCount]);
    ui ->FrameScrollArea->show();
    ui ->ScrollWidget->setLayout(ui -> FrameLayout);
    frameCount++;

    //Hot Keys for tool bars
    ui->BrushButton->setShortcut(Qt::Key_D);
    ui->EraseButton->setShortcut(Qt::Key_E);
    ui->FillButton->setShortcut(Qt::Key_F);
    ui->StampButton->setShortcut(Qt::Key_S);
    //Hot Keys for file menu
    ui->actionNew->setShortcut(Qt::CTRL + Qt::Key_N);
    ui->actionOpen->setShortcut(Qt::CTRL + Qt::Key_O);
    ui->actionSave->setShortcut(Qt::CTRL + Qt::Key_S);
    ui->actionClose->setShortcut(Qt::CTRL + Qt::Key_X);

    connect(ui-> BrushButton, &QToolButton::clicked, this, &MainWindow::BrushClicked);
    connect(ui-> AddButton, &QPushButton::clicked, this, &MainWindow::AddFrameClicked);
    connect(ui ->DeleteButton, &QPushButton::clicked, this, &MainWindow::DeleteFrameClicked);
    connect(ui->EraseButton, &QPushButton::clicked, this, &MainWindow::EraseClicked);
    connect(ui->FillButton, &QPushButton::clicked, this, &MainWindow::FillClicked);
    connect(ui->LinesButton, &QPushButton::clicked, this, &MainWindow::LineClicked);
    connect(ui->RectangleButton, &QToolButton::clicked, this, &MainWindow::RectangleClicked);

    //connecting frames and main window
    connect(this, &MainWindow::AddFrameSignal, framesPointer, &Frame::AddFrame);
    connect(this, &MainWindow::DeleteFrameSignal, framesPointer, &Frame::DeleteFrame);

    ui->FPSSlider->setTickInterval(3);
    ui->FPSSlider->setSingleStep(1);
    ui->FPSSlider->setTickPosition(QSlider::TicksBothSides);
    connect(ui->FPSSlider, &QSlider::valueChanged, this, &MainWindow::FPSClicked);

    QGraphicsScene *previewScene = new QGraphicsScene();
    ui->Preview->setScene(previewScene);
    fps = 1000; //initializing our fps to 1
    UpdatePreview();
    hasChanged=false;


    connect(ui->StampButton, &QPushButton::clicked, this, &MainWindow::StampClicked);

    connect(ui->HeartStamp, &QPushButton::clicked, this, &MainWindow::HeartStampSelected);
    connect(ui->DiamondStamp, &QPushButton::clicked, this, &MainWindow::DiamondStampSelected);
    connect(ui->TriangleStamp, &QPushButton::clicked, this, &MainWindow::TriangleStampSelected);

    //Set background colors for color buttons
                   ui->Black->setStyleSheet("background-color:black");
                   ui->Grey->setStyleSheet("background-color:grey");
                   ui->White->setStyleSheet("background-color:white");
                   ui->Blue->setStyleSheet("background-color:blue");
                   ui->Green->setStyleSheet("background-color:green");
                   ui->Yellow->setStyleSheet("background-color:yellow");
                   //ui->Cyan->setStyleSheet("background-color:cyan");
                   ui->Purple->setStyleSheet("background-color:purple");
                   ui->Red->setStyleSheet("background-color:red");

                   //Add plus sign and delete minus sign
                   ui->AddButton->setIcon(QIcon(":/images/Images/add.png"));
                   ui->DeleteButton->setIcon(QIcon(":/images/Images/minus.png"));

                   isBrush = true;
                   //Brush
                   ui->BrushButton->setIcon(QIcon(":/images/Images/brush.png"));
                   ui->BrushButton->setIconSize(QSize(40,40));

                   //Bucket
                   ui->FillButton->setIcon(QIcon(":/images/Images/bucket.png"));
                   ui->FillButton->setIconSize(QSize(40,40));

                   //Eraser
                   ui->EraseButton->setIcon(QIcon(":/images/Images/erase.png"));
                   ui->EraseButton->setIconSize(QSize(40,40));

                   //Line
                   ui->LinesButton->setIcon(QIcon(":/images/Images/line.png"));
                   ui->LinesButton->setIconSize(QSize(40,40));

                   //Square
                   ui->RectangleButton->setIcon(QIcon(":/images/Images/square.png"));
                   ui->RectangleButton->setIconSize(QSize(40,40));

                   //Stamps
                   ui->StampButton->setIcon(QIcon(":/images/Images/stamp.png"));
                   ui->StampButton->setIconSize(QSize(40,40));
                   //Heart
                   ui->HeartStamp->setIcon(QIcon(":/images/Images/heart.png"));
                   ui->HeartStamp->setIconSize(QSize(20,20));
                   //Diamond
                   ui->DiamondStamp->setIcon(QIcon(":/images/Images/diamond.png"));
                   ui->DiamondStamp->setIconSize(QSize(25,25));
                   //Triangle
                   ui->TriangleStamp->setIcon(QIcon(":/images/Images/triangle.png"));
                   ui->TriangleStamp->setIconSize(QSize(25,25));


                   connect(ui->StampButton, &QPushButton::clicked, this, &MainWindow::StampClicked);

                          connect(ui->HeartStamp, &QPushButton::clicked, this, &MainWindow::HeartStampSelected);
                          connect(ui->DiamondStamp, &QPushButton::clicked, this, &MainWindow::DiamondStampSelected);
                          connect(ui->TriangleStamp, &QPushButton::clicked, this, &MainWindow::TriangleStampSelected);
                          connect(ui->CustomColorButton, &QPushButton::clicked, this, &MainWindow::CustomSelected);
                          connect(ui->Black, &QPushButton::clicked, this, &MainWindow::BlackSelected);
                          connect(ui->Grey, &QPushButton::clicked, this, &MainWindow::GreySelected);
                          connect(ui->White, &QPushButton::clicked, this, &MainWindow::WhiteSelected);
                          connect(ui->Blue, &QPushButton::clicked, this, &MainWindow::BlueSelected);
                          connect(ui->Green, &QPushButton::clicked, this, &MainWindow::GreenSelected);
                          connect(ui->Yellow, &QPushButton::clicked, this, &MainWindow::YellowSelected);
                          connect(ui->Red, &QPushButton::clicked, this, &MainWindow::RedSelected);
                          connect(ui->Purple, &QPushButton::clicked, this, &MainWindow::PurpleSelected);
                          //connect(ui->Cyan, &QPushButton::clicked, this, &MainWindow::CyanSelected);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief
 */
void MainWindow::BrushClicked()
{
    //ui->BrushSizeButton->setDisabled(false);
    TurnOffButton();
    isBrush = true;
    UnselectStamp();

   // selectedColor = QColorDialog::getColor(Qt::red, this);

}

void MainWindow::CustomSelected()
{
    selectedColor = QColorDialog::getColor(Qt::red, this);
}

/**
 * @brief MainWindow::EraseClicked
 */
void MainWindow::EraseClicked()
{
    TurnOffButton();
    UnselectStamp();
    erasing=true;


}

/**
 * @brief MainWindow::FillClicked
 */
void MainWindow::FillClicked()
{
    TurnOffButton();
    fillClicked = true;

    QPen pen(selectedColor);
    QBrush brush(selectedColor);
    int x = 0;
    int y = 0;

    int x2 = ui->ImageView->width();
    int y2 = ui->ImageView->height();
    ui->ImageView->scene()->addRect(x,y,x2,y2,pen, brush);
    UpdateFrameView();

    UnselectStamp();
}

/**
 * @brief MainWindow::LineClicked
 */
void MainWindow::LineClicked()
{
    TurnOffButton();
    drawingLine = true;
    squareClicked = false;
    UnselectStamp();

}

/**
 * @brief MainWindow::SquareClicked
 */
void MainWindow::RectangleClicked()
{
    TurnOffButton();
    //selectedColor = QColorDialog::getColor(Qt::red, this);
    squareClicked = true;
    drawingLine = false;
    UnselectStamp();
}

/**
 * @brief MainWindow::StampClicked
 */
void MainWindow::StampClicked()
{
    //selectedColor = QColorDialog::getColor(Qt::red, this);
    TurnOffButton();
    isStamped = true;

 //Show all the stamps when user wants
    ui ->HeartStamp->show();
    ui->DiamondStamp->show();
    ui->TriangleStamp->show();
}

/**
 * @brief MainWindow::SetImageView - Gets the image from the frames class to display on the main view
 */
void MainWindow::SetImageView(int index)
{
    QPixmap framePix = QPixmap::fromImage(frames.imageFrames[index]);
    QGraphicsScene *frameScene = new QGraphicsScene();
    frameScene ->addPixmap(framePix);
    ui->ImageView->setScene(frameScene);
}

/**
 * @brief MainWindow::SetFrameView - Gets the image from the frames class to display on the frame view
 */
void MainWindow::SetFrameView(int index)
{
    QPixmap framePix = QPixmap::fromImage(frames.imageFrames[index].scaled(100, 100));
    QGraphicsScene *frameScene = new QGraphicsScene();
    frameScene ->addPixmap(framePix);
    MyGraphicsView *frameView = new MyGraphicsView(frameCount);
    frameView->setScene(frameScene);

    connect(frameView, &MyGraphicsView::SelectionSignal, this, &MainWindow::NewFrameSelected);
    framesVector.insert(framesVector.begin()+index, frameView);
}

/**
 * @brief MainWindow::AddFrameClicked - Adds a frame to the project
 */
void MainWindow::AddFrameClicked()
{
    emit AddFrameSignal();
    hasChanged=true;
    SetFrameView(frameCount);
    ui ->FrameLayout -> addWidget(framesVector[frameCount]);
    ui ->FrameScrollArea->show();
    ui ->ScrollWidget->setLayout(ui -> FrameLayout);

    frameCount++;

}

/**
 * @brief MainWindow::DeleteFrameClicked - Deletes a frame from the project
 */
void MainWindow::DeleteFrameClicked()
{
    //if there is no images, won't cause an error
    if (framesVector.size() != 0)
    {
        emit DeleteFrameSignal(selectedFrame); //holds the frame number you want to delete
        delete framesVector[selectedFrame]; //delete GraphicsView Pointer
        framesVector.erase(framesVector.begin()+selectedFrame);
        frameCount--;
        for (int i = 0; i < framesVector.size(); i++)
        {
            framesVector[i] -> placement = i;
        }
        if (selectedFrame > 0)
        {
            NewFrameSelected(selectedFrame - 1);
        }
        else
        {
            NewFrameSelected(0);
        }
    }
    //Will show the preview of the selected frame is it is at 0 fps
    if (fps == 0)
    {
        UpdateZeroPreview();
    }
	DisableStamps();
}

/**
 * @brief MainWindow::NewFrameSelected - Runs whenever a new frame is selected
 */
void MainWindow::NewFrameSelected(int frame)
{
    if (frame < 0)
    {
        frame = 0;
    }
    selectedFrame = frame;
    for (int i = 0; i < framesVector.size(); i++)
    {
        if (i != selectedFrame)
        {
            framesVector[i]-> selected = false;
        }
    }
    //Sets the image and preview view of the newly selected frame
    SetImageView(selectedFrame);
    if (fps == 0)
    {
        UpdateZeroPreview();
    }
}

/**
 * @brief MainWindow::mouseMoveEvent - drawing for a brush
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePressed && !squareClicked && !drawingLine)
    {
        int x = ui->ImageView->pos().x();
        int y = ui->ImageView->pos().y();
        int width = ui->ImageView->width();
        int height = ui->ImageView->height();
        if((event ->pos().x()<x+width) && (event->pos().x()>=x) && (event->pos().y()>=y) && (event->pos().y()<=y+height)) {

            if((event ->pos().x()<x+width) && (event->pos().x()>=x) && (event->pos().y()>=y) && (event->pos().y()<=y+height))
            {
                int imagex = event->pos().x()-ui->ImageView->pos().x();
                int imagey = event->pos().y()-ui->ImageView->pos().y();

                const QPen pen(selectedColor); /* will make pen and brush a member variable*/
                QBrush brush(selectedColor);
                qreal pixelRow = (int)(getMouseY(event))/gridSquareSize;
                qreal pixelColumn = (int)(getMouseX(event))/gridSquareSize;
                if(erasing)
                    Erase(event);
                else
                    ui->ImageView->scene()->addRect(pixelColumn*gridSquareSize, pixelRow*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);

                UpdateFrameView();
            }
        }
    }
}

/**
 * @brief MainWindow::mousePressEvent - displays pixels for brush clicks
 */
void MainWindow::mousePressEvent(QMouseEvent * event)
{
    mousePressed=true;

    //calculate the inital position of the mouse press
    initialMouseX = getMouseX(event);
    initialMouseY = getMouseY(event);
    int x = ui->ImageView->pos().x();
    int y = ui->ImageView->pos().y();
    int width = ui->ImageView->width();
    int height = ui->ImageView->height();
    if(!squareClicked) /**do I need to change this for line*/
    {
        hasChanged=true;
        if((event->pos().x()<x+width) && (event->pos().x()>=x) && (event->pos().y()>=y) && (event->pos().y()<=y+height)) {

            int x = ui->ImageView->pos().x();
            int y = ui->ImageView->pos().y();
            int width = ui->ImageView->width();
            int height = ui->ImageView->height();
            if((event->pos().x()<x+width) && (event->pos().x()>=x) && (event->pos().y()>=y) && (event->pos().y()<=y+height)) {
                int imagex = event->pos().x()-290;
                int imagey = event->pos().y()-39;
                const QPen pen(selectedColor);
                QBrush brush(selectedColor);
                qreal pixelRow = (int)(getMouseX(event))/gridSquareSize;
                qreal pixelColumn = (int)(getMouseY(event))/gridSquareSize;
                if (heartStampInProgress)
                {
                    heartStampInProgress = false;
                    DrawHeart(gridSquareSize, pen, brush, pixelRow, pixelColumn);
                }
                else if (diamondStampInProgress)
                {
                    diamondStampInProgress = false;
                    DrawDiamond(gridSquareSize, pen, brush, pixelRow, pixelColumn);
                }
                else if (triangleStampInProgress)
                {
                    triangleStampInProgress = false;
                    DrawTriangle(gridSquareSize, pen, brush, pixelRow, pixelColumn);
                }
                if(erasing)
                    Erase(event);
                else
                    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
                UpdateFrameView();
            }
        }
    }
}

/**
 * @brief MainWindow::mouseReleaseEvent - draw lines or squares for a brush click
 */
void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    finalMouseX = getMouseX(event);
    finalMouseY = getMouseY(event);

    if(squareClicked)
    {
        drawRectangle();
    }
    if(drawingLine)
    {
        drawLine();
    }

    mousePressed=false;
}

/**
 * @brief MainWindow::getMouseX - returns mouse's x location in terms of the image view
 * @param event
 * @return
 */
int MainWindow::getMouseX(QMouseEvent * event)
{
    int imageViewX = ui->ImageView->pos().x();
    return event->pos().x()-imageViewX; //mouse position in terms of image view
}

/**
 * @brief MainWindow::getMouseX - returns mouse's y location in terms of the image view
 * @param event
 * @return
 */
int MainWindow::getMouseY(QMouseEvent * event)
{
    int imageViewY = ui->ImageView->pos().y();
    return event->pos().y()-imageViewY; //mouse position in terms of image view
}

/**
 * @brief MainWindow::drawSquare - draws a rectangle
 */
void MainWindow::drawRectangle()
{
    int x1,y1,x2,y2;

    qreal initialPixelRow = (int)(initialMouseY)/gridSquareSize;
    qreal initialPixelColumn = (int)(initialMouseX)/gridSquareSize;
    qreal finalPixelRow = (int)(finalMouseY)/gridSquareSize;
    qreal finalPixelColumn = (int)(finalMouseX)/gridSquareSize;

    if(finalPixelRow>initialPixelRow)
    {
        y1 = initialPixelRow;
        y2 = finalPixelRow;
    }
    else
    {
        y2 = initialPixelRow;
        y1 = finalPixelRow;
    }

    if(finalPixelColumn>initialPixelColumn)
    {
        x1 = initialPixelColumn;
        x2 = finalPixelColumn;
    }
    else
    {
        x2 = initialPixelColumn;
        x1 = finalPixelColumn;
    }

    const QPen pen(selectedColor);
    QBrush brush(selectedColor);

    //top row of rectangle
    for(int i=x1; i<=x2; i++)
    {
        ui->ImageView->scene()->addRect(i*gridSquareSize, y1*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        UpdateFrameView();
    }
    //bottom row of rectangle
    for(int i=x1; i<=x2; i++)
    {
        ui->ImageView->scene()->addRect(i*gridSquareSize, y2*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        UpdateFrameView();
    }
    //right row of rectangle
    for(int i=y1; i<=y2; i++)
    {
        ui->ImageView->scene()->addRect(x2*gridSquareSize, i*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        UpdateFrameView();
    }
    //left row of rectangle
    for(int i=y1; i<=y2; i++)
    {
        ui->ImageView->scene()->addRect(x1*gridSquareSize, i*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        UpdateFrameView();
    }
}

void MainWindow::Erase(QMouseEvent * event)
{
    qreal pixelRow = (int)(getMouseY(event))/gridSquareSize;
    qreal pixelColumn = (int)(getMouseX(event))/gridSquareSize;

    QTransform transform;
    while ((this->ui->ImageView->scene()->itemAt((pixelColumn+0.5)*gridSquareSize,(pixelRow+0.5)*gridSquareSize,transform)) != 0)
    {
        this->ui->ImageView->scene()->removeItem(this->ui->ImageView->scene()->itemAt((pixelColumn+0.5)*gridSquareSize,(pixelRow+0.5)*gridSquareSize,transform));
    }
}

/**
 * @brief MainWindow::UpdateFrameView - Updates the image to the frame preview
 */
void MainWindow::UpdateFrameView()
{
    ui->ImageView->scene()->setSceneRect(0,0,512,512);
    QImage image(ui->ImageView->scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(QColor(0, 0, 0,0));
    QPainter painter(&image);
    ui->ImageView->scene()->render(&painter);

    //bool x = image.save("..//testSave.png", "PNG", -1);
    //std::cout << "x: " << x << std::endl;

    frames.imageFrames[selectedFrame] = image;

    QPixmap pix = QPixmap::fromImage(image.scaled(100, 100, Qt::KeepAspectRatio));
    QList<QGraphicsItem*> items = framesVector[selectedFrame]->scene()->items();
    for (int i = 0; i < items.size(); i++)
    {
        framesVector[selectedFrame]->scene()->removeItem(items[i]);
        delete items[i];
    }
    framesVector[selectedFrame]->scene()->addPixmap(pix);
}

void MainWindow::drawLine()
{
    int x1,y1,x2,y2;

    qreal initialPixelColumn = (int)(initialMouseX)/gridSquareSize;
    qreal initialPixelRow = (int)(initialMouseY)/gridSquareSize;
    qreal finalPixelColumn = (int)(finalMouseX)/gridSquareSize;
    qreal finalPixelRow = (int)(finalMouseY)/gridSquareSize;

    //std::cout<<"final "<<finalPixelColumn<<" initial "<<initialPixelColumn<<std::endl;

    if(finalPixelColumn>initialPixelColumn)
    {
        x1 = initialPixelColumn*gridSquareSize;
        y1 = initialPixelRow*gridSquareSize;
        x2 = finalPixelColumn*gridSquareSize;
        y2 = finalPixelRow*gridSquareSize;
    }
    else if(finalPixelColumn==initialPixelColumn)
    {
        std::cout<<"i "<<initialPixelRow<<" f "<<finalPixelRow;
        drawStraightLine(initialPixelRow, finalPixelRow, initialPixelColumn, gridSquareSize);
    }
    else
    {
        x1 = finalPixelColumn*gridSquareSize;
        y1 = finalPixelRow*gridSquareSize;
        x2 = initialPixelColumn*gridSquareSize;
        y2 = initialPixelRow*gridSquareSize;
    }
    //std::cout <<"y1: "<<y1<<" "<<"y2: "<<y2<<"x1: "<<x1<<" "<<"x2: "<<x2<<std::endl;
    double slope = (double)(y2-y1)/(x2-x1);
    //std::cout<<"slope "<<slope<<std::endl;
    //std::cout <<"x1: "<<x1<<" "<<"x2: "<<x2<<std::endl;
    double y;
    int pixelColumn,pixelRow;

    const QPen pen(selectedColor);
    QBrush brush(selectedColor);

    for(int i=x1; i<x2+gridSquareSize; i+=gridSquareSize/10)
    {
        y = slope*(i-x1)+y1;
        pixelColumn = i/gridSquareSize;
        pixelRow = y/gridSquareSize;
        ui->ImageView->scene()->addRect(pixelColumn*gridSquareSize, pixelRow*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        UpdateFrameView();
    }
}

void MainWindow::drawStraightLine(int startRow, int endRow, int column, int gridSquareSize)
{
    int begin;
    int end;

    if(startRow>=endRow)
    {
        begin = endRow;
        end = startRow;
    }
    else
    {
        begin = startRow;
        end = endRow;
    }


    const QPen pen(selectedColor);
    QBrush brush(selectedColor);

    for(int i=begin; i<=end; i++)
    {
        ui->ImageView->scene()->addRect(column*gridSquareSize, i*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        UpdateFrameView();
    }
}

void MainWindow::on_actionNew_triggered()
{
    MainWindow *newWindow = new MainWindow;
    newWindow->show();
}

void MainWindow::on_actionOpen_triggered()
{
    if(!hasChanged)
    {
        QString filename = QFileDialog::getOpenFileName(this,tr("Text Files (*.txt)"));
        QFile file(filename);
        int height, width;//----numberOfFrames;
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            stream >> height >> width;
            int gridSquareHeight = 512/height;
            int gridSquareWidth = 512/width;
            stream >> numberOfFrames;

            //        //Get correct number of frames for file being opened (by first deleting all currently opened frames,
            //        //then adding new ones)
            for (int i = 0; i < framesVector.size()-1; i++)
            {
                DeleteFrameClicked();
            }


            for (int i = 0; i < numberOfFrames-1; i++)
            {
                AddFrameClicked();
            }
            QImage newFrame = QImage(512, 512, QImage::Format_ARGB32);
            frames.imageFrames[0] = newFrame;
            frames.imageFrames[0].fill(QColor(0, 0, 0,0));

            stream.readLine(0);
            for (int frameCount = 0; frameCount < numberOfFrames; frameCount++)
            {
                ui->ImageView->scene()->clear();
                ui->Preview->scene()->clear();      //---------
                for (int row = 0; row < height; row++)
                {
                    //Get the colors of all pixels in a row
                    std::stringstream colorsInRow;
                    QString rowString = stream.readLine(0);

                    colorsInRow << rowString.toStdString();
                    for (int col = 0; col < width; col++)
                    {
                        int red, green, blue, alpha;
                        colorsInRow >> red >> green >> blue >> alpha;
                        //                        std::cout << red << "green"<< green << "blue" << blue << "alpha" << alpha;
                        QColor color(red, green, blue, alpha);
                        color.setAlpha(alpha);
                        //                        std::cout << "alpha" << alpha;
                        QPen pixelPen(color);
                        QBrush pixelBrush(color);
                        ui->ImageView->scene()->addRect(col*gridSquareHeight, row*gridSquareWidth, (qreal)gridSquareHeight, (qreal)gridSquareWidth, pixelPen, pixelBrush);
                    }
                    UpdateFrameView();
                    selectedFrame = frameCount;
                }
            }
        }
    }
    else
    {
        on_actionSave_triggered();
        hasChanged = false;
        on_actionOpen_triggered();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Text Files (*.txt)"));
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        int gridSquareSize = 64;

        stream << 512/gridSquareSize << " " << 512/gridSquareSize << "\n";
        stream << frames.imageFrames.count() << "\n";

        for (int frame = 0; frame < frames.imageFrames.count(); frame++)
        {
            for (int row = 0; row < 512/gridSquareSize; row++)
            {
                for (int col = 0; col < (512/gridSquareSize); col++)
                {
                    QColor pixelColor = frames.imageFrames[frame].pixel((col+0.5)*gridSquareSize, (row+0.5)*gridSquareSize);
                    int alpha = qAlpha(frames.imageFrames[frame].pixel((col+0.5)*gridSquareSize, (row+0.5)*gridSquareSize));
                    stream << pixelColor.red() << " " << pixelColor.green() << " " << pixelColor.blue() << " " <<
                              alpha << " ";
                }
                stream << "\n";
            }
        }
    }
    //this->close();
}


void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::on_HelpButton_clicked()
{

    QMessageBox::about(this, tr("Sprite Editor"),
                tr("<p>The <b>Sprite Editor</b> is an awesome way to paint creatively"
                   ". You want to find out how? Below are simple instructions to let you navigate the app easily<br>"
                   "<b>Fill:</b> fills out all the grid<br>"
                   "<b>Brush:</b> the brush is used to paint on grid<br>"
                   "<b>Lines:</b> this is used to draw straight lines on grid<br>"
                   "<b>Square:</b> this button draws squares on the grid<br>"
                   "<b>Stamps:</b> allows the selection of different stamps "
                   "</p><p> <b>Sprite Editor</b> provides keyboard hotkeys for easy use.<br>"
                   "B:: Brush<br>"
                   "F:: Fill<br>"
                   "S:: Stamps<br>"
                   "CTRL + N:: New<br>"
                   "CTRL + O:: Open<br>"
                   "CTRL + S:: Save<br>"
                   "CTRL + X:: Close </p>"));
}


/*void MainWindow::on_ColorButton_clicked()
{
    selectedColor = QColorDialog::getColor(Qt::red, this);
}

void MainWindow::on_BrushSizeButton_clicked()
{
    TurnOffButton();
    isBrush = true;
    brushSize = 2;

}*/
void MainWindow::TurnOffButton()
{
    fillClicked = false;
    erasing = false;
   // isStamped = false;
    isBrush = false;

}

void MainWindow::UpdateZeroPreview()
{
    QPixmap previewPix = QPixmap::fromImage(frames.imageFrames[selectedFrame].scaled(180, 180));
    QList<QGraphicsItem*> items = ui->Preview->scene()->items();

    for(int i=0; i<items.size();i++)
    {
        ui->Preview->scene()->removeItem(items[i]);
        delete items[i];
    }
    ui->Preview->scene()->addPixmap(previewPix);

}

void MainWindow::UpdatePreview()
{
    if(fps>0)
    {
        if(index>=frames.imageFrames.size())
        {
            index=0;
        }
        QPixmap previewPix = QPixmap::fromImage(frames.imageFrames[index].scaled(180, 180));
        QList<QGraphicsItem*> items = ui->Preview->scene()->items();
        index++;
        for(int i=0; i<items.size();i++)
        {
            ui->Preview->scene()->removeItem(items[i]);
            delete items[i];
        }
        ui->Preview->scene()->addPixmap(previewPix);
    }
    //have timer call on all fps values
    myTimer.singleShot(fps, this, SLOT(UpdatePreview())); //delay before enabling buttons for user

}

/**
 * @brief MainWindow::FPSClicked - Changes the fps when the slider changes
 */
void MainWindow::FPSClicked()
{
    fps = ui->FPSSlider->value();
    ui->FPSLabel->setText(QString::number(fps) + " FPS");
    if(fps!=0)
        fps = 1000/fps;
}

//DRAW HEART
void MainWindow::DrawHeart(int gridSquareSize, const QPen pen, QBrush brush, qreal pixelRow, qreal pixelColumn)
{
    // -2, -2
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -2, -1
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -1, -2
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-gridSquareSize, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -1, -1
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-gridSquareSize, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -1, 0
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-gridSquareSize, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 0, -1
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 0, 1
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize+gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    //1, -2
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+gridSquareSize, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 1, -1
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+gridSquareSize, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 1, 0
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+gridSquareSize, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 2, -2
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 2, -1
    ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);

    //Make the heart a bit bigger
    if(gridSquareSize <= 16 )
    {
        // -3, -3
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*3, pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -3, -2
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*3, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -3, -1
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*3, pixelColumn*gridSquareSize-(gridSquareSize), (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -2, -3
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -2, 0
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -1, -3
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize), pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -1, 1
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize), pixelColumn*gridSquareSize+(gridSquareSize), (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 0, -2
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 0, 2
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize+(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 1, -3
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize), pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 1, 1
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize), pixelColumn*gridSquareSize+(gridSquareSize), (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 2, -3
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 2, 0
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 3, -3
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*3, pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 3, -2
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*3, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 3, -1
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*3, pixelColumn*gridSquareSize-(gridSquareSize), (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
///////////////////////////
        // -4, -4
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*4, pixelColumn*gridSquareSize-(gridSquareSize)*4, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -4, -3
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*4, pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -4, -2
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*4, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -3, -4
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*3, pixelColumn*gridSquareSize-(gridSquareSize)*4, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -2, -4
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize-(gridSquareSize)*4, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 2, -4
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize-(gridSquareSize)*4, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        //3, -4
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*3, pixelColumn*gridSquareSize-(gridSquareSize)*4, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 4, -4
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*4, pixelColumn*gridSquareSize-(gridSquareSize)*4, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 4, -3
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*4, pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        //4, -2
        ui->ImageView->scene()-> addRect(pixelRow*gridSquareSize+(gridSquareSize)*4, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);

    }
}

//DRAW DIAMOND
void MainWindow::DrawDiamond(int gridSquareSize, const QPen pen, QBrush brush, qreal pixelRow, qreal pixelColumn)
{
    // -2, 0
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -2, -1 -- > -1, -1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize), pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -1, 0
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-gridSquareSize, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -2, 1 --> -1, 1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize), pixelColumn*gridSquareSize+(gridSquareSize), (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 0, -2
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 0, -1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 0, 1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize+gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 0, 2
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize+(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 1, -1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+gridSquareSize, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 1, 0
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+gridSquareSize, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 1, 1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+gridSquareSize, pixelColumn*gridSquareSize+gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 2, 0
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);

    //Make the diamond a bit bigger
    if (gridSquareSize <= 16)
    {
        // -3, 0
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize)*3, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -2, -1
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -2, 1
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize+gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -1, -2
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize), pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -1, 2
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize), pixelColumn*gridSquareSize+(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 0, -3
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 0, 3
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize+(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 1, -2
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize), pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 1, 2
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize), pixelColumn*gridSquareSize+(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 2, -1
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 2, 1
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize+gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
       // 3, 0
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize)*3, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);

    }
}

//DRAW TRIANGLE
void MainWindow::DrawTriangle(int gridSquareSize, const QPen pen, QBrush brush, qreal pixelRow, qreal pixelColumn)
{

    // -2, 0
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -1, -1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-gridSquareSize, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // -1, 0
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-gridSquareSize, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 0, -2
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 0, -1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 1, -1
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+gridSquareSize, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 1, 0
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+gridSquareSize, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
    // 2, 0
    ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);

    //Make the Triangle a bit bigger
    if (gridSquareSize <= 16)
    {
        // -3, 0
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize)*3, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -2, -1
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize)*2, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // -1, -2
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize-(gridSquareSize), pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 0, -3
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize, pixelColumn*gridSquareSize-(gridSquareSize)*3, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 1, -2
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize), pixelColumn*gridSquareSize-(gridSquareSize)*2, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        // 2, -1
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize)*2, pixelColumn*gridSquareSize-gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);
        //3, 0
        ui->ImageView->scene()->addRect(pixelRow*gridSquareSize+(gridSquareSize)*3, pixelColumn*gridSquareSize, (qreal)gridSquareSize, (qreal)gridSquareSize, pen, brush);

    }
}

/**
 * @brief MainWindow::HeartStampSelected
 */
void MainWindow::HeartStampSelected()
{
    erasing = false;
    heartStampInProgress = true;

    //Make sure all other stamps are false
    diamondStampInProgress = false;
    triangleStampInProgress = false;
}
/**
 * @brief MainWindow::DiamondStampSelected
 */
void MainWindow::DiamondStampSelected()
{
    erasing = false;
    diamondStampInProgress = true;

    //Make sure all other stamps are false
    heartStampInProgress = false;
    triangleStampInProgress = false;
}
/**
 * @brief MainWindow::StarStampSelected
 */
void MainWindow::TriangleStampSelected()
{
    erasing = false;
    triangleStampInProgress = true;

    //Make sure all other stamps are false
    heartStampInProgress = false;
    diamondStampInProgress = false;
}

/**
  * Diable all stamps until the user asks for them by clicking the stamps button
  * */
void MainWindow::DisableStamps()
{
    ui ->HeartStamp->hide();
    ui->DiamondStamp->hide();
    ui->TriangleStamp->hide();
}

/**
  * Deselsects all of the stamps when another tool is pressed instead. This way it won't
  * stamp when its not suppose to
  *
  * @brief MainWindow::UnselectStamp
  */
 void MainWindow::UnselectStamp()
{
     heartStampInProgress = false;
     diamondStampInProgress = false;
     triangleStampInProgress = false;
}


 void MainWindow::BlackSelected()
 {
     selectedColor = Qt::black;
 }

 void MainWindow::GreySelected()
 {
     selectedColor = Qt::gray;
 }

 void MainWindow::WhiteSelected()
 {
     selectedColor = Qt::white;
 }

 void MainWindow::BlueSelected()
 {
     selectedColor = Qt::blue;
 }

 void MainWindow::GreenSelected()
 {
     selectedColor = Qt::green;
 }

 void MainWindow::YellowSelected()
 {
     selectedColor = Qt::yellow;
 }

 void MainWindow::RedSelected()
 {
     selectedColor = Qt::red;
 }

 void MainWindow::MainWindow::CyanSelected()
 {
     selectedColor = Qt::cyan;
 }

 void MainWindow::PurpleSelected()
 {
     selectedColor = Qt::darkMagenta;
 }

void MainWindow::on_ExportButton_clicked()
{

   QImage image(ui->ImageView->scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);

   Image magickImage;


    QVector<Magick::Image> magickVector;


    for(int i = 0; i < frames.imageFrames.size(); i++)
    {

        try
        {
                image = frames.imageFrames[i] ;
                image.save("..//testSave.png", "PNG", -1);
                magickImage.read("..//testSave.png");

                magickVector.push_back(magickImage);
                magickVector[i].gifDisposeMethod(2);

        }
        catch(QException &error)
        {
            std::cout <<"Error: "<< error.what() << endl;
        }

    }

    for(int i = 0; i< magickVector.size(); i++)
    {
        magickVector[i].animationDelay(100/fps);
    }

    writeImages(magickVector.begin(), magickVector.end(),"..//gif_version.gif");

    //QMessageBox::Information(this, tr("Saved GIF"), tr("Exported Sucessful!"));

}

