#include "NetworkManager.h"
#include "DatabaseManager.h"
#include "Player.h"
#include "UserInfo.h"
#include <iostream>

NetworkManager* NetworkManager::instance;

NetworkManager* NetworkManager::getInstance()
{
	if(!instance)
		instance = new NetworkManager;
	return instance;
}

void NetworkManager::init()
{
    messageThread = std::thread(&NetworkManager::checkForConnections, this);
}

// Loops through player packet queues and responds to
// each packet
void NetworkManager::update()
{
    for(auto& player : connectPlayers)
    {
        if(!player.receivedPackets.empty())
        {
            sf::Packet packet = player.receivedPackets.front();

            queueAccess.lock();
            player.receivedPackets.pop();
            queueAccess.unlock();
            
            std::cout << "Popped off packet" << std::endl;
            std::cout << packet << std::endl;

            PacketDecode decode;
            int decodeIndex;
            packet >> decodeIndex;
            decode = PacketDecode(decodeIndex);

            switch(decode)
            {
                case PacketDecode::LOGIN:
                {
                    std::string user;
                    std::string pass;
                    packet >> user 
                           >> pass;
                    if (DatabaseManager::getInstance().loginUser(user, pass))
                    {
                        UserInfo userInfo = DatabaseManager::getInstance().getUserInfo(user);
                        player.playerInfo = userInfo;
                        sf::Packet answer;
                        answer << true // Indicates successful login
                               << userInfo;
                        player.playerSocket->send(answer);

                        std::cout << "Sent login packet" << std::endl;
                        std::cout << answer << std::endl;
                    }
                    else
                    {
                        sf::Packet answer;
                        answer << false;
                        player.playerSocket->send(answer);

                        std::cout << "Sent login packet" << std::endl;
                        std::cout << answer << std::endl;
                    }
                    break;
                }
                case PacketDecode::REGISTER:
                {
                    std::string user;
                    std::string pass;
                    packet >> user 
                           >> pass;

                    // Returns true if a user can be registered
                    // else returns false if the account already exists
                    if (DatabaseManager::getInstance().registerUser(user, pass))
                    {
                        int i = 1;
                        UserInfo userInfo = DatabaseManager::getInstance().getUserInfo(user);
                        sf::Packet answer;
                        answer << true
                               << userInfo;
                        player.playerSocket->send(answer);

                        std::cout << "Sent packet register" << std::endl;
                        std::cout << answer << std::endl;
                    }
                    else
                    {
                        sf::Packet answer;
                        answer << false;
                        player.playerSocket->send(answer);

                        std::cout << "Sent packet register" << std::endl;
                        std::cout << answer << std::endl;
                    }
                    break;
                }
            }
        }
    }
}

// Checks for conneciton requests and incoming messages
void NetworkManager::checkForConnections()
{
	listener.listen(5000);
	connections.add(listener);

	while (running)
	{
		// Make the selector wait for data on any socket
		if (connections.wait())
		{
			//If incoming connection add it else check others for packets
			if (connections.isReady(listener))
			{
				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
                    connectPlayers.push_back(Player(client));
					connections.add(*client);
				}
				else
				{
					delete client;
				}
			}

			else
			{
				// The listener socket is not ready, test all other sockets (the clients)
				for (auto& player : connectPlayers)
				{
					if (connections.isReady(*player.playerSocket))
					{
						sf::Packet packet;
                        if(player.playerSocket->receive(packet) == sf::Socket::Done)
						{
                            queueAccess.lock();
                            player.receivedPackets.push(packet);
                            queueAccess.unlock();
						}
					}
				}
			}
		}
	}
}