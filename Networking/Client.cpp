#include "ClientManager.h"





//Connects to the server socket
//Currently connects on the local machine only
//To Change this swap out IP with the first paramater of socket.connect()
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


//Needs to be updated to work with UserInfo.h
void clientManager::createUser()
{
	sf::Packet playerInfo;
	socket.receive(playerInfo);

	//insert code to creat a new object here

}


