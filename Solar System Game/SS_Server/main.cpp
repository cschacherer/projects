#include <QCoreApplication>
#include "server.h"
#include <iostream>
#include <QSettings>
#include <QDebug>
//#include "httplistener.h"
//#include "webserver.h"
#include "database.h"

#include <SFML/Network.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "Starting server..." << std::endl;
    //Server s(argc, argv);
    Server s;
    s.Listen();


//        QSettings* listenerSettings =
//             new QSettings("../Browser.ini",QSettings::IniFormat,&a);
//        qDebug("config file loaded");

//        listenerSettings->beginGroup("listener");

//            // Start the HTTP server
//           new HttpListener(listenerSettings, new Database(&a), &a);

//    qDebug() << "Jessy";
    Database db;
    qDebug() << "db";
   // qDebug() << db.GetPlayerLevel("Jessy");

  //  db.RegisterUser("Martin", "Jack", "Jamjam", "jsmooth");


    //return s.exec();

    return a.exec();
}
