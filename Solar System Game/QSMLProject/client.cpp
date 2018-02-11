#include "client.h"
#include <iostream>
#include <cstring>
#include "loginform.h"
#include <QDebug>
#include <sstream>
#include <QTimer>
#include <string>

Client::Client()
{
    correctLogin = false;
    correctRegister = false;
}

Client::~Client()
{

}

void Client::ClientConnect(QString typeOfLogin)
{
    std::cout << "Starting Client" << std::endl;

    status = clientSocket.connect("localhost", 72000);
    sf::Packet outPacket;

    std::string data;
    const char *buffer;

    if (typeOfLogin == "Login")
    {
        data = "Login: " + username.toStdString() + " " + password.toStdString() + "\n";
        buffer = data.c_str();
        outPacket << buffer;
    }
    else if (typeOfLogin == "Register")
    {
        data = "Register: " + username.toStdString() + " " + password.toStdString() + " " + firstName.toStdString() + " " + lastName.toStdString() + "\n";
        buffer = data.c_str();
        outPacket << buffer;
    }
    clientSocket.send(outPacket);
    //check if it has sent then delete buffer

    //recieves login information
    ReceiveData();
}

void Client::GetUsername(QString name, QString pass)
{
    username = name;
    password = pass;
    ClientConnect("Login");
}

void Client::RegisterUser(QString name, QString pass, QString first, QString last)
{
    username = name;
    password = pass;
    firstName = first;
    lastName = last;

    ClientConnect("Register");
}

void Client::SaveLevel(int newLevel)
{
    //std::string savedlevel = std::to_string(player.level);

    std::string data = "ChangeLevel: " + QString::number(player.level).toStdString();

    char *buffer = new char [data.length() + 1];
    std::strcpy (buffer, data.c_str());
    sf::Packet packet;
    packet << buffer;
    clientSocket.send(packet);
    //if send is successful,
    //delete buffer;
}

void Client::SaveQuizScore()
{
//    //std::string savedlevel = std::to_string(player.level);
//    int score = player.quizScores[player.level];
//    std::string data = "QuizScore: " + std::to_string(score);

//    char *buffer = new char [data.length() + 1];
//    std::strcpy (buffer, data.c_str());
//    sf::Packet packet;
//    packet << buffer;
//    clientSocket.send(packet);
//    //if send is successful,
//    //delete buffer;
}

void Client::ReceiveData()
{
    sf::Packet packet;
    clientSocket.receive(packet);

    char *charData = new char [packet.getDataSize()];
    if (packet >> charData)
    {
        std::string message (charData);
        std::stringstream ss(message);
        QList <std::string> messageList;
        while (ss.good())
        {
            std::string msg;
            ss >> msg;
            messageList.push_back(msg);
        }

        //prints message just to check if it is right.
        for(int i = 0; i < messageList.length(); i++)
        {
            std::cout << messageList[i] << std::endl;
        }

        if (messageList[0] == "LoginPlayer:")
        {
            player.username = messageList[1];
            player.level = atoi(messageList[2].c_str());
            //emit CorrectLoginSignal
            correctLogin = true;
        }
        if (messageList[0] == "SuccessfulRegister:")
        {
            player.username = messageList[1];
            player.level = 1;
            //emit CorrectRegisterSignal
            correctRegister = true;
        }
        if (messageList[0] == "IncorrectLogin:")
        {
            //emit IncorrectLoginSignal();
            correctLogin = false;
        }

        if (messageList[0] == "UnsuccessfulRegister:")
        {
            //emit UnsuccessfulRegisterSignal();
            correctRegister = false;
        }
    }

}

