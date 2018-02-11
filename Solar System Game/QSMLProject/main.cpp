#include <QApplication>
#include "mainwindow.h"
#include "mycanvas.h"
#include <QFrame>
#include <Box2D/Box2D.h>
#include <QDesktopWidget>
#include <QResource>
#include <string>
#include <qsfmlcanvas.h>
#include <SFML/Audio.hpp>
#include "loginform.h"
#include <QMediaPlayer>
#include <QSound>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    //QApplication a(argc, argv);
//    LoginForm w;
    MainWindow w;
    QSound sound(":/music/music.wav");
    sound.setLoops(QSound::Infinite);
    sound.play();
//    QMediaPlayer *mediaPlayer = new QMediaPlayer;
//    mediaPlayer->setMedia(QUrl(":/music/music.wav"));
//    mediaPlayer->setVolume(100);
//    mediaPlayer->play();
//    LoginForm w;


//    sf::Music music;
//    if(music.openFromFile(""))
//        music.play();

   w.show();
    return App.exec();
}

