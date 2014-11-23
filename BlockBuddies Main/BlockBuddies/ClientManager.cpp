#include "ClientManager.h"

//Connects to the server socket
//Currently connects on the local machine only

bool ClientManager::initConnection(sf::IpAddress IP, int portNumber)
{
	//Tries to connect
	sf::Socket::Status status = socket.connect(IP, portNumber);
	//Checks if it was able to connect
	if (status != sf::Socket::Done)
	{
		isConnected = false;
		return false;
	}
	else 
	{
		isConnected = true;
		return true;		
	}
}

bool ClientManager::loginUser(std::string username , std::string password)
{
	//Sends the log in
	sf::Packet login;
	int i = 0;
	login << i << username << password;
	socket.send(login);
	//Gets the result from the server
	sf::Packet result;
	socket.receive(result);

	int t;
	result >> t;

	if (t == 0)
		return true;
	else
		return false;
	
}

bool ClientManager::registerUser(std::string username, std::string password)
{
	sf::Packet toAdd;
	int i = 1;
	toAdd << i << username << password;
	socket.send(toAdd);

	//Gets the result from the server
	sf::Packet result;
	socket.receive(result);
	
	int t;
	result >> t;

	if (t == 0)
		return true;
	else
		return false;
}

//Needs to be updated to work with UserInfo.h
void ClientManager::createUser()
{
	sf::Packet playerInfo;
	socket.receive(playerInfo);

	//insert code to creat a new object here

}

void ClientManager::messageWait()
{	
	while (true)
	{
		sf::Packet packet;
		if (socket.receive(packet) != sf::Socket::Done)
		{
			std::string recieved;
			if(packet >> recieved)

			std::cout << "Received: " << recieved << std::endl;
		}
	}
}
