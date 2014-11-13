#pragma once

#include <string>
#include <vector>
#include <SFML/System/Thread.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <list>

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
	void makeNewPlayer();
	void parseMessage();



private:
	
	NetworkManager(const NetworkManager&);                 
	NetworkManager& operator=(const NetworkManager&);

	sf::SocketSelector connections;
	std::list<sf::TcpSocket*> clients;
	sf::TcpListener listener;
	bool running = true;

};