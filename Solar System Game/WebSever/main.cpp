#include <QCoreApplication>
#include <QSettings>
#include "startup.h"
#include <httplistener.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

            QSettings* listenerSettings =
                 new QSettings("../Browser.ini",QSettings::IniFormat,&a);
            qDebug("config file loaded");

            listenerSettings->beginGroup("listener");

                // Start the HTTP server
               new HttpListener(listenerSettings, new StartUp(&a), &a);

    return a.exec();
}
