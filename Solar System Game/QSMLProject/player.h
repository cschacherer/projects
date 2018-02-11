#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <SFML/Network.hpp>
#include <backpack.h>
#include <QMap>
#include <QObject>

class Player: public QObject
{
    Q_OBJECT
public:
    Player();

    sf::TcpSocket* socket;
    std::string username;
    std::string password;
    std::string firstName;
    std::string lastName;
    QMap<int, int> quizScores;
    int level;
    bool isAdmin;
    //add backpack
    //add journal



};

#endif // PLAYER_H
