#include "NetworkManager.h"
#include "DatabaseManager.h"
#include "Player.h"
#include "UserInfo.h"

std::list<Player> NetworkManager::connectPlayers;

void NetworkManager::run()
{
	//gamelogic will go here
}
bool NetworkManager::checkLogin(std::string user, std::string pass)
{
	return DatabaseManager::getInstance().loginUser(user, pass);
}

bool NetworkManager::registerUser(std::string user, std::string pass)
{
	return DatabaseManager::getInstance().registerUser(user, pass);
}



sf::Packet NetworkManager::parseMessage(sf::Packet parse, sf::TcpSocket* socket)
{
	sf::Uint8 i;
	parse >> i;
	std::string user;
	std::string pass;
	

	sf::Packet answer;
	switch (i) {
	//LoginUser
	case 0:

		parse >> user >> pass;
		if (checkLogin(user, pass))
		{
			sf::Uint8 i = 1;
			Player newPlayer = Player(socket, DatabaseManager::getInstance().getUserInfo(user));
			answer << i <<
				newPlayer.playerInfo.username << newPlayer.playerInfo.gamesPlayed <<
				newPlayer.playerInfo.gamesWon << newPlayer.playerInfo.gamesLost << newPlayer.playerInfo.highScore;
			connectPlayers.push_back(newPlayer);
			return answer;
		}
		else
		{
			
			return answer << 0;
		}
		
	//Register User
	case 2:

		parse >> user >> pass;
		if (registerUser(user, pass))
		{
			sf::Uint8 i = 1;
			Player newPlayer = Player(socket, DatabaseManager::getInstance().getUserInfo(user));
			answer << i <<
				newPlayer.playerInfo.username << newPlayer.playerInfo.gamesPlayed <<
				newPlayer.playerInfo.gamesWon << newPlayer.playerInfo.gamesLost << newPlayer.playerInfo.highScore;
			connectPlayers.push_back(newPlayer);
			return answer;
		}
		else
		{

			return answer << 0;
		}
	default:
		return answer << 0;
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
						//Add a queue to store packets then send them out. 
						sf::Packet packet;

						if (client.receive(packet) == sf::Socket::Done)
						{
							client.send(parseMessage(packet, *it));

						}
					}
				}
			}
		}

	}

}