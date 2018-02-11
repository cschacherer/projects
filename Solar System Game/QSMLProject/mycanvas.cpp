//#include "mycanvas.h"
//#include "mainwindow.h"
//#include <iostream>
//#include <SFML/Network.hpp>
//#include <string>
//#include <SFML/Graphics.hpp>
//#include <QDir>
//#include <QResource>
//#include <QDebug>
//#include <SFML/Window/Mouse.hpp>
//#include <SFML/Window/Event.hpp>
//#include <planets.h>
//#include <QDesktopWidget>
//#include <Box2D/Box2D.h>
//#include <QTimer>
//#include <QTime>
//#include <QCoreApplication>
//MyCanvas::MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLCanvas(Parent, Position, Size)
//{
//    surfaceImages.push_back(":/images/Earth.jpg");
//    surfaceImages.push_back(":/images/sun.jpg");
//    surfaceImages.push_back(":/images/venus.jpg");
//    surfaceImages.push_back(":/images/mar.jpg");

//}

//void MyCanvas::OnInit()
//{
//    //// Load the image
//    std::cout << "onInit" << std::endl;
//    QString dir = QDir::currentPath();
//    std::string utf8_text = dir.toUtf8().constData();
//    std::cout << "HELLO: " << utf8_text << std::endl;

//    QResource res(":/images/Earth.jpg");
//    QResource res2(":/images/smallerImage.png");
//    if (res.isCompressed()) {
//        QByteArray data = qUncompress(res.data(), res.size());
//        myImage.loadFromMemory(data.data(), data.size());
//    } else {
//        myImage.loadFromMemory(res.data(), res.size());
//    }

//    if (res2.isCompressed()) {
//        QByteArray data = qUncompress(res2.data(), res2.size());
//        myImage2.loadFromMemory(data.data(), data.size());
//    } else {
//        myImage2.loadFromMemory(res2.data(), res2.size());
//    }
//    //// Setup the background
//    //background.setTexture(bg);
//    //background.setPosition(0,0);

//    //// Setup the sprite
//    mySprite.setTexture(myImage);
//    mySprite.setPosition(0, 0);
//    mySprite.setOrigin(0,0);


//    mySprite2.setTexture(myImage2);
//    mySprite2.setPosition(-45, 180);
//    mySprite2.setOrigin(200,200);


//    std::cout << "setting the texture of the sprite" << std::endl;
//    //mySprite.setCenter(mySprite.GetSize() / 2.f);
//    //mySprite.setCenter(mySprite.GetSize() / 2.f);
//    myClock.restart();
//}

//void MyCanvas::OnUpdate()
//{
//    sf::RenderWindow::setFramerateLimit(60);

//    //// Clear screen
//    //RenderWindow::clear(sf::Color(255, 128, 0));
//    //sf::Vector2f spritePos = mySprite2.getPosition();
//    //    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(*this));
//    //    float angle = atan2(mousePos.y - spritePos.y, mousePos.x - spritePos.x) * 57.296f;
//    //mySprite2.setRotation(spritePos);

//    // Rotate the sprite
//    //mySprite2.rotate(myClock.getElapsedTime().asSeconds() * 100.f);


//    sf::Vector2f pos1 = (sf::Vector2<float>)(sf::Mouse::getPosition(*this));

//    // Draw it
//    RenderWindow::draw(background);
//    RenderWindow::draw(mySprite);
//    mySprite2.setPosition(pos1.x,pos1.y);
//    RenderWindow::draw(mySprite2);
//    sf::Event event;



//    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
//    {
//        qDebug()<<"mouse pressed";
//        int pixelsPerMeter = 50;
//        int characterHeight = 1.5; //Meters
//        int characterMass = 50;  //Kilograms
//        float planetGravity = -9.8 ;
//        //Create the planet ground using Box2D (from Box2D's Hello World code)
//        b2Vec2 gravity(0.0f, planetGravity);
//        b2World world(gravity);
//        float scale = 30;
//        b2BodyDef groundBodyDef;
//        groundBodyDef.position.Set(0.0f, 1.0f);
//        b2Body* groundBody = world.CreateBody(&groundBodyDef);
//        b2PolygonShape groundBox;
//        groundBox.SetAsBox(250.0f, 0.0f);
//        groundBody->CreateFixture(&groundBox, 0.0f);

//        // Create the moving object (jumping character) using Box2D (from Box2D's Hello World code)
//        b2BodyDef bodyDef;
//        bodyDef.type = b2_dynamicBody;
//        bodyDef.position.Set(100/scale, 100/scale);
//        b2Body* body = world.CreateBody(&bodyDef);
//        b2PolygonShape dynamicBox;
//        dynamicBox.SetAsBox(50/scale, 50/scale);
//        b2FixtureDef fixtureDef;
//        fixtureDef.shape = &dynamicBox;
//        fixtureDef.density = 1.0f;
//        fixtureDef.friction = 0.3f;
//        body->CreateFixture(&fixtureDef);

//        float32 timeStep = 1.0f / 60.0f;
//        int32 velocityIterations = 6;
//        int32 positionIterations = 2;


//        //Jumping - add momentum to the character (from http://www.iforce2d.net/b2dtut/jumping)
//        float impulse = body->GetMass() * 3;
//        body->ApplyLinearImpulse( b2Vec2(0,impulse), body->GetWorldCenter(), false );

//        b2Vec2 pos = body->GetPosition();
//        float32 angle = body->GetAngle();

//        mySprite2.setPosition(pos.x, pos.y);
//        //              mySprite2.setRotation(-(angle*(180/b2_pi)));

//        RenderWindow::draw(mySprite2);

//        RenderWindow::display();

//    }


//}
