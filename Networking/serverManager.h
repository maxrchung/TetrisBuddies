#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#pragma comment(lib, "sfml-network.lib")
#include <iostream>
#include <list>
#include <SFML/Network.hpp>
#include "DatabaseManager.h"
#include "UserInfo.h"

class serverManager
{
public:

	serverManager();

	bool startListen(int portNumber);

	bool connectClient();

	void sendPlayer(std::string name, int playerID, int rank);

	void terminateConnection();

	bool loginUser(std::string username, std::string password);

	void registerUser(std::string username, std::string password);



private:
	sf::TcpListener listener;
	sf::TcpSocket server;

	std::list<sf::TcpSocket*> clients;
	sf::SocketSelector selector;

	std::list<UserInfo*> usersConnected;


};

#endif