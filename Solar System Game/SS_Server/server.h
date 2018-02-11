#ifndef SERVER_H
#define SERVER_H

#include <QCoreApplication>
#include <QSettings>
//#include "qtservice.h"
//#include "httplistener.h"
#include <QObject>
#include <QDebug>
#include <vector>
#include <iostream>
#include "player.h"
#include "planet.h"
#include "database.h"


class Server : public QObject //, public QtService<QCoreApplication>
{
    Q_OBJECT

public:
    //explicit Server(QObject *parent = 0);
    //Server(int argc, char *argv[]);
    Server();
    ~Server();
    void Listen();

    void LoginPlayer(sf::TcpSocket&, QList<std::string>);
    void AddNewPlayer(sf::TcpSocket&, QList<std::string>);
    void ChangeLevel(sf::TcpSocket&, QList<std::string>);
    void SaveQuizScore(sf::TcpSocket&, QList<std::string>);
    bool CheckDatabase(std::string, std::string);
    Database database;

protected:
    void start();
    void stop();

private:
    // Create a list to store the future clients
    std::vector<sf::TcpSocket*> clients;

    //create a list of all the players
    std::vector<Player> players;

    std::vector<Planet> planets;

    //HttpListener* listener;

    //sf::TcpSocket& selectedSocket;
    unsigned int serverconnect = 72000;

    bool isAdmin;
};

#endif // SERVER_H
