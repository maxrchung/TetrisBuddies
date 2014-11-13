#include "NetworkManager.h"


void NetworkManager::run()
{
	//gamelogic will go here
	

}

void parseMessage()
{
	
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
						std::size_t received;
						char data[100];

						if (client.receive(data, 100, received) == sf::Socket::Done)
						{
							//Prints what you sent
							std::cout << data << "\n";
							
						}
					}
				}
			}
		}

	}

}