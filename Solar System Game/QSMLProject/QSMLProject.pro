##-------------------------------------------------
##
## Project created by QtCreator 2016-04-19T16:19:31
##
##-------------------------------------------------

#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/sfml/2.3_1/include
#DEPENDPATH += $$PWD/../../../../usr/local/Cellar/sfml/2.3_1/include

#macx: LIBS += -L/usr/local/lib/ \
#    -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network
#TARGET = QSMLProject
#TEMPLATE = app

##CONFIG+=c++11

#SOURCES += main.cpp\
#        mainwindow.cpp \
#    qsfmlcanvas.cpp \
#    mycanvas.cpp \
#    planets.cpp \
#    souvenir.cpp \
#    player.cpp \
#    backpack.cpp \
#    quizzes.cpp

#HEADERS  += mainwindow.h \
#    qsfmlcanvas.h \
#    mycanvas.h \
#    client.h \
#    planets.h \
#    souvenir.h \
#    player.h \
#    backpack.h \
#    quizzes.h

#FORMS    += mainwindow.ui

##macx: LIBS += -L/usr/local/lib/ \
##    -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network

#INCLUDEPATH += /usr/local/Cellar/sfml/2.3_1/include
#DEPENDPATH += /usr/local/Cellar/sfml/2.3_1/include


#DISTFILES += \
#    images/rightArrow.png

#RESOURCES += \
#    planets.qrc

##macx: LIBS += -L$$PWD/../../../../usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-network.2.3.0

##INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/sfml/2.3_1/include
##DEPENDPATH += $$PWD/../../../../usr/local/Cellar/sfml/2.3_1/include

#macx: LIBS += -L$$PWD/Build/Box2D/ -lBox2D

#INCLUDEPATH += $$PWD/Build/Box2D
#DEPENDPATH += $$PWD/Build/Box2D




QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/sfml/2.3_1/include
#DEPENDPATH += $$PWD/../../../../usr/local/Cellar/sfml/2.3_1/include

#macx: LIBS += -L/usr/local/lib/ \
#   -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-network
TARGET = QSMLProject
TEMPLATE = app

#CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    planets.cpp \
    souvenir.cpp \
    player.cpp \
    quizzes.cpp \
    moon.cpp \
    earth.cpp \
    mercury.cpp \
    venus.cpp \
    uranus.cpp \
    mars.cpp \
    saturn.cpp \
    backback.cpp \
    journal.cpp \
    neptune.cpp \
    jupiter.cpp \
    client.cpp \
    loginform.cpp \
    registerform.cpp
    uranus.cpp \

HEADERS  += mainwindow.h \
#    client.h \
    planets.h \
    souvenir.h \
    player.h \
    quizzes.h \
    moon.h \
    earth.h \
    mercury.h \
    venus.h \
    uranus.h \
    mars.h \
    saturn.h \
    backback.h \
    journal.h \
    neptune.h \
    jupiter.h \
    client.h \
    loginform.h \
    registerform.h

FORMS    += mainwindow.ui \
    journal.ui \
    backpack.ui \
    loginform.ui \
    registerform.ui
    #loginform.ui \
    #registerform.ui

include(Box2D/Box2D.pro)

#macx: LIBS += -L/usr/local/lib/ \
#    -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network

#INCLUDEPATH += /usr/local/Cellar/sfml/2.3_1/include
#DEPENDPATH += /usr/local/Cellar/sfml/2.3_1/include


DISTFILES += \
    images/rightArrow.png

RESOURCES += \
    planets.qrc


macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-audio.2.3.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include


macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-graphics.2.3.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-network.2.3.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-system.2.3.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include

macx: LIBS += -L$$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/lib/ -lsfml-window.2.3.0

INCLUDEPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include
DEPENDPATH += $$PWD/../../../../../../usr/local/Cellar/sfml/2.3_1/include

