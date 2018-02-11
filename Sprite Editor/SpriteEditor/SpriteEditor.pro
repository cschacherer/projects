#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T15:31:54
#
#-------------------------------------------------

INCLUDEPATH += /usr/include/ImageMagick

#LIBS += /usr/lib64/libMagick++.so.5.0.0
#LIBS += /usr/lib64/libMagick++.so.5
#LIBS += /usr/lib64/libMagick++.so
LIBS += /usr/lib64/libMagick++.so /usr/lib64/libMagickCore.so

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteEditor #-I $(INCLUDEPATH) -L $(LIBS) $(Magick++-config --cppflags --cxxflags --ldflags --libs)
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    frame.cpp \
    mygraphicsview.cpp

    mygraphicsview.cpp
    mygraphicsview.cpp



HEADERS  += \
    frame.h \
    mainwindow.h \
    mygraphicsview.h

    mygraphicsview.h



FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
