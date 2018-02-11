QT += core sql network
QT -= gui

CONFIG += c++11

TARGET = WebSever
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    startup.cpp

include(QtWebApp/QtWebApp.pro)

mac {
    INCLUDEPATH += /usr/local/mysql-5.7.12-osx10.11-x86_64/include
    LIBS += -L/usr/local/mysql-5.7.12-osx10.11-x86_64/lib -lmysqlclient -lm -lz
}

unix:!mac {

}

HEADERS += \
    startup.h
