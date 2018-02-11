#include "mainwindow.h"
#include <QApplication>
#include <Magick++.h>

int main(int argc, char *argv[])
{
   // InitializeMagick(*argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();
}
