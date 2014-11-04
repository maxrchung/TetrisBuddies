#include "serverManager.h"


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

bool serverManager::loginUser(std::string username, std::string password)
{
	if (DatabaseManager::getInstance().loginUser(username, password))
	{
		usersConnected.push_front(&DatabaseManager::getInstance().getUserInfo(username));
		return true;
	}
	else return false;

}

void serverManager::registerUser(std::string username, std::string password)
{
	DatabaseManager::getInstance().registerUser(username, password);
}


void serverManager::terminateConnection()
{
	server.disconnect();
}
