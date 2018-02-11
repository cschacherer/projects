#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SFML/Network.hpp>
#include <backpack.h>
#include <QMap>

class Player
{
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
