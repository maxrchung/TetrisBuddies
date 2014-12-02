#include "ClientManager.h"
#include "windows.h"

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

char* ClientManager::getName()
{

	return "Coming Soon";
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
		return false;
	else
	{
		int test;
		
		result >> player.username >>  player.gamesPlayed >> player.gamesWon >> player.gamesLost >> player.highScore;
		test = 0;
		return true;
	}
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
		return false;
	else
	{
		int test;

		result >> player.username >> player.gamesPlayed >> player.gamesWon >> player.gamesLost >> player.highScore;
		test = 0;
		return true;
	}
}


void ClientManager::messageWait()
{	
	while (true)
	{
		Sleep(550);

		sf::Packet packet;
		//socket.setBlocking(false);
		if (socket.receive(packet) != sf::Socket::Done)
		{
			
		}
		else
		{
			std::string recieved;
			packet >> recieved;
			std::cout << "Received: " << recieved << std::endl;
		}
		//socket.setBlocking(true);

	}
}
