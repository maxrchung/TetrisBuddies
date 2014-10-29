#include "ClientManager.h"

sf::TcpSocket socket;


clientManager::clientManager()
{

}

//Connects to the server socket
bool clientManager::initConnection(sf::IpAddress IP, int portNumber)
{
	sf::Socket::Status status = socket.connect(sf::IpAddress::getLocalAddress(), portNumber);
	if (status != sf::Socket::Done)
	{
		std::cout << "Can't Connect!";
		return false;
	}
	else return true;
}



void clientManager::createUser()
{
	sf::Packet playerInfo;
	socket.receive(playerInfo);

	//insert code to creat a new object here


}


