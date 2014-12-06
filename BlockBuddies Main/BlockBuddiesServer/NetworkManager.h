#pragma once

#include <string>
#include <vector>
#include <SFML/System/Thread.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "Player.h"
//The following code will create a thread for checking connections
//This will also work if you have any class and you replace everything with your input.

//NetworkManager postMaster;
//sf::Thread thread(&NetworkManager::checkForConnections, &postMaster);
//thread.launch();

class NetworkManager
{
	
public:
	
	NetworkManager() {}
	~NetworkManager() {}

	void run();
	void checkForConnections();
	bool checkLogin(std::string user, std::string pass);
	bool registerUser(std::string user, std::string pass);
	void makeNewPlayer();
	sf::Packet parseMessage(sf::Packet parse, sf::TcpSocket* socket);

	static std::list<Player> connectPlayers;


private:
	
	NetworkManager(const NetworkManager&);                 
	NetworkManager& operator=(const NetworkManager&);
	sf::SocketSelector connections;
	std::list<sf::TcpSocket*> clients;
	sf::TcpListener listener;
	bool running = true;

};