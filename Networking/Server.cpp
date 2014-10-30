#include "serverManager.h"

//These will need to be a private variable.
//Grant access to messageHandler so that messages can be sent that way
sf::TcpListener listener;
sf::TcpSocket server;


serverManager::serverManager()
{

}


//Listens for a connection
bool serverManager::startListen(int port)
{
	if (listener.listen(port) != sf::Socket::Done)
	{
		std::cout << "Error: Port listening";
		return false;
	}
	else
		return true;
	
}

//Actually connects server if listener has found one.
//Could be wrong on this
bool serverManager::connectClient()
{
	if (listener.accept(server) != sf::Socket::Done)
	{
		std::cout << "Error: Client connection";
		return false;
	}
	else return true;
	
}



void serverManager::sendPlayer(std::string name, int playerID, int rank)
{
	sf::Packet packet;
	packet << name << playerID << rank;
	server.send(packet);
}

void serverManager::terminateConnection()
{
	server.disconnect();
}


