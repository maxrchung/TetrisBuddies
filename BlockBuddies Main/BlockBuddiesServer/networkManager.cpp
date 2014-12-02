#include "NetworkManager.h"
#include "DatabaseManager.h"
#include "Player.h"
#include "UserInfo.h"

std::list<Player> NetworkManager::connectPlayers;
void NetworkManager::run()
{
	//gamelogic will go here
}
bool checkLogin(std::string user, std::string pass)
{
	return DatabaseManager::getInstance().loginUser(user, pass);
}

bool registerUser(std::string user, std::string pass)
{
	return DatabaseManager::getInstance().registerUser(user, pass);
}

bool parseMessage(sf::Packet parse)
{
	int i;
	std::string user;
	std::string pass;
	parse >> i >> user >> pass;
	//Checks to see if the int is 0 || 1
	//This can be expanded to multiple message types and then call the correct function later on. 
	//A suggestion but for now this works for our simple set up.
	switch (i) {
	case 0:
		return checkLogin(user, pass);
	case 1:
		return registerUser(user, pass);
	default:
		return false;
	}
}

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
					//Adds to the list of connections
					clients.push_back(client);
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
				
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
				{
					
					sf::TcpSocket& client = **it;
					if (connections.isReady(client))
					{
						//This will have to be replaced with some way of parsing the message
						sf::Packet packet;
						
						if (client.receive(packet) == sf::Socket::Done)
						{
							int i;
							std::string user;
							std::string pass;
							packet >> i >> user >> pass;
							//Checks to see if the int is 0 || 1
							//This can be expanded to multiple message types and then call the correct function later on. 
							//A suggestion but for now this works for our simple set up.
							
							if (i == 0)
							{
								if (DatabaseManager::getInstance().loginUser(user, pass))
								{
									int i = 1;
									Player newPlayer = Player(*it, DatabaseManager::getInstance().getUserInfo(user));
									sf::Packet answer;
									UserInfo sendMe = DatabaseManager::getInstance().getUserInfo(user);
									answer << i << 
									newPlayer.playerInfo.username << newPlayer.playerInfo.gamesPlayed <<
									newPlayer.playerInfo.gamesWon << newPlayer.playerInfo.gamesLost << newPlayer.playerInfo.highScore;
									client.send(answer);
									connectPlayers.push_back(newPlayer);
								}
								else
								{
									int i = 0;
									sf::Packet answer;
									answer << i;
									client.send(answer);
								}
							}
							else if (i == 1)
							{

								if (DatabaseManager::getInstance().registerUser(user, pass))
								{
									int i = 1;
									Player newPlayer = Player(*it, DatabaseManager::getInstance().getUserInfo(user));
									sf::Packet answer;
									UserInfo sendMe = DatabaseManager::getInstance().getUserInfo(user);
									answer << i <<
										newPlayer.playerInfo.username << newPlayer.playerInfo.gamesPlayed <<
										newPlayer.playerInfo.gamesWon << newPlayer.playerInfo.gamesLost << newPlayer.playerInfo.highScore;
									client.send(answer);
									connectPlayers.push_back(newPlayer);
								}
								else
								{
									int i = 0;
									sf::Packet answer;
									answer << i;
									client.send(answer);
								}
							}
							
						}
					}
				}
			}
		}

	}

}