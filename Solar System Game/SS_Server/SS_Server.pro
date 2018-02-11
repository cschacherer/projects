QT += core
QT -= gui
QT += network
QT += sql

INCLUDEPATH += /usr/local/mysql-5.7.12-osx10.11-x86_64/include
LIBS += -L/usr/local/mysql-5.7.12-osx10.11-x86_64/lib -lmysqlclient -lm -lz

#CONFIG += c++11

TARGET = SS_Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    player.cpp \
 #   webserver.cpp \
    database.cpp \
    backpack.cpp \
    planet.cpp \
    souvenir.cpp \
#    WebServer/webserver.cpp

HEADERS += \
    server.h \
    player.h \
#    webserver.h \
    database.h \
    backpack.h \
    planet.h \
    souvenir.h \
#    WebServer/webserver.h



OTHER_FILES += etc/webapp1.ini


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
