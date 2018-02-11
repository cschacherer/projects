#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mycanvas.h"
#include <planets.h>
#include <qdebug.h>
#include <Box2D/Box2D.h>
#include <QImage>
#include <QGraphicsScene>
#include <QColor>
#include <QRgb>
#include <QToolButton>
#include <iostream>
#include <QStyle>
#include <QPushButton>
#include <QDebug>
#include <QScrollArea>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>
#include <QDialog>
#include <QColorDialog>
#include <QPen>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QString>
#include <QFile>
#include <QPainter>
#include <QPalette>
#include <QInputDialog>
#include <sstream>
#include <QMessageBox>
#include <QException>
#include <QBrush>
#include <QPen>
#include <QMouseEvent>
#include "journal.h"
#include "moon.h"
#include "earth.h"
#include "mercury.h"
#include <SFML/Audio.hpp>
#include "jupiter.h"
#include "neptune.h"
#include "client.h"
#include "loginform.h"
#include "registerform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame->setStyleSheet("background-image: url(:/journalItems/the-milky-way_Journal.jpg);");
    ui->graphicsView->setStyleSheet("background-image: url(:/journalItems/the-milky-way_Journal.jpg);");

    //ui->pushButton->setVisible(0);

    //login/Register

//    login.show();

//    Client *clientPointer = &client;
//    LoginForm *loginPointer = &login;
//    RegisterForm *regPointer = &regForm;

//    QObject::connect(loginPointer, &LoginForm::SendUsernameSignal, this, &MainWindow::LoginUsername);
//    QObject::connect(loginPointer, &LoginForm::ShowRegisterForm, this, &MainWindow::ShowRegister);
//    QObject::connect(regPointer, &RegisterForm::SendRegisterSignal, this, &MainWindow::RegisterPlayer);


    planets = new Planets();
    level = 0;
    imagePath = ":/images/Earth.jpg";
    background = QImage(":/images/Earth.jpg");
    backgroundScene = new QGraphicsScene(0, 0, 1200, 1200);
    QRectF sceneRect = ui->graphicsView->sceneRect();
    backgroundPix = QPixmap::fromImage(background);
    backgroundScene ->addPixmap(backgroundPix.scaled(1200,1200, Qt::KeepAspectRatio));
    ui->graphicsView->setScene(backgroundScene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->graphicsView->setWindowFlags(Qt::FramelessWindowHint);
    ui->graphicsView->setAttribute(Qt::WA_TranslucentBackground);
    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);
    qDebug()<<"before obj";
    qDebug()<<"af obj";
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    playAudio();


    connect(buttonBox, SIGNAL(accepted()), this, SLOT(closeQuiz()));
    connect(this, SIGNAL(gradeQuizSignal(QVector<QRadioButton*>, QVector<int>)), this, SLOT(gradeQuiz(QVector<QRadioButton*>, QVector<int>)));
    QObject::connect(ui->nextPlanet, &QPushButton::clicked, this, &MainWindow::displayPlanet);
    //Souvenir buttons
    QObject::connect(ui->item1Button, &QPushButton::clicked, this, &MainWindow::item1ButtonSlot);
    QObject::connect(ui->item2Button, &QPushButton::clicked, this, &MainWindow::item2ButtonSlot);
    QObject::connect(ui->item3Button, &QPushButton::clicked, this, &MainWindow::item3ButtonSlot);
    QObject::connect(ui->item4Button, &QPushButton::clicked, this, &MainWindow::item4ButtonSlot);
    QObject::connect(ui->item5Button, &QPushButton::clicked, this, &MainWindow::item5ButtonSlot);
    QObject::connect(ui->item6Button, &QPushButton::clicked, this, &MainWindow::item6ButtonSlot);
    QObject::connect(ui->item7Button, &QPushButton::clicked, this, &MainWindow::item7ButtonSlot);
    QObject::connect(ui->item8Button, &QPushButton::clicked, this, &MainWindow::item8ButtonSlot);
    QObject::connect(ui->item9Button, &QPushButton::clicked, this, &MainWindow::item9ButtonSlot);


    //    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::checkClick);
    //    QObject::connect(ui->p, &QPushButton::clicked, this, &MainWindow::checkClick);


    //connect(ui->item1Button, &QPushButton::clicked, )
    ui->nextPlanet->setEnabled(true);
    displayMessage();

    SetButtons();

    if(imagePath == ":/images/Earth.jpg")
    {
        earthLevel();
    }

    character = new QGraphicsRectItem(ui->graphicsView->pos().x(),ui->graphicsView->pos().y(),75,75);
    QBrush brush(Qt::transparent);
    QPen pen(Qt::transparent);
    character->setBrush(brush);
    character->setPen(pen);
    characterImage.setPixmap(QPixmap(":/images/astro-2.png"));
    characterImage.setParentItem(character);
    character->setPos(1, 600);

    backgroundScene->addItem(character);
    ui->graphicsView->setScene(backgroundScene);
    animationCount = 0;


    //    ui->pushButton_2->setStyleSheet("QPushButton{background: transparent;}");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    qDebug()<<"works";
    //ui->pushButton->setVisible(0);

}

void MainWindow::showButton()
{
    qDebug()<<"in Main";
    // ui->pushButton->setVisible(1);

}

void MainWindow::LoginUsername(QString name, QString pass)
{
    client.GetUsername(name, pass);
    login.hide();
    if (client.correctLogin)
    {
        this->show();
    }
}

void MainWindow::RegisterPlayer(QString user, QString pass, QString first, QString last)
{
    client.RegisterUser(user, pass, first, last);
    regForm.hide();
    this->show();
}

void MainWindow::ShowRegister()
{
    regForm.show();
    login.hide();
}

void MainWindow::addCharacter()
{
    QGraphicsPixmapItem *player = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(":/images/astro-2.png")));
    player->setPos(1,600);
    backgroundScene->addItem(player);
    ui->graphicsView->setScene(backgroundScene);

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << event->pos().x() << " " << event->pos().y();

    //    if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 300 && event->pos().y() < 400)
    //    {
    //        ui->itemNameLabel->setText("water");
    //        ui->itemDescriptionLabel->setText("water description");
    //    }

    //mars items hover
    if(imagePath ==":/images/mar.jpg")
    {
        if (event->pos().x() > 300 + 200 && event->pos().x() < 400 + 200 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            if (mars.m1.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(mars.m1.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(mars.m1.souvenirDescription));
            }
        }
        else if (event->pos().x() > 600 + 200 && event->pos().x() < 700 + 200 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            if (mars.m2.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(mars.m2.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(mars.m2.souvenirDescription));
            }
        }
        else if (event->pos().x() > 25 + 200 && event->pos().x() < 325 + 200 && event->pos().y() > 300 && event->pos().y() < 500)
        {
            if (mars.m3.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(mars.m3.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(mars.m3.souvenirDescription));
            }
        }
        else
        {
            ui->itemNameLabel->setText("");
            ui->itemDescriptionLabel->setText("");
        }
    }
    if(imagePath==":/images/mercury.png")
    {
        //mantle
        if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            if (mercury.m1.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(mercury.m1.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(mercury.m1.souvenirDescription));
            }
        }
        //metal
        else if (event->pos().x() > 600 && event->pos().x() < 700 && event->pos().y() > 500 && event->pos().y() < 600)
        {
            if (mercury.m2.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(mercury.m2.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(mercury.m2.souvenirDescription));
            }
        }
        //dirt
        else if (event->pos().x() > 400 && event->pos().x() < 500 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            if (mercury.m3.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(mercury.m3.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(mercury.m3.souvenirDescription));
            }
        }
        //crust
        else if (event->pos().x() > 734 && event->pos().x() < 834 && event->pos().y() > 354 && event->pos().y() < 454)
        {
            if (mercury.m4.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(mercury.m4.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(mercury.m4.souvenirDescription));
            }
        }
        else
        {

                ui->itemNameLabel->setText("");
                ui->itemDescriptionLabel->setText(" Hover over an item\nto see its descritpion.");
        }
    }

    if(imagePath==":/images/venus.jpg")
    {
        //magnet
        if (event->pos().x() > 600 && event->pos().x() < 700 && event->pos().y() > 500 && event->pos().y() < 600)
        {
            if (venus.v1.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(venus.v1.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(venus.v1.souvenirDescription));
            }
        }
        //mantle
        else if (event->pos().x() > 400 && event->pos().x() < 500 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            if (venus.v2.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(venus.v2.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(venus.v2.souvenirDescription));
            }
        }
        //dirt
        else if (event->pos().x() > 734 && event->pos().x() < 854 && event->pos().y() > 354 && event->pos().y() < 454)
        {
            if (venus.v3.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(venus.v3.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(venus.v3.souvenirDescription));
            }
        }
        else
        {

                ui->itemNameLabel->setText("");
                ui->itemDescriptionLabel->setText(" Hover over an item\nto see its descritpion.");
        }

    }


    //saturn items hover
    if(imagePath ==":/images/saturn.png")
    {
        if (event->pos().x() > 300 + 200 && event->pos().x() < 400 + 200 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            if (saturn.s1.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(saturn.s1.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(saturn.s1.souvenirDescription));
            }
        }
        else if (event->pos().x() > 600 + 200 && event->pos().x() < 700 + 200 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            if (saturn.s2.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(saturn.s2.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(saturn.s2.souvenirDescription));
            }
        }
        else if (event->pos().x() > 100 + 200 && event->pos().x() < 200 + 200 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            if (saturn.s3.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(saturn.s3.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(saturn.s3.souvenirDescription));
            }
        }
        else
        {

                ui->itemNameLabel->setText("");
                ui->itemDescriptionLabel->setText(" Hover over an item\nto see its descritpion.");
        }
    }



    //uranus items hover
    if(imagePath ==":/images/uranus.png")
    {
        if (event->pos().x() > 300 + 200 && event->pos().x() < 400 + 200 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            if (uranus.u1.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(uranus.u1.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(uranus.u1.souvenirDescription));
            }
        }
        else if (event->pos().x() > 600 + 200 && event->pos().x() < 700 + 200 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            if (uranus.u2.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(uranus.u2.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(uranus.u2.souvenirDescription));
            }
        }
        else if (event->pos().x() > 100 + 200 && event->pos().x() < 200 + 200 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            if (uranus.u3.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(uranus.u3.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(uranus.u3.souvenirDescription));
            }
        }
        else
        {
                ui->itemNameLabel->setText("");
                ui->itemDescriptionLabel->setText(" Hover over an item\nto see its descritpion.");
        }
    }

    if(imagePath==":/images/Earth.jpg")
    {
        //Water
        if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e1.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e1.souvenirDescription));
        }
        //Comb
        else if (event->pos().x() > 800 && event->pos().x() < 850 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e2.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e2.souvenirDescription));
        }
        //iPod
        else if(event->pos().x() > 450 && event->pos().x() < 500 && event->pos().y() > 454 && event->pos().y() < 504)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e3.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e3.souvenirDescription));
        }
        //cell 578 484
        else if(event->pos().x() > 550 && event->pos().x() < 600 && event->pos().y() > 450 && event->pos().y() < 500)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e4.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e4.souvenirDescription));
        }
        //Lighter
        else if(event->pos().x() > 950 && event->pos().x() < 1000 && event->pos().y() > 450 && event->pos().y() < 500)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e5.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e5.souvenirDescription));
        }
        //Oxygen
        else if(event->pos().x() > 325 && event->pos().x() < 425 && event->pos().y() > 354 && event->pos().y() < 454)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e6.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e6.souvenirDescription));
        }
        //Food
        else if(event->pos().x() > 1100 && event->pos().x() < 1200 && event->pos().y() > 350 && event->pos().y() < 450)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e7.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e7.souvenirDescription));
        }
        //Radio
        else if(event->pos().x() > 600 && event->pos().x() < 650 && event->pos().y() > 300 && event->pos().y() < 350)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e8.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e8.souvenirDescription));
        }
        //Blanket
        else if(event->pos().x() > 650 && event->pos().x() < 710 && event->pos().y() > 400 && event->pos().y() < 460)
        {
            ui->itemNameLabel->setText(QString::fromStdString(earth.e9.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(earth.e9.souvenirDescription));
        }
        else
        {
            ui->itemNameLabel->setText("");
            ui->itemDescriptionLabel->setText(" Hover over an item\nto see its descritpion.");
        }

    }

    if(imagePath==":/images/moon.jpg")
    {
        //dirt
        if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            ui->itemNameLabel->setText(QString::fromStdString(moon.m4.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(moon.m4.souvenirDescription));
        }
        //moon near side
        else if (event->pos().x() > 434 && event->pos().x() < 534 && event->pos().y() > 554 && event->pos().y() < 654)
        {
            ui->itemNameLabel->setText(QString::fromStdString(moon.m1.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(moon.m1.souvenirDescription));
        }
        //maria
        else if (event->pos().x() > 400 && event->pos().x() < 500 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            ui->itemNameLabel->setText(QString::fromStdString(moon.m3.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(moon.m3.souvenirDescription));
        }
        //flag
        else if (event->pos().x() > 734 && event->pos().x() < 1034 && event->pos().y() > 354 && event->pos().y() < 654)
        {
            ui->itemNameLabel->setText(QString::fromStdString(moon.m5.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(moon.m5.souvenirDescription));
        }
        //moon far side
        else if (event->pos().x() > 300 && event->pos().x() < 400 && event->pos().y() > 500 && event->pos().y() < 600)
        {
            ui->itemNameLabel->setText(QString::fromStdString(moon.m2.souvenirName));
            ui->itemDescriptionLabel->setText(QString::fromStdString(moon.m2.souvenirDescription));
        }
        //Earth
        else if (event->pos().x() > 781 && event->pos().x() < 858 && event->pos().y() > 193 && event->pos().y() < 277)
        {
            ui->itemNameLabel->setText(QString::fromStdString("Earth"));
            ui->itemDescriptionLabel->setText(QString::fromStdString("This is our beautiful home\n planet"));
        }
        else
        {
            ui->itemNameLabel->setText("");
            ui->itemDescriptionLabel->setText(" Hover over an item\nto see its descritpion.");
        }
    }

    //uranus items hover
    if(imagePath ==":/images/uranus.png")
    {
        if (event->pos().x() > 300 + 200 && event->pos().x() < 400 + 200 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            if (uranus.u1.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(uranus.u1.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(uranus.u1.souvenirDescription));
            }
        }
        else if (event->pos().x() > 600 + 200 && event->pos().x() < 700 + 200 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            if (uranus.u2.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(uranus.u2.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(uranus.u2.souvenirDescription));
            }
        }
        else if (event->pos().x() > 100 + 200 && event->pos().x() < 200 + 200 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            if (uranus.u3.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(uranus.u3.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(uranus.u3.souvenirDescription));
            }
        }
        else
        {
            ui->itemNameLabel->setText("");
            ui->itemDescriptionLabel->setText("");
        }
    }

    if(imagePath==":/images/neptune.png")
    {
        //
        if (event->pos().x() > 600 && event->pos().x() < 700 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            if (neptune.n1.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(neptune.n1.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(neptune.n1.souvenirDescription));
            }
        }
        //
        if (event->pos().x() > 800 && event->pos().x() < 900 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            if (neptune.n2.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(neptune.n2.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(neptune.n2.souvenirDescription));
            }
        }
        //
        if (event->pos().x() > 400 && event->pos().x() < 500 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            if (neptune.n3.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(neptune.n3.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(neptune.n3.souvenirDescription));
            }
        }
        else
        {
            ui->itemNameLabel->setText("");
            ui->itemDescriptionLabel->setText("");
        }

    }

    if(imagePath==":/images/jupiter.png")
    {
        //
        if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            if (jupiter.j1.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(neptune.n1.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(neptune.n1.souvenirDescription));
            }
        }
        //
        else if (event->pos().x() > 800 && event->pos().x() < 900 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            if (jupiter.j2.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(neptune.n2.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(neptune.n2.souvenirDescription));
            }
        }
        //
        else if (event->pos().x() > 300 && event->pos().x() < 400 && event->pos().y() > 500 && event->pos().y() < 500)
        {
            if (jupiter.j3.pixmapItem->isVisible() == true)
            {
                ui->itemNameLabel->setText(QString::fromStdString(neptune.n3.souvenirName));
                ui->itemDescriptionLabel->setText(QString::fromStdString(neptune.n3.souvenirDescription));
            }
        }
        else
        {
            ui->itemNameLabel->setText("");
            ui->itemDescriptionLabel->setText("");
        }

    }
    
}



/**
 * @brief MainWindow::mouseMoveEvent - drawing for a brush
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int pixelsPerMeter = 50;
    int characterHeight = 1.5; //Meters
    int characterMass = 50;  //Kilograms

    int x = ui->graphicsView->pos().x();
    int y = ui->graphicsView->pos().y();
    int width = ui->graphicsView->width();
    int height = ui->graphicsView->height();


    qDebug() << "pos: " << event->pos().x() << " " << event->pos().y();

    //if(x > 300 && x < 400 && y > 300 && y < 400)
    if(imagePath==":/images/Earth.jpg")
    {
        //Water
        if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->item1Button->setVisible(true);
            earth.e1.pixmapItem->setVisible(0);
        }
        //Comb
        if (event->pos().x() > 800 && event->pos().x() < 850 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            ui->item2Button->setVisible(true);
            earth.e2.pixmapItem->setVisible(0);
        }
        //iPod
        if(event->pos().x() > 450 && event->pos().x() < 500 && event->pos().y() > 454 && event->pos().y() < 504)
        {
            ui->item3Button->setVisible(true);
            earth.e3.pixmapItem->setVisible(0);
        }
        //cell 578 484
        if(event->pos().x() > 550 && event->pos().x() < 600 && event->pos().y() > 450 && event->pos().y() < 500)
        {
            ui->item4Button->setVisible(true);
            earth.e4.pixmapItem->setVisible(0);
        }
        //Lighter
        if(event->pos().x() > 950 && event->pos().x() < 1000 && event->pos().y() > 450 && event->pos().y() < 500)
        {
            ui->item5Button->setVisible(true);
            earth.e5.pixmapItem->setVisible(0);
        }
        //Oxygen
        if(event->pos().x() > 325 && event->pos().x() < 425 && event->pos().y() > 354 && event->pos().y() < 454)
        {
            ui->item6Button->setVisible(true);
            earth.e6.pixmapItem->setVisible(0);
        }
        //Food
        if(event->pos().x() > 1100 && event->pos().x() < 1200 && event->pos().y() > 350 && event->pos().y() < 450)
        {
            ui->item7Button->setVisible(true);
            earth.e7.pixmapItem->setVisible(0);
        }
        //Radio
        if(event->pos().x() > 600 && event->pos().x() < 650 && event->pos().y() > 300 && event->pos().y() < 350)
        {
            ui->item8Button->setVisible(true);
            earth.e8.pixmapItem->setVisible(0);
        }
        //Blanket
        if(event->pos().x() > 650 && event->pos().x() < 710 && event->pos().y() > 400 && event->pos().y() < 460)
        {
            ui->item9Button->setVisible(true);
            earth.e9.pixmapItem->setVisible(0);
        }

    }
    if(imagePath==":/images/moon.jpg")
    {
        //dirt
        if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            ui->item1Button->setVisible(true);
            moon.m4.pixmapItem->setVisible(0);
        }
        //moon near side
        if (event->pos().x() > 434 && event->pos().x() < 534 && event->pos().y() > 554 && event->pos().y() < 654)
        {
            ui->item2Button->setVisible(true);
            moon.m1.pixmapItem->setVisible(0);
        }
        //maria
        if (event->pos().x() > 400 && event->pos().x() < 500 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            ui->item3Button->setVisible(true);
            moon.m3.pixmapItem->setVisible(0);
        }
        //flag
        if (event->pos().x() > 734 && event->pos().x() < 1034 && event->pos().y() > 354 && event->pos().y() < 654)
        {
            ui->item4Button->setVisible(true);
            moon.m5.pixmapItem->setVisible(0);
        }
        //moon far side
        if (event->pos().x() > 300 && event->pos().x() < 400 && event->pos().y() > 500 && event->pos().y() < 600)
        {
            ui->item5Button->setVisible(true);
            moon.m2.pixmapItem->setVisible(0);
        }
    }

    if(imagePath==":/images/neptune.png")
    {
        //
        if (event->pos().x() > 600 && event->pos().x() < 700 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->item1Button->setVisible(true);
            neptune.n1.pixmapItem->setVisible(0);
        }
        //
        if (event->pos().x() > 800 && event->pos().x() < 900 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->item2Button->setVisible(true);
            neptune.n2.pixmapItem->setVisible(0);
        }
        //
        if (event->pos().x() > 400 && event->pos().x() < 500 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->item3Button->setVisible(true);
            neptune.n3.pixmapItem->setVisible(0);
        }

    }

    if(imagePath==":/images/jupiter.png")
    {
        //
        if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->item1Button->setVisible(true);
            jupiter.j1.pixmapItem->setVisible(0);
        }
        //
        if (event->pos().x() > 800 && event->pos().x() < 900 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            ui->item2Button->setVisible(true);
            jupiter.j2.pixmapItem->setVisible(0);
        }
        //
        if (event->pos().x() > 300 && event->pos().x() < 400 && event->pos().y() > 500 && event->pos().y() < 600)
        {
            ui->item3Button->setVisible(true);
            jupiter.j3.pixmapItem->setVisible(0);
        }

    }

    if(imagePath==":/images/mercury.png")
    {
        //mantle
        if (event->pos().x() > 500 && event->pos().x() < 600 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            ui->item1Button->setVisible(true);
            mercury.m1.pixmapItem->setVisible(0);
        }
        //metal
        if (event->pos().x() > 600 && event->pos().x() < 700 && event->pos().y() > 500 && event->pos().y() < 600)
        {
            ui->item2Button->setVisible(true);
            mercury.m2.pixmapItem->setVisible(0);
        }
        //dirt
        if (event->pos().x() > 400 && event->pos().x() < 500 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            ui->item3Button->setVisible(true);
            mercury.m3.pixmapItem->setVisible(0);
        }
        //crust
        if (event->pos().x() > 734 && event->pos().x() < 834 && event->pos().y() > 354 && event->pos().y() < 454)
        {
            ui->item4Button->setVisible(true);
            mercury.m4.pixmapItem->setVisible(0);
        }
    }

    if(imagePath==":/images/venus.jpg")
    {
        //magnet
        if (event->pos().x() > 600 && event->pos().x() < 700 && event->pos().y() > 500 && event->pos().y() < 600)
        {
            ui->item1Button->setVisible(true);
            venus.v1.pixmapItem->setVisible(0);
        }
        //mantle
        if (event->pos().x() > 400 && event->pos().x() < 500 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            ui->item2Button->setVisible(true);
            venus.v2.pixmapItem->setVisible(0);
        }
        //dirt
        if (event->pos().x() > 734 && event->pos().x() < 854 && event->pos().y() > 354 && event->pos().y() < 454)
        {
            ui->item3Button->setVisible(true);
            venus.v3.pixmapItem->setVisible(0);
        }

    }

    //mars item clicked
    if(imagePath ==":/images/mar.jpg")
    {
        if (event->pos().x() > 300 + 200 && event->pos().x() < 400 + 200 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->item1Button->setVisible(true);
            mars.m1.pixmapItem->setVisible(false);
        }
        if (event->pos().x() > 600 + 200 && event->pos().x() < 700 + 200 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            ui->item2Button->setVisible(true);
            mars.m2.pixmapItem->setVisible(false);
        }
        if (event->pos().x() > 25 + 200 && event->pos().x() < 325 + 200 && event->pos().y() > 300 && event->pos().y() < 600)
        {
            ui->item3Button->setVisible(true);
            mars.m3.pixmapItem->setVisible(false);
        }
    }

    //saturn item clicked
    if(imagePath ==":/images/saturn.png")
    {
        if (event->pos().x() > 300 + 200 && event->pos().x() < 400 + 200 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->item1Button->setVisible(true);
            saturn.s1.pixmapItem->setVisible(false);
        }
        if (event->pos().x() > 600 + 200 && event->pos().x() < 700 + 200 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            ui->item2Button->setVisible(true);
            saturn.s2.pixmapItem->setVisible(false);
        }
        if (event->pos().x() > 100 + 200 && event->pos().x() < 200 + 200 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            ui->item3Button->setVisible(true);
            saturn.s3.pixmapItem->setVisible(false);
        }
    }

    //uranus item clicked
    if(imagePath ==":/images/uranus.png")
    {
        if (event->pos().x() > 300 + 200 && event->pos().x() < 400 + 200 && event->pos().y() > 300 && event->pos().y() < 400)
        {
            ui->item1Button->setVisible(true);
            uranus.u1.pixmapItem->setVisible(false);
        }
        if (event->pos().x() > 600 + 200 && event->pos().x() < 700 + 200 && event->pos().y() > 400 && event->pos().y() < 500)
        {
            ui->item2Button->setVisible(true);
            uranus.u2.pixmapItem->setVisible(false);
        }
        if (event->pos().x() > 100 + 200 && event->pos().x() < 200 + 200 && event->pos().y() > 450 && event->pos().y() < 550)
        {
            ui->item3Button->setVisible(true);
            uranus.u3.pixmapItem->setVisible(false);
        }
    }


    //    if((event->pos().x()<x+width) && (event->pos().x()>=x) && (event->pos().y()>=y) && (event->pos().y()<=y+height)) {

    //        if((event->pos().x()<x+width) && (event->pos().x()>=x) && (event->pos().y()>=y) && (event->pos().y()<=y+height))
    //        {
    //    int imagex = event->pos().x()-ui->graphicsView->pos().x();
    //    int imagey = event->pos().y()-ui->graphicsView->pos().y();
    //    qDebug()<<imagex<<" "<<imagey;
    //    QBrush brush(Qt::transparent);
    //    QPen pen(Qt::transparent);
    //    //            character = new QGraphicsRectItem(300,300,characterHeight*pixelsPerMeter,characterHeight*pixelsPerMeter);
    //    //            character->setPos(event->pos().x(), event->pos().y());
    //    character->setBrush(brush);
    //    character->setPen(pen);

    //        }
    //    }

}

void MainWindow::displayPlanet()
{
    ui->nextPlanet->setEnabled(true);
    removeMessage();
    //    imagePath = planets->getPlanet();
    //    ui->graphicsView->scene()->clear();

    //    qDebug()<<"in display";
    //    planets->setPlanetNum();
    //    qDebug()<<imagePath;
    //    background = QImage(imagePath);
    //    backgroundPix = QPixmap::fromImage(background);
    //    backgroundScene ->addPixmap(backgroundPix.scaled(1200,1200, Qt::KeepAspectRatio));
    //    ui->graphicsView->setScene(backgroundScene);
    //    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    //    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents);
    //    ui->graphicsView->setWindowFlags(Qt::FramelessWindowHint);
    //    ui->graphicsView->setAttribute(Qt::WA_TranslucentBackground);

    if(imagePath!=":/images/Earth.jpg" && imagePath!=":/images/sun.jpg")
    {
        loadQuiz(level);
        level++;
    }

    goToPlanetAnimation(animationCount);
    animationCount++;
    //qDebug() << "level: " << level;
    imagePath = planets->getPlanet();

    backgroundScene = new QGraphicsScene(0, 0, 1200, 1200);
    qDebug()<<"in display";
    planets->setPlanetNum();
    //qDebug()<<imagePath;
    background = QImage(imagePath);
    backgroundPix = QPixmap::fromImage(background);
    backgroundScene ->addPixmap(backgroundPix.scaled(1200,1200, Qt::KeepAspectRatio));


    backgroundScene->addItem(character);
    ui->graphicsView->setScene(backgroundScene);


    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->graphicsView->setWindowFlags(Qt::FramelessWindowHint);
    ui->graphicsView->setAttribute(Qt::WA_TranslucentBackground);

    displayMessage();
    //if(imagePath!=":/images/Earth.jpg" && imagePath!=":/images/sun.jpg")
//    if(imagePath!=":/images/sun.jpg")
//    {
//        loadQuiz(level);
//        level++;
//    }

    if(imagePath == ":/images/Earth.jpg")
    {
        earthLevel();
    }

    if(imagePath == ":/images/mercury.png")
    {
        mercuryLevel();
    }
    if(imagePath == ":/images/moon.jpg")
    {
        moonLevel();
    }
    if(imagePath == ":/images/venus.jpg")
    {
        venusLevel();
    }
    //mars level
    if (imagePath == ":/images/mar.jpg")
    {
        MarsLevel();
    }

    //Saturn level
    if (imagePath == ":/images/saturn.png")
    {
        SaturnLevel();
    }

    //uranus level
    if(imagePath ==":/images/uranus.png")
    {
        UranusLevel();
    }
    //neptune
    if(imagePath == ":/images/neptune.png")
    {
        NeptuneLevel();
    }
    //jupiter
    if(imagePath == ":/images/jupiter.png")
    {
        JupiterLevel();
    }
    SetButtons();

}

void MainWindow::nextLevel(int currentLevel)
{
    loadQuiz(currentLevel);
    client.SaveLevel(currentLevel + 1);
}

int MainWindow::loadQuiz(int level)
{
    removeMessage();
    question = new QDialog();
    Quizzes quizzes;
    QVector<QVector<QString> > quiz = quizzes.getQuiz(level);
    QVector<int> solution = quizzes.getSolution(level);
    QVector<QRadioButton*> options;
    QVBoxLayout *allQuestionsVBox = new QVBoxLayout;
    QGroupBox *allQuestionsGroupBox = new QGroupBox;
    for (int questionNumber = 0; questionNumber < quiz.count(); questionNumber++)
    {
        const QString questionString = quiz[questionNumber][0];
        QGroupBox *groupBox = new QGroupBox(questionString);
        QVBoxLayout *vbox = new QVBoxLayout;

        for (int optionNumber = 1; optionNumber < quiz[questionNumber].count(); optionNumber++)
        {
            const QString optionString = quiz[questionNumber][optionNumber];
            QRadioButton* option = new QRadioButton(question);
            options.push_back(option);

            option->setText(optionString);
            vbox->addWidget(option);
        }
        vbox->addStretch(3);
        groupBox->setLayout(vbox);
        allQuestionsVBox->addWidget(groupBox);
        allQuestionsVBox->addStretch(1);
    }

    allQuestionsVBox->addWidget(buttonBox);
    allQuestionsGroupBox->setLayout(allQuestionsVBox);
    allQuestionsGroupBox->setParent(question);
    question->setLayout(allQuestionsVBox);

    if(question->exec() == true);
    emit gradeQuizSignal(options, solution);
}

void MainWindow::closeQuiz()
{
    question->close();
}

void MainWindow::gradeQuiz(QVector<QRadioButton*> options, QVector<int> solution)
{
    int score = 0;
    for (int i = 0; i<options.count(); i++)
    {
        if (options[i]->isChecked()&&solution[i] == 1)
            score++;
    }

    QMessageBox grade;
    const QString message = "You scored " + QString::number(score) + " out of 5";
    grade.setText(message);
    grade.exec();
}

void MainWindow::SetButtons()
{
    //Set buttons transparent
    ui->item1Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item2Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item3Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item4Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item5Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item6Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item7Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item8Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item9Button->setStyleSheet("QPushButton{background: transparent;}");
    ui->item10Button->setStyleSheet("QPushButton{background: transparent;}");

    if(imagePath == ":/images/Earth.jpg")
    {
        //Water
        ui->item1Button->setIcon(QIcon(":/earthItems/earthWaterBottle.png"));
        ui->item1Button->setIconSize(QSize(40, 40));
        ui->item1Button->setVisible(false);
        //Comb
        ui->item2Button->setIcon(QIcon(":/earthItems/earthComb.png"));
        ui->item2Button->setIconSize(QSize(40, 40));
        ui->item2Button->setVisible(false);
        //iPod
        ui->item3Button->setIcon(QIcon(":/earthItems/earthIPod.png"));
        ui->item3Button->setIconSize(QSize(40, 40));
        ui->item3Button->setVisible(false);
        //Cell
        ui->item4Button->setIcon(QIcon(":/earthItems/earthCell.png"));
        ui->item4Button->setIconSize(QSize(40, 40));
        ui->item4Button->setVisible(false);
        //Lighter
        ui->item5Button->setIcon(QIcon(":/earthItems/earthLighter.png"));
        ui->item5Button->setIconSize(QSize(40, 40));
        ui->item5Button->setVisible(false);
        //Oxygen
        ui->item6Button->setIcon(QIcon(":/earthItems/earthOxygen.png"));
        ui->item6Button->setIconSize(QSize(40, 40));
        ui->item6Button->setVisible(false);
        //Food
        ui->item7Button->setIcon(QIcon(":/earthItems/earthFood.png"));
        ui->item7Button->setIconSize(QSize(40, 40));
        ui->item7Button->setVisible(false);
        //Radio
        ui->item8Button->setIcon(QIcon(":/earthItems/earthRadio.png"));
        ui->item8Button->setIconSize(QSize(40, 40));
        ui->item8Button->setVisible(false);
        //Space blanket
        ui->item9Button->setIcon(QIcon(":/earthItems/earthSpaceBlanket.png"));
        ui->item9Button->setIconSize(QSize(40, 40));
        ui->item9Button->setVisible(false);
        //        //Water boottle
        //        ui->item9Button->setIcon(QIcon(":/earthItems/earthWaterBottle.png"));
        //        ui->item9Button->setIconSize(QSize(40, 40));
        //        ui->item9Button->setVisible(false);

    }
    if(imagePath==":/images/moon.jpg")
    {
        //Dirt
        ui->item1Button->setIcon(QIcon(":/moonItems/moonDirt.png"));
        ui->item1Button->setIconSize(QSize(40, 40));
        ui->item1Button->setVisible(false);
        //Moon far side
        ui->item2Button->setIcon(QIcon(":/moonItems/moonNearSide.png"));
        ui->item2Button->setIconSize(QSize(40, 40));
        ui->item2Button->setVisible(false);
        //Maria
        ui->item3Button->setIcon(QIcon(":/moonItems/moonMaria.png"));
        ui->item3Button->setIconSize(QSize(40, 40));
        ui->item3Button->setVisible(false);
        //Flag
        ui->item4Button->setIcon(QIcon(":/moonItems/moonFlag.png"));
        ui->item4Button->setIconSize(QSize(40, 40));
        ui->item4Button->setVisible(false);
        //Moon near side
        ui->item5Button->setIcon(QIcon(":/moonItems/moonFarSide.png"));
        ui->item5Button->setIconSize(QSize(40, 40));
        ui->item5Button->setVisible(false);

        ui->item6Button->setVisible(false);
        ui->item7Button->setVisible(false);
        ui->item8Button->setVisible(false);
        ui->item9Button->setVisible(false);
    }

    if(imagePath==":/images/mercury.png")
    {
        //mercury mantle
        ui->item1Button->setIcon(QIcon(":/mercuryItems/mercuryMantle.png"));
        ui->item1Button->setIconSize(QSize(40, 40));
        ui->item1Button->setVisible(false);
        //mercury metal
        ui->item2Button->setIcon(QIcon(":/mercuryItems/mercuryMetalCore.png"));
        ui->item2Button->setIconSize(QSize(40, 40));
        ui->item2Button->setVisible(false);
        //mercury dirt
        ui->item3Button->setIcon(QIcon(":/mercuryItems/mercuryDirt.png"));
        ui->item3Button->setIconSize(QSize(40, 40));
        ui->item3Button->setVisible(false);
        //mercury crust
        ui->item4Button->setIcon(QIcon(":/mercuryItems/moonCrustSample.png"));
        ui->item4Button->setIconSize(QSize(40, 40));
        ui->item4Button->setVisible(false);

        ui->item5Button->setVisible(false);
        ui->item6Button->setVisible(false);
        ui->item7Button->setVisible(false);
        ui->item8Button->setVisible(false);
        ui->item9Button->setVisible(false);
    }

    if(imagePath==":/images/venus.jpg")
    {
        //venus magnet
        ui->item1Button->setIcon(QIcon(":/venusItems/venusMagneticFieldSample.png"));
        ui->item1Button->setIconSize(QSize(40, 40));
        ui->item1Button->setVisible(false);
        //venus mantle
        ui->item2Button->setIcon(QIcon(":/venusItems/venusRockyMantle.png"));
        ui->item2Button->setIconSize(QSize(40, 40));
        ui->item2Button->setVisible(false);
        //venus dirt
        ui->item3Button->setIcon(QIcon(":/venusItems/venusDirt.png"));
        ui->item3Button->setIconSize(QSize(40, 40));
        ui->item3Button->setVisible(false);

        ui->item4Button->setVisible(false);
        ui->item5Button->setVisible(false);
        ui->item6Button->setVisible(false);
        ui->item7Button->setVisible(false);
        ui->item8Button->setVisible(false);
        ui->item9Button->setVisible(false);

    }

    if(imagePath==":/images/mar.jpg")
    {
        //Soil Sample
        ui->item1Button->setIcon(QIcon(":/marsItems/marsSoil.png"));
        ui->item1Button->setIconSize(QSize(40, 40));
        ui->item1Button->setVisible(false);
        //Iron Sample
        ui->item2Button->setIcon(QIcon(":/marsItems/marsIron.png"));
        ui->item2Button->setIconSize(QSize(40, 40));
        ui->item2Button->setVisible(false);
        //rover
        ui->item3Button->setIcon(QIcon(":/marsItems/marsrover.png"));
        ui->item3Button->setIconSize(QSize(40, 40));
        ui->item3Button->setVisible(false);

        ui->item4Button->setVisible(false);
        ui->item5Button->setVisible(false);
        ui->item6Button->setVisible(false);
        ui->item7Button->setVisible(false);
        ui->item8Button->setVisible(false);
        ui->item9Button->setVisible(false);

    }

    if(imagePath==":/images/jupiter.png")
    {
        //Core
        ui->item1Button->setIcon(QIcon(":/jupiterItems/jupiterCore.png"));
        ui->item1Button->setIconSize(QSize(40, 40));
        ui->item1Button->setVisible(false);
        //UO
        ui->item2Button->setIcon(QIcon(":/jupiterItems/jupiterLiquidMetalicHydrogen.png"));
        ui->item2Button->setIconSize(QSize(40, 40));
        ui->item2Button->setVisible(false);
        //Ice Particles
        ui->item3Button->setIcon(QIcon(":/jupiterItems/jupiterIceParticles.png"));
        ui->item3Button->setIconSize(QSize(40, 40));
        ui->item3Button->setVisible(false);

        ui->item4Button->setVisible(false);
        ui->item5Button->setVisible(false);
        ui->item6Button->setVisible(false);
        ui->item7Button->setVisible(false);
        ui->item8Button->setVisible(false);
        ui->item9Button->setVisible(false);

    }

    if(imagePath==":/images/saturn.png")
    {
        //Core
        ui->item1Button->setIcon(QIcon(":/saturnItems/saturnCore.png"));
        ui->item1Button->setIconSize(QSize(40, 40));
        ui->item1Button->setVisible(false);
        //UO
        ui->item2Button->setIcon(QIcon(":/saturnItems/saturnIceParticles copy 4.png"));
        ui->item2Button->setIconSize(QSize(40, 40));
        ui->item2Button->setVisible(false);
        //Ice Particles
        ui->item3Button->setIcon(QIcon(":/saturnItems/saturnLiquidHydrogen.png"));
        ui->item3Button->setIconSize(QSize(40, 40));
        ui->item3Button->setVisible(false);

        ui->item4Button->setVisible(false);
        ui->item5Button->setVisible(false);
        ui->item6Button->setVisible(false);
        ui->item7Button->setVisible(false);
        ui->item8Button->setVisible(false);
        ui->item9Button->setVisible(false);

    }
}

void MainWindow::earthLevel()
{
    //setting water bottle
    qDebug() << "test" << QString::fromStdString(earth.e1.souvenirImage);
    QImage e1Image = QImage(QString::fromStdString(earth.e1.souvenirImage));
    QPixmap e1Item = QPixmap::fromImage(e1Image.scaled(100, 100, Qt::KeepAspectRatio));
    earth.e1.pixmapItem = backgroundScene ->addPixmap(e1Item);
    earth.e1.pixmapItem->setPos(300, 300);

    //setting comb
    QImage e2Image = QImage(QString::fromStdString(earth.e2.souvenirImage));
    QPixmap e2Item = QPixmap::fromImage(e2Image.scaled(50, 50, Qt::KeepAspectRatio));
    earth.e2.pixmapItem = backgroundScene ->addPixmap(e2Item);
    earth.e2.pixmapItem->setPos(600, 450);

    //setting Ipod
    QImage e3Image = QImage(QString::fromStdString(earth.e3.souvenirImage));
    QPixmap e3Item = QPixmap::fromImage(e3Image.scaled(50, 50, Qt::KeepAspectRatio));
    earth.e3.pixmapItem = backgroundScene ->addPixmap(e3Item);
    earth.e3.pixmapItem->setPos(254, 454);

    //setting phone
    QImage e4Image = QImage(QString::fromStdString(earth.e4.souvenirImage));
    QPixmap e4Item = QPixmap::fromImage(e4Image.scaled(50, 50, Qt::KeepAspectRatio));
    earth.e4.pixmapItem = backgroundScene ->addPixmap(e4Item);
    earth.e4.pixmapItem->setPos(354, 454);

    //setting lighter
    QImage e5Image = QImage(QString::fromStdString(earth.e5.souvenirImage));
    QPixmap e5Item = QPixmap::fromImage(e5Image.scaled(50, 50, Qt::KeepAspectRatio));
    earth.e5.pixmapItem = backgroundScene ->addPixmap(e5Item);
    earth.e5.pixmapItem->setPos(750, 450);

    //setting oxygen
    QImage e6Image = QImage(QString::fromStdString(earth.e6.souvenirImage));
    QPixmap e6Item = QPixmap::fromImage(e6Image.scaled(100, 100, Qt::KeepAspectRatio));
    earth.e6.pixmapItem = backgroundScene ->addPixmap(e6Item);
    earth.e6.pixmapItem->setPos(124, 354);

    //setting food
    QImage e7Image = QImage(QString::fromStdString(earth.e7.souvenirImage));
    QPixmap e7Item = QPixmap::fromImage(e7Image.scaled(100, 100, Qt::KeepAspectRatio));
    earth.e7.pixmapItem = backgroundScene ->addPixmap(e7Item);
    earth.e7.pixmapItem->setPos(900, 350);

    //setting radio
    QImage e8Image = QImage(QString::fromStdString(earth.e8.souvenirImage));
    QPixmap e8Item = QPixmap::fromImage(e8Image.scaled(50, 50, Qt::KeepAspectRatio));
    earth.e8.pixmapItem = backgroundScene ->addPixmap(e8Item);
    earth.e8.pixmapItem->setPos(400, 300);

    //setting space blanket
    QImage e9Image = QImage(QString::fromStdString(earth.e9.souvenirImage));
    QPixmap e9Item = QPixmap::fromImage(e9Image.scaled(60, 60, Qt::KeepAspectRatio));
    earth.e9.pixmapItem = backgroundScene ->addPixmap(e9Item);
    earth.e9.pixmapItem->setPos(450, 400);

    //    //setting food
    //    QImage e9Image = QImage(QString::fromStdString(earth.e9.souvenirImage));
    //    QPixmap e9Item = QPixmap::fromImage(e9Image.scaled(100, 100, Qt::KeepAspectRatio));
    //    QGraphicsPixmapItem *e9pixItem = backgroundScene ->addPixmap(e9Item);
    //    e9pixItem->setPos(550, 350);


    //    earth.e1.pixmapItem = backgroundScene ->addPixmap(e1Item);

    //    Souvenir *e1Pointer = &earth.e1;
    //
    //connect(e1Pointer, &Souvenir::HoverTextSignal, this, &MainWindow::SouvenirHoverSlot);


    //    QGraphicsPixmapItem.hoverEnterEvent();


    ui->graphicsView->setScene(backgroundScene);
}

void MainWindow::mercuryLevel()
{
    //mercury mantle sample
    QImage m1Image = QImage(QString::fromStdString(mercury.m1.souvenirImage));
    QPixmap m1Item = QPixmap::fromImage(m1Image.scaled(100, 100, Qt::KeepAspectRatio));
    mercury.m1.pixmapItem = backgroundScene ->addPixmap(m1Item);
    mercury.m1.pixmapItem->setPos(300, 450);

    //mercury metal core
    QImage m2Image = QImage(QString::fromStdString(mercury.m2.souvenirImage));
    QPixmap m2Item = QPixmap::fromImage(m2Image.scaled(100, 100, Qt::KeepAspectRatio));
    mercury.m2.pixmapItem = backgroundScene ->addPixmap(m2Item);
    mercury.m2.pixmapItem->setPos(400, 500);

    //mercury dirt
    QImage m3Image = QImage(QString::fromStdString(mercury.m3.souvenirImage));
    QPixmap m3Item = QPixmap::fromImage(m3Image.scaled(100, 100, Qt::KeepAspectRatio));
    mercury.m3.pixmapItem = backgroundScene ->addPixmap(m3Item);
    mercury.m3.pixmapItem->setPos(200, 400);

    //mercury crust
    QImage m5Image = QImage(QString::fromStdString(mercury.m4.souvenirImage));
    QPixmap m5Item = QPixmap::fromImage(m5Image.scaled(100, 100, Qt::KeepAspectRatio));
    mercury.m4.pixmapItem = backgroundScene ->addPixmap(m5Item);
    mercury.m4.pixmapItem->setPos(534, 354);

    ui->graphicsView->setScene(backgroundScene);
}

void MainWindow::venusLevel()
{
    //
    QImage v1Image = QImage(QString::fromStdString(venus.v1.souvenirImage));
    QPixmap v1Item = QPixmap::fromImage(v1Image.scaled(100, 100, Qt::KeepAspectRatio));
    venus.v1.pixmapItem = backgroundScene ->addPixmap(v1Item);
    venus.v1.pixmapItem->setPos(400, 500);


    //venus mantle
    QImage v2Image = QImage(QString::fromStdString(venus.v2.souvenirImage));
    QPixmap v2Item = QPixmap::fromImage(v2Image.scaled(100, 100, Qt::KeepAspectRatio));
    venus.v2.pixmapItem = backgroundScene ->addPixmap(v2Item);
    venus.v2.pixmapItem->setPos(200, 400);


    //venus dirt
    QImage v3Image = QImage(QString::fromStdString(venus.v3.souvenirImage));
    QPixmap v3Item = QPixmap::fromImage(v3Image.scaled(100, 100, Qt::KeepAspectRatio));
    venus.v3.pixmapItem = backgroundScene ->addPixmap(v3Item);
    venus.v3.pixmapItem->setPos(534, 354);

    ui->item4Button->setVisible(false);
    ui->item5Button->setVisible(false);
    ui->item6Button->setVisible(false);
    ui->item7Button->setVisible(false);
    ui->item8Button->setVisible(false);
    ui->item9Button->setVisible(false);
    ui->item10Button->setVisible(false);

    //    QImage v4Image = QImage(QString::fromStdString(venus.v2.souvenirImage));
    //    QPixmap v4Item = QPixmap::fromImage(v2Image.scaled(100, 100, Qt::KeepAspectRatio));
    //    QGraphicsPixmapItem *v4pixItem = backgroundScene ->addPixmap(v4Item);
    //    v1pixItem->setPos(500, 400);

     ui->graphicsView->setScene(backgroundScene);
}
void MainWindow::moonLevel()
{
    //moon dirt
    QImage m1Image = QImage(QString::fromStdString(moon.m4.souvenirImage));
    QPixmap m1Item = QPixmap::fromImage(m1Image.scaled(100, 100, Qt::KeepAspectRatio));
    moon.m4.pixmapItem = backgroundScene ->addPixmap(m1Item);
    moon.m4.pixmapItem->setPos(300, 450);

    //far side
    QImage m2Image = QImage(QString::fromStdString(moon.m2.souvenirImage));
    QPixmap m2Item = QPixmap::fromImage(m2Image.scaled(100, 100, Qt::KeepAspectRatio));
    moon.m2.pixmapItem = backgroundScene ->addPixmap(m2Item);
    moon.m2.pixmapItem->setPos(100, 500);
    ui->graphicsView->setScene(backgroundScene);

    //maria
    QImage m3Image = QImage(QString::fromStdString(moon.m3.souvenirImage));
    QPixmap m3Item = QPixmap::fromImage(m3Image.scaled(100, 100, Qt::KeepAspectRatio));
    moon.m3.pixmapItem = backgroundScene ->addPixmap(m3Item);
    moon.m3.pixmapItem->setPos(200, 400);

    //flag
    QImage m5Image = QImage(QString::fromStdString(moon.m5.souvenirImage));
    QPixmap m5Item = QPixmap::fromImage(m5Image.scaled(300, 300, Qt::KeepAspectRatio));
    moon.m5.pixmapItem = backgroundScene ->addPixmap(m5Item);
    moon.m5.pixmapItem->setPos(534, 354);

    //moon near side
    QImage m6Image = QImage(QString::fromStdString(moon.m1.souvenirImage));
    QPixmap m6Item = QPixmap::fromImage(m6Image.scaled(150, 150, Qt::KeepAspectRatio));
    moon.m1.pixmapItem= backgroundScene ->addPixmap(m6Item);
    moon.m1.pixmapItem->setPos(234, 554);

    ui->item6Button->setVisible(false);
    ui->item7Button->setVisible(false);
    ui->item8Button->setVisible(false);
    ui->item9Button->setVisible(false);
    ui->item10Button->setVisible(false);

    ui->graphicsView->setScene(backgroundScene);
}
void MainWindow::UranusLevel()
{
    //uranus core
    qDebug() << "test" << QString::fromStdString(uranus.u1.souvenirImage);
    QImage u1Image = QImage(QString::fromStdString(uranus.u1.souvenirImage));
    QPixmap u1Item = QPixmap::fromImage(u1Image.scaled(100, 100, Qt::KeepAspectRatio));
    uranus.u1.pixmapItem = backgroundScene ->addPixmap(u1Item);
    uranus.u1.pixmapItem ->setPos(300, 300);
    ui->graphicsView->setScene(backgroundScene);

    //uranus ice particles
    qDebug() << "test" << QString::fromStdString(uranus.u2.souvenirImage);
    QImage u2Image = QImage(QString::fromStdString(uranus.u2.souvenirImage));
    QPixmap u2Item = QPixmap::fromImage(u2Image.scaled(100, 100, Qt::KeepAspectRatio));
    uranus.u2.pixmapItem = backgroundScene ->addPixmap(u2Item);
    uranus.u2.pixmapItem ->setPos(600, 400);
    ui->graphicsView->setScene(backgroundScene);

    //uranus liquid hydrogen
    qDebug() << "test" << QString::fromStdString(uranus.u3.souvenirImage);
    QImage u3Image = QImage(QString::fromStdString(uranus.u3.souvenirImage));
    QPixmap u3Item = QPixmap::fromImage(u3Image.scaled(100, 100, Qt::KeepAspectRatio));
    uranus.u3.pixmapItem = backgroundScene ->addPixmap(u3Item);
    uranus.u3.pixmapItem ->setPos(100, 450);
    ui->graphicsView->setScene(backgroundScene);


    //set the ui buttons icons
    ui->item1Button->setIcon(QIcon(QString::fromStdString(uranus.u1.souvenirImage)));
    ui->item1Button->setIconSize(QSize(30, 30));
    ui->item1Button->setVisible(false);

    ui->item2Button->setIcon(QIcon(QString::fromStdString(uranus.u2.souvenirImage)));
    ui->item2Button->setIconSize(QSize(30, 30));
    ui->item2Button->setVisible(false);

    ui->item3Button->setIcon(QIcon(QString::fromStdString(uranus.u3.souvenirImage)));
    ui->item3Button->setIconSize(QSize(30, 30));
    ui->item3Button->setVisible(false);

    ui->item4Button->setVisible(false);
    ui->item5Button->setVisible(false);
    ui->item6Button->setVisible(false);
    ui->item7Button->setVisible(false);
    ui->item8Button->setVisible(false);
    ui->item9Button->setVisible(false);
    ui->item10Button->setVisible(false);
}


void MainWindow::MarsLevel()
{
    //mars core
    qDebug() << "test" << QString::fromStdString(mars.m1.souvenirImage);
    QImage m1Image = QImage(QString::fromStdString(mars.m1.souvenirImage));
    QPixmap m1Item = QPixmap::fromImage(m1Image.scaled(100, 100, Qt::KeepAspectRatio));
    mars.m1.pixmapItem = backgroundScene ->addPixmap(m1Item);
    mars.m1.pixmapItem ->setPos(300, 300);
    ui->graphicsView->setScene(backgroundScene);

    //mars iron sample
    qDebug() << "test" << QString::fromStdString(mars.m2.souvenirImage);
    QImage m2Image = QImage(QString::fromStdString(mars.m2.souvenirImage));
    QPixmap m2Item = QPixmap::fromImage(m2Image.scaled(100, 100, Qt::KeepAspectRatio));
    mars.m2.pixmapItem = backgroundScene ->addPixmap(m2Item);
    mars.m2.pixmapItem ->setPos(600, 400);
    ui->graphicsView->setScene(backgroundScene);

    //mars rover
    qDebug() << "test" << QString::fromStdString(mars.m3.souvenirImage);
    QImage m3Image = QImage(QString::fromStdString(mars.m3.souvenirImage));
    QPixmap m3Item = QPixmap::fromImage(m3Image.scaled(300, 300, Qt::KeepAspectRatio));
    mars.m3.pixmapItem = backgroundScene ->addPixmap(m3Item);
    mars.m3.pixmapItem ->setPos(25, 300);
    ui->graphicsView->setScene(backgroundScene);


    //set the ui buttons icons
    ui->item1Button->setIcon(QIcon(QString::fromStdString(mars.m1.souvenirImage)));
    ui->item1Button->setIconSize(QSize(30, 30));
    ui->item1Button->setVisible(false);

    ui->item2Button->setIcon(QIcon(QString::fromStdString(mars.m2.souvenirImage)));
    ui->item2Button->setIconSize(QSize(30, 30));
    ui->item2Button->setVisible(false);

    ui->item3Button->setIcon(QIcon(QString::fromStdString(mars.m3.souvenirImage)));
    ui->item3Button->setIconSize(QSize(30, 30));
    ui->item3Button->setVisible(false);

    ui->item4Button->setVisible(false);
    ui->item5Button->setVisible(false);
    ui->item6Button->setVisible(false);
    ui->item7Button->setVisible(false);
    ui->item8Button->setVisible(false);
    ui->item9Button->setVisible(false);
    ui->item10Button->setVisible(false);
}


void MainWindow::SaturnLevel()
{
    //saturn core sample
    qDebug() << "test" << QString::fromStdString(saturn.s1.souvenirImage);
    QImage s1Image = QImage(QString::fromStdString(saturn.s1.souvenirImage));
    QPixmap s1Item = QPixmap::fromImage(s1Image.scaled(100, 100, Qt::KeepAspectRatio));
    saturn.s1.pixmapItem = backgroundScene ->addPixmap(s1Item);
    saturn.s1.pixmapItem ->setPos(300, 300);
    ui->graphicsView->setScene(backgroundScene);

    //saturn unidentified object (liquid hydrogen)
    qDebug() << "test" << QString::fromStdString(saturn.s2.souvenirImage);
    QImage s2Image = QImage(QString::fromStdString(saturn.s2.souvenirImage));
    QPixmap s2Item = QPixmap::fromImage(s2Image.scaled(100, 100, Qt::KeepAspectRatio));
    saturn.s2.pixmapItem = backgroundScene ->addPixmap(s2Item);
    saturn.s2.pixmapItem ->setPos(600, 400);
    ui->graphicsView->setScene(backgroundScene);

    //saturn ice particles
    qDebug() << "test" << QString::fromStdString(saturn.s3.souvenirImage);
    QImage s3Image = QImage(QString::fromStdString(saturn.s3.souvenirImage));
    QPixmap s3Item = QPixmap::fromImage(s3Image.scaled(100, 100, Qt::KeepAspectRatio));
    saturn.s3.pixmapItem = backgroundScene ->addPixmap(s3Item);
    saturn.s3.pixmapItem ->setPos(100, 450);
    ui->graphicsView->setScene(backgroundScene);


    //set the ui buttons icons
    ui->item1Button->setIcon(QIcon(QString::fromStdString(saturn.s1.souvenirImage)));
    ui->item1Button->setIconSize(QSize(30, 30));
    ui->item1Button->setVisible(false);

    ui->item2Button->setIcon(QIcon(QString::fromStdString(saturn.s2.souvenirImage)));
    ui->item2Button->setIconSize(QSize(30, 30));
    ui->item2Button->setVisible(false);

    ui->item3Button->setIcon(QIcon(QString::fromStdString(saturn.s3.souvenirImage)));
    ui->item3Button->setIconSize(QSize(30, 30));
    ui->item3Button->setVisible(false);

    ui->item4Button->setVisible(false);
    ui->item5Button->setVisible(false);
    ui->item6Button->setVisible(false);
    ui->item7Button->setVisible(false);
    ui->item8Button->setVisible(false);
    ui->item9Button->setVisible(false);
    ui->item10Button->setVisible(false);
}

void MainWindow::NeptuneLevel()
{
    //saturn core sample
    qDebug() << "test" << QString::fromStdString(neptune.n1.souvenirImage);
    QImage s1Image = QImage(QString::fromStdString(neptune.n1.souvenirImage));
    QPixmap s1Item = QPixmap::fromImage(s1Image.scaled(100, 100, Qt::KeepAspectRatio));
    neptune.n1.pixmapItem = backgroundScene ->addPixmap(s1Item);
    neptune.n1.pixmapItem ->setPos(300, 300);
    ui->graphicsView->setScene(backgroundScene);

    //saturn unidentified object (liquid hydrogen)
    qDebug() << "test" << QString::fromStdString(neptune.n2.souvenirImage);
    QImage s2Image = QImage(QString::fromStdString(neptune.n2.souvenirImage));
    QPixmap s2Item = QPixmap::fromImage(s2Image.scaled(100, 100, Qt::KeepAspectRatio));
    neptune.n2.pixmapItem = backgroundScene ->addPixmap(s2Item);
    neptune.n2.pixmapItem ->setPos(600, 400);
    ui->graphicsView->setScene(backgroundScene);

    //saturn ice particles
    qDebug() << "test" << QString::fromStdString(neptune.n3.souvenirImage);
    QImage s3Image = QImage(QString::fromStdString(neptune.n3.souvenirImage));
    QPixmap s3Item = QPixmap::fromImage(s3Image.scaled(100, 100, Qt::KeepAspectRatio));
    neptune.n3.pixmapItem = backgroundScene ->addPixmap(s3Item);
    neptune.n3.pixmapItem ->setPos(100, 450);
    ui->graphicsView->setScene(backgroundScene);


    //set the ui buttons icons
    ui->item1Button->setIcon(QIcon(QString::fromStdString(neptune.n1.souvenirImage)));
    ui->item1Button->setIconSize(QSize(30, 30));
    ui->item1Button->setVisible(false);

    ui->item2Button->setIcon(QIcon(QString::fromStdString(neptune.n2.souvenirImage)));
    ui->item2Button->setIconSize(QSize(30, 30));
    ui->item2Button->setVisible(false);

    ui->item3Button->setIcon(QIcon(QString::fromStdString(neptune.n3.souvenirImage)));
    ui->item3Button->setIconSize(QSize(30, 30));
    ui->item3Button->setVisible(false);

    ui->item4Button->setVisible(false);
    ui->item5Button->setVisible(false);
    ui->item6Button->setVisible(false);
    ui->item7Button->setVisible(false);
    ui->item8Button->setVisible(false);
    ui->item9Button->setVisible(false);
    ui->item10Button->setVisible(false);
}
void MainWindow::JupiterLevel()
{
    //saturn core sample
    qDebug() << "test" << QString::fromStdString(jupiter.j1.souvenirImage);
    QImage s1Image = QImage(QString::fromStdString(jupiter.j1.souvenirImage));
    QPixmap s1Item = QPixmap::fromImage(s1Image.scaled(100, 100, Qt::KeepAspectRatio));
    jupiter.j1.pixmapItem = backgroundScene ->addPixmap(s1Item);
    jupiter.j1.pixmapItem ->setPos(300, 300);
    ui->graphicsView->setScene(backgroundScene);

    //saturn unidentified object (liquid hydrogen)
    qDebug() << "test" << QString::fromStdString(jupiter.j2.souvenirImage);
    QImage s2Image = QImage(QString::fromStdString(jupiter.j2.souvenirImage));
    QPixmap s2Item = QPixmap::fromImage(s2Image.scaled(100, 100, Qt::KeepAspectRatio));
    jupiter.j2.pixmapItem = backgroundScene ->addPixmap(s2Item);
    jupiter.j2.pixmapItem ->setPos(600, 400);
    ui->graphicsView->setScene(backgroundScene);

    //saturn ice particles
    qDebug() << "test" << QString::fromStdString(jupiter.j3.souvenirImage);
    QImage s3Image = QImage(QString::fromStdString(jupiter.j3.souvenirImage));
    QPixmap s3Item = QPixmap::fromImage(s3Image.scaled(100, 100, Qt::KeepAspectRatio));
    jupiter.j3.pixmapItem = backgroundScene ->addPixmap(s3Item);
    jupiter.j3.pixmapItem ->setPos(100, 450);
    ui->graphicsView->setScene(backgroundScene);


    //set the ui buttons icons
    ui->item1Button->setIcon(QIcon(QString::fromStdString(jupiter.j1.souvenirImage)));
    ui->item1Button->setIconSize(QSize(30, 30));
    ui->item1Button->setVisible(false);

    ui->item2Button->setIcon(QIcon(QString::fromStdString(jupiter.j2.souvenirImage)));
    ui->item2Button->setIconSize(QSize(30, 30));
    ui->item2Button->setVisible(false);

    ui->item3Button->setIcon(QIcon(QString::fromStdString(jupiter.j3.souvenirImage)));
    ui->item3Button->setIconSize(QSize(30, 30));
    ui->item3Button->setVisible(false);

    ui->item4Button->setVisible(false);
    ui->item5Button->setVisible(false);
    ui->item6Button->setVisible(false);
    ui->item7Button->setVisible(false);
    ui->item8Button->setVisible(false);
    ui->item9Button->setVisible(false);
    ui->item10Button->setVisible(false);

}

void MainWindow::SouvenirHoverSlot(std::string name, std::string description)
{
    qDebug() << "name" <<QString::fromStdString(name);
    qDebug() << "name" <<QString::fromStdString(description);
}


void MainWindow::checkClick()
{
    qDebug()<<"button has been clicked";
}

//Water
void MainWindow::item1ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e1.pixmapItem->setVisible(1);
        ui->item1Button->setVisible(0);
    }
    if(imagePath==":/images/moon.jpg")
    {
        moon.m4.pixmapItem->setVisible(1);
        ui->item1Button->setVisible(0);
    }
    if(imagePath==":/images/mercury.png")
    {
        mercury.m1.pixmapItem->setVisible(1);
        ui->item1Button->setVisible(0);
    }
    if(imagePath==":/images/venus.jpg")
    {
        venus.v1.pixmapItem->setVisible(1);
        ui->item1Button->setVisible(0);
    }
    if(imagePath ==":/images/mar.jpg")
    {
        ui->item1Button->setVisible(false);
        mars.m1.pixmapItem->setVisible(true);
    }
    if(imagePath ==":/images/saturn.png")
    {
        ui->item1Button->setVisible(false);
        saturn.s1.pixmapItem->setVisible(true);
    }
    if(imagePath ==":/images/uranus.png")
    {
        ui->item1Button->setVisible(false);
        uranus.u1.pixmapItem->setVisible(true);
    }
    if(imagePath == ":/images/neptune.png")
    {
        ui->item1Button->setVisible(false);
        neptune.n1.pixmapItem->setVisible(true);
    }
    if(imagePath == ":/images/jupiter.png")
    {
        ui->item1Button->setVisible(false);
        jupiter.j1.pixmapItem->setVisible(true);
    }
}

//comb
void MainWindow::item2ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e2.pixmapItem->setVisible(1);
        ui->item2Button->setVisible(0);
    }

    if(imagePath==":/images/moon.jpg")
    {
        moon.m1.pixmapItem->setVisible(1);
        ui->item2Button->setVisible(0);
    }
    if(imagePath==":/images/mercury.png")
    {
        mercury.m2.pixmapItem->setVisible(1);
        ui->item2Button->setVisible(0);
    }
    if(imagePath==":/images/venus.jpg")
    {
        venus.v2.pixmapItem->setVisible(1);
        ui->item2Button->setVisible(0);
    }

    if(imagePath ==":/images/mar.jpg")
    {
        ui->item2Button->setVisible(false);
        mars.m2.pixmapItem->setVisible(true);
    }
    if(imagePath ==":/images/saturn.png")
    {
        ui->item2Button->setVisible(false);
        saturn.s2.pixmapItem->setVisible(true);
    }
    if(imagePath ==":/images/uranus.png")
    {
        ui->item2Button->setVisible(false);
        uranus.u2.pixmapItem->setVisible(true);
    }
    if(imagePath == ":/images/neptune.png")
    {
        ui->item2Button->setVisible(false);
        neptune.n2.pixmapItem->setVisible(true);
    }
    if(imagePath == ":/images/jupiter.png")
    {
        ui->item2Button->setVisible(false);
        jupiter.j2.pixmapItem->setVisible(true);
    }
}

//iPod
void MainWindow::item3ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e3.pixmapItem->setVisible(1);
        ui->item3Button->setVisible(0);
    }

    if(imagePath==":/images/moon.jpg")
    {
        moon.m3.pixmapItem->setVisible(1);
        ui->item3Button->setVisible(0);
    }
    if(imagePath==":/images/mercury.png")
    {
        mercury.m3.pixmapItem->setVisible(1);
        ui->item3Button->setVisible(0);
    }
    if(imagePath==":/images/venus.jpg")
    {
        venus.v3.pixmapItem->setVisible(1);
        ui->item3Button->setVisible(0);
    }
    if(imagePath ==":/images/mar.jpg")
    {
        ui->item3Button->setVisible(false);
        mars.m3.pixmapItem->setVisible(true);
    }
    if(imagePath ==":/images/saturn.png")
    {
        ui->item3Button->setVisible(false);
        saturn.s3.pixmapItem->setVisible(true);
    }
    if(imagePath ==":/images/uranus.png")
    {
        ui->item3Button->setVisible(false);
        uranus.u3.pixmapItem->setVisible(true);
    }
    if(imagePath == ":/images/neptune.png")
    {
        ui->item3Button->setVisible(false);
        neptune.n3.pixmapItem->setVisible(true);
    }
    if(imagePath == ":/images/jupiter.png")
    {
        ui->item3Button->setVisible(false);
        jupiter.j3.pixmapItem->setVisible(true);
    }
}

//cell
void MainWindow::item4ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e4.pixmapItem->setVisible(1);
        ui->item4Button->setVisible(0);
    }

    if(imagePath==":/images/moon.jpg")
    {
        moon.m5.pixmapItem->setVisible(1);
        ui->item4Button->setVisible(0);
    }
    if(imagePath==":/images/mercury.png")
    {
        mercury.m4.pixmapItem->setVisible(1);
        ui->item4Button->setVisible(0);
    }
}

//lighter
void MainWindow::item5ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e5.pixmapItem->setVisible(1);
        ui->item5Button->setVisible(0);
    }

    if(imagePath==":/images/moon.jpg")
    {
        moon.m2.pixmapItem->setVisible(1);
        ui->item5Button->setVisible(0);
    }
}

//oxygen
void MainWindow::item6ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e6.pixmapItem->setVisible(1);
        ui->item6Button->setVisible(0);
    }
}

//food
void MainWindow::item7ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e7.pixmapItem->setVisible(1);
        ui->item7Button->setVisible(0);
    }
}

//radio
void MainWindow::item8ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e8.pixmapItem->setVisible(1);
        ui->item8Button->setVisible(0);
    }
}

//space blanket
void MainWindow::item9ButtonSlot()
{
    if(imagePath==":/images/Earth.jpg")
    {
        earth.e9.pixmapItem->setVisible(1);
        ui->item9Button->setVisible(0);
    }
}

void MainWindow::playAudio()
{
    sf::SoundBuffer buffer;
    sf::Sound sound;
    QString s = ":/music/music.wav";
    //    if(buffer.loadFromFile("music.wav"))
    //    {
    qDebug()<<"loaded";
    //        sound.setBuffer(buffer);
    //        sound.play();
    //    }

    //    sf::Music music;
    //    if(music.openFromFile(":/music/music.wav"))
    //        music.play();

}


void MainWindow::openJournal(){
    winJournal= new Journal(this);
    winJournal->show();
}

void MainWindow::on_journalButton_clicked()
{
    openJournal();
}

void MainWindow:: openBackpack(){
    winBackpack = new Backpack(this);
    winBackpack->show();
}

void MainWindow::on_backpackButton_clicked()
{
    openBackpack();
}

void MainWindow::on_jump_clicked()
{
    Planets planets;
    int pixelsPerMeter = 50;
    int characterHeight = 1.5; //Meters
    int characterMass = 50;  //Kilograms
    float planetGravity = planets.planetGravityList[animationCount];    //Create the planet ground using Box2D (from Box2D's Hello World code)
    b2Vec2 gravity(0.0f, planetGravity);
    b2World world(gravity);
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 1.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(250.0f, 0.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Create the moving object (jumping character) using Box2D (from Box2D's Hello World code)
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(200.0f, 2.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = characterMass; //Box area is 1
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    //Jumping - add momentum to the character (from http://www.iforce2d.net/b2dtut/jumping)
    float impulse = body->GetMass() * 3;
    body->ApplyLinearImpulse( b2Vec2(0,impulse), body->GetWorldCenter(), false );

    //Draw the character and ground on the scene
    int numberOfSteps = 300;
    if (planetGravity > -1)
        numberOfSteps = 600;

    for (int32 i = 0; i < numberOfSteps; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();

        QTime endTime= QTime::currentTime().addMSecs(16.667);
        while (QTime::currentTime() < endTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        character->setPos(315, 500 - position.y*pixelsPerMeter);
        ui->graphicsView->setScene(backgroundScene);
    }
}

void MainWindow::goToPlanetAnimation(int animationCount)
{
    QVector<QString> planetImages;
    planetImages << ":/backpackItems/moonBackpack.png" << ":/backpackItems/sunBackpack.png" << ":/backpackItems/mercuryBackpack.png" << ":/backpackItems/venusBackpack.ico" <<
                    ":/backpackItems/marsBackpack.png" <<  ":/backpackItems/jupiterBackground.jpg" <<  ":/backpackItems/saturnBackpack.png"   <<
                    ":/backpackItems/uranusBackpack.png" <<  ":/backpackItems/neptuneBackground.jpeg"  << ":/backpackItems/plutoBackpack.png"   <<
                    ":/backpackItems/earthBackpack.ico";

    QGraphicsScene* scene = new QGraphicsScene(QRect(ui->graphicsView->pos().x(), ui->graphicsView->pos().y(), ui->graphicsView->width(), ui->graphicsView->height()));
    const QBrush black(Qt::black);
    const QBrush white(Qt::white);
    const QPen pen(Qt::transparent);
    ui->graphicsView->scene()->addRect((qreal)ui->graphicsView->pos().x(),(qreal)ui->graphicsView->pos().y(),ui->graphicsView->scene()->width(), ui->graphicsView->scene()->height(), pen, black);

    QGraphicsRectItem star(0,0,4,4);
    star.setBrush(white);
    ui->graphicsView->scene()->addItem(&star);

    QGraphicsRectItem star2(40,40,4,4);
    star2.setBrush(white);
    ui->graphicsView->scene()->addItem(&star2);

    QGraphicsRectItem star3(40,40,4,4);
    star3.setBrush(white);
    ui->graphicsView->scene()->addItem(&star3);

    QGraphicsRectItem star4(0,0,4,4);
    star4.setBrush(white);
    ui->graphicsView->scene()->addItem(&star4);

    QGraphicsRectItem star5(0,0,4,4);
    star5.setBrush(white);
    ui->graphicsView->scene()->addItem(&star5);

    QGraphicsRectItem star6(40,40,4,4);
    star6.setBrush(white);
    ui->graphicsView->scene()->addItem(&star6);

    QGraphicsRectItem* planet = new QGraphicsRectItem(ui->graphicsView->pos().x(),ui->graphicsView->pos().y(),75,75);
    QBrush brush(Qt::transparent);
    planet->setBrush(brush);
    planet->setPen(pen);
    QGraphicsPixmapItem planetImage(QPixmap::fromImage(QImage(planetImages[animationCount])).scaled(700,700,Qt::KeepAspectRatio));
    planetImage.setParentItem(planet);
    planet->setPos(315, 500);
    ui->graphicsView->scene()->addItem(planet);

    QGraphicsPixmapItem rocket;
    rocket.setPixmap(QPixmap::fromImage(QImage(":/images/rocketLiftOff.png").scaled(100, 900, Qt::KeepAspectRatio)));
    rocket.setPos(400,300);
    ui->graphicsView->scene()->addItem(&rocket);

    b2Vec2 gravity(0.0f, -4);
    b2World world(gravity);

    // Create a star
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(200.0f, 2.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 50; //Box area is 1
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i = 0; i < 310; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();

        QTime endTime= QTime::currentTime().addMSecs(16.667);
        while (QTime::currentTime() < endTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        star.setPos(ui->graphicsView->pos().x() + 130, ui->graphicsView->pos().y() - (100 + (int)position.y*50)%(int)ui->graphicsView->height());
        star2.setPos(ui->graphicsView->pos().x() + 380, ui->graphicsView->pos().y()  - (-300 + (int)position.y*50)%(int)ui->graphicsView->height());
        star3.setPos(ui->graphicsView->pos().x() + 500, ui->graphicsView->pos().y()  - (400 + (int)position.y*50)%(int)ui->graphicsView->height());
        star4.setPos(ui->graphicsView->pos().x() + 60, ui->graphicsView->pos().y()  - (270 + (int)position.y*50)%(int)ui->graphicsView->height());
        star5.setPos(ui->graphicsView->pos().x() + 625, ui->graphicsView->pos().y()  - (-200 + (int)position.y*50)%(int)ui->graphicsView->height());
        star6.setPos(ui->graphicsView->pos().x() + 205, ui->graphicsView->pos().y()  - (500 + (int)position.y*50)%(int)ui->graphicsView->height());
        planet->setPos(200,-2500-position.y*50);
        if (i > 210)
        {
            rocket.setPixmap(QPixmap::fromImage(QImage(":/images/rocketLiftOff.png").scaled(310-i, 900, Qt::KeepAspectRatio)));
            rocket.setPos(rocket.pos().x()+1, rocket.pos().y());
        }
    }

    QTime endTime= QTime::currentTime().addMSecs(1567);
    while (QTime::currentTime() < endTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}

/*
 * Help message for the player to know what to do and what planet they're on
 *
 */
void MainWindow::displayMessage()
{

    ui->instructions->setVisible(true);
    // Set font
    QFont font;
    font.setFamily("Courier");
    font.setPointSize(14);
    font.setBold(true);
    ui->instructions->setAlignment(Qt::AlignCenter);
    ui->instructions->setFont(font);

//    ui->instructions->setFont(QFont("Courier", 12));
//    ui->instructions->setWindowFlags(Qt::FramelessWindowHint);
//    ui->instructions->setFrameStyle(QFrame::NoFrame);
//    ui->instructions->setAlignment(Qt::AlignCenter);
    QPalette pal = palette();

    // text color (brush)
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);

    // background color (brush)
    QBrush brushBg(QColor(0, 0, 0, 155));
    brushBg.setStyle(Qt::SolidPattern);

    // set text
    pal.setBrush(QPalette::Active, QPalette::WindowText, brush);
    pal.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

    // set background color
    pal.setBrush(QPalette::Active, QPalette::Window, brushBg);
    pal.setBrush(QPalette::Inactive, QPalette::Window, brushBg);

    ui->instructions->setPalette(pal);

    ui->instructions->setAutoFillBackground(true);

//    ui->instructions->setStyleSheet("background-image:url(:/images/bubble3.png); background-attachment: fixed");

    if(imagePath==":/images/Earth.jpg")
    {
        ui->instructions->setText("We are on Earth! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/moon.jpg")
    {
        ui->instructions->setText("We are on the moon! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/sun.jpg")
    {
        ui->instructions->setText("     Oh no!\n"
                                  " We are too close to\n"
                                  " the sun! We better\n "
                                  "  go to the next\n"
                                  "  location quick!");
    }
    else if (imagePath==":/images/mercury.png")
    {
        ui->instructions->setText(" We are on Mercury! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/venus.jpg")
    {
        ui->instructions->setText(" We are on Venus! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/mar.jpg")
    {
        ui->instructions->setText(" We are on Mars! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/jupiter.png")
    {
        ui->instructions->setText(" We are on Jupiter! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/saturn.png")
    {
        ui->instructions->setText(" We are on Saturn! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/uranus.png")
    {
        ui->instructions->setText(" We are on Uranus! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/neptune.png")
    {
        ui->instructions->setText(" We are on Neptune! \n"
                                  " Help me collect what\n"
                                  " I need so we can get\n"
                                  " to the next location!");
    }
    else if (imagePath==":/images/pluto.png")
    {
        ui->instructions->setText(" We completed our\n"
                                  " mission! Thank you\n"
                                  "  for all your help! \n"
                                  "  See you next time!");
    }

}

void MainWindow::removeMessage()
{

    ui->instructions->setVisible(false);

}

void MainWindow::on_radioNasa_clicked()
{
    bool correctItems = false;

        //check earth items
        if(imagePath ==":/images/Earth.jpg")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== false && ui->item3Button == false && ui->item4Button->isVisible() == false && ui->item5Button->isVisible() == false && ui->item6Button->isVisible() == true && ui->item7Button->isVisible() == true && ui->item8Button->isVisible() == true && ui->item9Button->isVisible() == true)
            {
                std::cout << "here";
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);
                ui->item4Button->setVisible(false);
                ui->item5Button->setVisible(false);
                ui->item6Button->setVisible(false);
                ui->item7Button->setVisible(false);
                ui->item8Button->setVisible(false);
                ui->item9Button->setVisible(false);
                ui->item10Button->setVisible(false);

                earth.e1.pixmapItem->setVisible(true);
                earth.e2.pixmapItem->setVisible(true);
                earth.e3.pixmapItem->setVisible(true);
                earth.e4.pixmapItem->setVisible(true);
                earth.e5.pixmapItem->setVisible(true);
                earth.e6.pixmapItem->setVisible(true);
                earth.e7.pixmapItem->setVisible(true);
                earth.e8.pixmapItem->setVisible(true);
                earth.e9.pixmapItem->setVisible(true);
            }
        }

        //check moon items
        if(imagePath ==":/images/moon.jpg")
        {
            if (ui->item1Button->isVisible() == false && ui->item2Button->isVisible() == true && ui->item3Button->isVisible()== true && ui->item4Button->isVisible() == false
                    && ui->item5Button->isVisible() == true)
                correctItems = true;
            else
            {
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);
                ui->item4Button->setVisible(false);
                ui->item5Button->setVisible(false);

                moon.m1.pixmapItem->setVisible(true);
                moon.m2.pixmapItem->setVisible(true);
                moon.m3.pixmapItem->setVisible(true);
                moon.m4.pixmapItem->setVisible(true);
            }

        }

        //check mercury items
        if(imagePath == ":/images/mercury.png")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible() == true && ui->item3Button->isVisible()== false && ui->item4Button->isVisible() == true)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);
                ui->item4Button->setVisible(false);

                mercury.m1.pixmapItem->setVisible(true);
                mercury.m2.pixmapItem->setVisible(true);
                mercury.m3.pixmapItem->setVisible(true);
                mercury.m4.pixmapItem->setVisible(true);
            }
        }

        //check venus items
        if(imagePath == ":/images/venus.jpg")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible() == true && ui->item3Button->isVisible()== false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                venus.v1.pixmapItem->setVisible(true);
                venus.v1.pixmapItem->setVisible(true);
                venus.v1.pixmapItem->setVisible(true);
            }
        }

        //check mars items
        if(imagePath ==":/images/mar.jpg")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== false && ui->item3Button == false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                mars.m1.pixmapItem->setVisible(true);
                mars.m2.pixmapItem->setVisible(true);
                mars.m3.pixmapItem->setVisible(true);
            }
        }

            //check jupiter's items
            if(imagePath == ":/images/jupiter.png")
            {
                if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== true && ui->item3Button == false)
                {
                    correctItems = true;
                }
                else
                {
                    //takes all existing items out of backpack
                    ui->item1Button->setVisible(false);
                    ui->item2Button->setVisible(false);
                    ui->item3Button->setVisible(false);

                    jupiter.j1.pixmapItem->setVisible(true);
                    jupiter.j1.pixmapItem->setVisible(true);
                    jupiter.j1.pixmapItem->setVisible(true);
                }
            }

        //check saturn's items
        if(imagePath ==":/images/saturn.png")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== true && ui->item3Button == false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                saturn.s1.pixmapItem->setVisible(true);
                saturn.s2.pixmapItem->setVisible(true);
                saturn.s3.pixmapItem->setVisible(true);
            }
        }

        //check uranus's items
        if(imagePath ==":/images/uranus.png")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== true && ui->item3Button == false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                uranus.u1.pixmapItem->setVisible(true);
                uranus.u2.pixmapItem->setVisible(true);
                uranus.u3.pixmapItem->setVisible(true);
            }
        }

    //check neptune's items
        if(imagePath ==":/images/neptune.png")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== true && ui->item3Button == false)
            {
                correctItems = true;
            }

            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                neptune.n1.pixmapItem->setVisible(true);
                neptune.n2.pixmapItem->setVisible(true);
                neptune.n3.pixmapItem->setVisible(true);
            }
        }

        //check earth items
        if(imagePath ==":/images/Earth.jpg")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== false && ui->item3Button->isVisible()  == false && ui->item4Button->isVisible() == false && ui->item5Button->isVisible() == false && ui->item6Button->isVisible() == true && ui->item7Button->isVisible() == true && ui->item8Button->isVisible() == true && ui->item9Button->isVisible() == false && ui->item10Button->isVisible()== false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);
                ui->item4Button->setVisible(false);
                ui->item5Button->setVisible(false);
                ui->item6Button->setVisible(false);
                ui->item7Button->setVisible(false);
                ui->item8Button->setVisible(false);
                ui->item9Button->setVisible(false);
                ui->item10Button->setVisible(false);

                earth.e1.pixmapItem->setVisible(true);
                earth.e2.pixmapItem->setVisible(true);
                earth.e3.pixmapItem->setVisible(true);
                earth.e4.pixmapItem->setVisible(true);
                earth.e5.pixmapItem->setVisible(true);
                earth.e6.pixmapItem->setVisible(true);
                earth.e7.pixmapItem->setVisible(true);
                earth.e8.pixmapItem->setVisible(true);
                earth.e9.pixmapItem->setVisible(true);
            }
        }

        //check moon items
        if(imagePath ==":/images/moon.jpg")
        {

        }

        //check mercury items
        if(imagePath == ":/images/mercury.png")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible() == true && ui->item3Button->isVisible()== false && ui->item4Button->isVisible() == true)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);
                ui->item4Button->setVisible(false);

                mercury.m1.pixmapItem->setVisible(true);
                mercury.m2.pixmapItem->setVisible(true);
                mercury.m3.pixmapItem->setVisible(true);
                mercury.m4.pixmapItem->setVisible(true);
            }
        }

        //check venus items
        if(imagePath == ":/images/venus.jpg")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible() == true && ui->item3Button->isVisible()== false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                venus.v1.pixmapItem->setVisible(true);
                venus.v1.pixmapItem->setVisible(true);
                venus.v1.pixmapItem->setVisible(true);
            }
        }

        //check mars items
        if(imagePath ==":/images/mar.jpg")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== false && ui->item3Button->isVisible()  == false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                mars.m1.pixmapItem->setVisible(true);
                mars.m2.pixmapItem->setVisible(true);
                mars.m3.pixmapItem->setVisible(true);
            }
        }

        //    //check jupiter's items
        //    if(imagePath == ":/images/jupiter.png")
        //    {
        //        if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== true && ui->item3Button == false)
        //        {
        //            correctItems = true;
        //        }
        //        else
        //        {
        //            //takes all existing items out of backpack
        //            ui->item1Button->setVisible(false);
        //            ui->item2Button->setVisible(false);
        //            ui->item3Button->setVisible(false);

        //            jupiter.j1.pixmapItem->setVisible(true);
        //            jupiter.j1.pixmapItem->setVisible(true);
        //            jupiter.j1.pixmapItem->setVisible(true);
        //        }
        //    }

        //check saturn's items
        if(imagePath ==":/images/saturn.png")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== true && ui->item3Button->isVisible() == false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                saturn.s1.pixmapItem->setVisible(true);
                saturn.s2.pixmapItem->setVisible(true);
                saturn.s3.pixmapItem->setVisible(true);
            }
        }

        //check uranus's items
        if(imagePath ==":/images/uranus.png")
        {
            if (ui->item1Button->isVisible() == true && ui->item2Button->isVisible()== true && ui->item3Button->isVisible()  == false)
            {
                correctItems = true;
            }
            else
            {
                //takes all existing items out of backpack
                ui->item1Button->setVisible(false);
                ui->item2Button->setVisible(false);
                ui->item3Button->setVisible(false);

                uranus.u1.pixmapItem->setVisible(true);
                uranus.u2.pixmapItem->setVisible(true);
                uranus.u3.pixmapItem->setVisible(true);
            }
        }


        QMessageBox* Nasa = new QMessageBox();

        QVector<QString> numberOfSouvenirs;
        numberOfSouvenirs << "5" << "3" << "3" << "2" << "1" << "2" << "2" << "2" << "2";

          //  if (imagePath == ":/images/sun.png")
            //    Nasa->setText("AAH! The sun is really hot! You should probably get away from there");

            //else if (imagePath == ":/images/pluto.png")
              //  Nasa->setText("Congratulations! You've collected samples from all the planets in the Solar System. You can return to Earth now");

             if (correctItems == false)
               Nasa->setText("Your items are interesting, but maybe not the best possible ones. "
                             "You have room for " + numberOfSouvenirs[level] + " samples from this planet. ");
            else
            {
                Nasa->setText("Good job!");
                ui->nextPlanet->setEnabled(true);
            }
            Nasa->exec();
}
