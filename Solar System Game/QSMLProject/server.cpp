//#include "server.h"

//#include <SFML/Audio.hpp>

//#include <SFML/Graphics.hpp>

//#include <SFML/Network.hpp>

//#include <iostream>

//#include <vector>
//Server::Server()
//{

//}

//void Server::Start(){

//    std::cout<<"in server";
//    sf::TcpListener listener;

//    if (listener.listen(53001) != sf::Socket::Done)

//    {

//        // error...

//    }

//    // Create a list to store the future clients

//    std::vector<sf::TcpSocket*> clients;

//    // Create a selector

//    sf::SocketSelector selector;

//    // Add the listener to the selector

//    selector.add(listener);

//    // Endless loop that waits for new connections

//    while (1)

//    {

//        // Make the selector wait for data on any socket

//        if (selector.wait())

//        {

//            // Test the listener

//            if (selector.isReady(listener))

//            {

//                // The listener is ready: there is a pending connection

//                sf::TcpSocket* client = new sf::TcpSocket;

//                std::cout << "Waiting to accept" << std::endl;

//                if (listener.accept(*client) == sf::Socket::Done)

//                {

//                    std::cout << "accepted" << std::endl;

//                    // Add the new client to the clients list

//                    clients.push_back(client);

//                    // Add the new client to the selector so that we will

//                    // be notified when he sends something

//                    selector.add(*client);

//                }

//                else

//                {

//                    // Error, we won't get a new connection, delete the socket

//                    delete client;

//                }

//            }

//            else

//            {

//                // The listener socket is not ready, test all other sockets (the clients)

//                for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)

//                {

//                    sf::TcpSocket& client = **it; // reference to the actual socket 1st * for it dereference second for pointer

//                    if (selector.isReady(client))

//                    {

//                        sf::Packet packet;

//                        if (client.receive(packet) == sf::Socket::Done)

//                        {

//                            // The client has sent some data, we can receive it

//                            std::string msg;

//                            packet >> msg;

//                            std::cout << "Msg received: " << msg << std::endl;

//                        }

//                    }

//                }

//            }

//        }

//    }


//}
