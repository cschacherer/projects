#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <QString>
#include <QObject>
#include "player.h"

class Client : public QObject
{
    Q_OBJECT

public:
    Client();
    ~Client();
    void ClientConnect(QString user);
    //void SendData(std::string data);

    void ProcessData(sf::Packet);
    void GetUsername(QString name, QString pass);
    void RegisterUser(QString name, QString pass, QString first, QString last);
    void SaveLevel(int newLevel);
    void SaveQuizScore();

    bool correctLogin;
    bool correctRegister;

public slots:
    void ReceiveData();

private:
    sf::TcpSocket clientSocket;
    sf::Socket::Status status;
    QString username;
    QString password;
    QString firstName;
    QString lastName;
    Player player;
};

#endif // CLIENT_H

