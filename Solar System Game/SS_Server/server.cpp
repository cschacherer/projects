#include "server.h"
#include "player.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <QList>
#include <QString>

//Server::Server(QObject *parent) : QObject(parent)
Server::Server()//(int argc, char *argv[]): QtService<QCoreApplication>(argc, argv, "Teacher info")
{
//    setServiceDescription("Testing");
//    setStartupType(QtServiceController::AutoStartup);

    qDebug() << "Server is listening";
    Listen();

    isAdmin = false;
}

Server::~Server()
{}
void Server::start()
{
//    QCoreApplication* app = application();

//    // HTTP server
//        QSettings* listenerSettings =
//             new QSettings("../Browser.ini",QSettings::IniFormat,app);
//        qDebug("config file loaded");

//        listenerSettings->beginGroup("listener");

//                // Start the HTTP server
//              listener = new HttpListener(listenerSettings, new Database(app), app);

}

void Server::stop()
{
//    qWarning("Webserver has been stopped");
}

void Server::Listen()
{
    sf::TcpListener listener;
    if (listener.listen(serverconnect) != sf::Socket::Done)
    {
        // error...
    }

    // Create a selector
    sf::SocketSelector selector;
    // Add the listener to the selector
    selector.add(listener);

    // Endless loop that waits for new connections
    while (1)
    {
        // Make the selector wait for data on any socket
        if (selector.wait())
        {
            // Test the listener
            if (selector.isReady(listener))
            {
                // The listener is ready: there is a pending connection
                sf::TcpSocket* client = new sf::TcpSocket;
                //std::cout << "Waiting to accept" << std::endl;

                if (listener.accept(*client) == sf::Socket::Done)
                {
                    std::cout << "Accepted" << std::endl;

                    // Add the new client to the clients list
                    clients.push_back(client);

                    // Add the new client to the selector so that we will
                    // be notified when he sends something
                    selector.add(*client);
                }
                else
                {
                    // Error, we won't get a new connection, delete the socket
                    delete client;
                }
            }
            else
            {
                // The listener socket is not ready, test all other sockets (the clients)
                for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it; // reference to the actual socket 1st * for it dereference second for pointer
                    //selectedClient = client;
                    if (selector.isReady(client))
                    {
                        qDebug() << "Client is connected";
                        sf::Packet packet;
                        if (client.receive(packet) == sf::Socket::Done)
                        {
                            char *data = new char [packet.getDataSize()];
                            packet >> data;
                            std::string message (data);

                            std::stringstream ss(message);
                            QList <std::string> messageList;
                            while (ss.good())
                            {
                                std::string msg;
                                ss >> msg;
                                messageList.push_back(msg);
                            }

                            if (messageList[0] == "Login:")
                            {            
                                LoginPlayer(client, messageList);
                            }
                            if (messageList[0] == "Register:")
                            {
                                AddNewPlayer(client, messageList);
                            }
                            if (messageList[0] == "LevelChanged:")
                            {
                                ChangeLevel(client, messageList);
                            }
                            if(messageList[0] == "QuizScore:")
                            {
                                SaveQuizScore(client, messageList);
                            }
                            else
                            {
                                //error message
                            }

                        }
                        //gracefully disconnects
                        if (client.receive(packet) == sf::Socket::Disconnected)
                        {
                            selector.remove(client);
                            int findClient = -1;
                            for (int i = 0; i < players.size(); i++)
                            {
                                if (players[i].socket = &client)
                                {
                                    findClient = i;
                                }
                            }
                            if (findClient != 0)
                            {
                                delete players[findClient].socket;
                                players.erase(players.begin() + findClient);
                            }
                            client.disconnect();
                            delete(&client);
                            clients.erase(it);
                            it--;

                        }
                    }
                }
            }
        }
    }
}

void Server::LoginPlayer(sf::TcpSocket & clientSocket, QList<std::string> dataList)
{
    qDebug() << "Login Function ";
    std::string user = dataList[1];
    std::string pass = dataList[2];

    if(user == "admin" && pass == "password")
    {
        isAdmin = true;
        start();
    }
    bool check = CheckDatabase(user, pass);
    if (check == true)
    {
        //SendExistingPlayerInfo
        //Get player information from database and make player, then add to player vector
        QString dbName = QString::fromStdString(user);
        QString playerLevel =  database.GetPlayerLevel(dbName);
        Player player;
        player.username = user;
        player.level = atoi(playerLevel.toStdString().c_str());
        player.socket = &clientSocket;
        players.push_back(player);

        std::string playerMessage = "LoginPlayer: " + player.username + " " + QString::number(player.level).toStdString();
        qDebug() << "Player message: " << QString::fromStdString(playerMessage);
        const char* buffer = playerMessage.c_str();
        sf::Packet packet;
        packet << buffer;
        clientSocket.send(packet);
    }
    else
    {
        sf::Packet packet;
        std::string playerMessage = "IncorrectLogin:";
        const char* buffer = playerMessage.c_str();
        packet << buffer;
        clientSocket.send(packet);
    }
}

bool Server::CheckDatabase(std::string name, std::string pass)
{
    QString dbName = QString::fromStdString(name);
    QString dbPass = QString::fromStdString(pass);
    qDebug() << dbName << " " << dbPass;

    database.ConnectTODb(dbName, dbPass);
    if (database.connected == true)
    {
        return true;
    }
    return false;
}


void Server::AddNewPlayer(sf::TcpSocket& clientSocket, QList<std::string> dataList)
{
    //creates a new player to add ot the list
    std::string user = dataList[1];
    std::string pass = dataList[2];
    std::string first = dataList[3];
    std::string last = dataList[4];

    QString dbName = QString::fromStdString(user);
    QString dbPass = QString::fromStdString(pass);
    QString dbFirst = QString::fromStdString(first);
    QString dbLast = QString::fromStdString(last);

    sf::Packet packet;

    database.RegisterUser(dbFirst, dbLast, dbName, dbPass);
    if (database.isSaved == true)
    {
        Player player;
        player.socket = &clientSocket;
        player.username = user;
        player.password = pass;
        player.firstName = first;
        player.lastName = last;
        player.level = 1;

        //sets up a player on Player vector
        players.push_back(player);

        //Sending player info back to client;
        sf::Packet packet;
        std::string playerMessage = "SuccessfulRegister: " + player.username;
        const char* buffer = playerMessage.c_str();
        packet << buffer;
        player.socket->send(packet);
        qDebug() << "registered player";
    }
    else
    {
        //Sending player info back to client;
        sf::Packet packet;
        std::string playerMessage = "UnsuccessfulRegister:";
        const char* buffer = playerMessage.c_str();
        packet << buffer;
        clientSocket.send(packet);
        qDebug() << "did not register";
    }

}

void Server::ChangeLevel(sf::TcpSocket & clientSocket, QList<std::string> dataList)
{
    std::string level = dataList[1];
    int intLevel = atoi(level.c_str());
    QString dblevel = QString::fromStdString(level);

    //Changel level for database
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i].socket == &clientSocket)
        {
            players[i].level = intLevel;

            QString dbuser = QString::fromStdString(players[i].username);
            database.UpdateLevels(dbuser, players[i].level);
            if (database.isSaved == false)
            {
                //throw error
            }

        }
    }
}

void Server::SaveQuizScore(sf::TcpSocket &clientSocket, QList<std::string> dataList)
{
    std::string score = dataList[1];
    int intScore = atoi(score.c_str());
    QString dbscore = QString::fromStdString(score);

    //SendQuizScores
    for(int i = 0; i < players.size(); i++)
    {
        if(players[i].socket == &clientSocket)
        {
            players[i].quizScores[players[i].level] = intScore;

//            QString dbuser = QString::fromStdString(players[i].username);

//            database.UpdateScore(dbuser, QString::toplayers[i].level, );
//            if (database.isSaved == false)
//            {
//                //throw error
//            }
        }
    }
}


