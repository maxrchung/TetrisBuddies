#include "ClientManager.h"
#include "windows.h"
#include "UserInfo.h"
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
	sf::Uint8 i = 0;
	login << i << username << password;
	socket.send(login);
	//Gets the result from the server
	sf::Packet result;
	socket.receive(result);

	sf::Uint8 t;
	result >> t;

	if (t == 0)
		return false;
	else
	{
		
		result >> player.username >>  player.gamesPlayed >> player.gamesWon >> player.gamesLost >> player.highScore;
		player.winPercentage = (float)player.gamesWon / player.gamesPlayed;
		return true;
	}
}

bool ClientManager::registerUser(std::string username, std::string password)
{
	sf::Packet toAdd;
	//Sends 2 to the server indicating that it's a register package
	sf::Uint8 i  = 2;
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
		result >> player.username >> player.gamesPlayed >> player.gamesWon >> player.gamesLost >> player.highScore;
		player.winPercentage = (float)player.gamesWon / player.gamesPlayed;	
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
