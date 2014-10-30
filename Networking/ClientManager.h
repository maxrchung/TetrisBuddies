#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#pragma comment(lib, "sfml-network.lib")
#include <iostream>
#include <SFML/Network.hpp>

class clientManager
{
public:

	clientManager();

	bool initConnection(sf::IpAddress IP, int portNumber);

	void createUser();

	void run();

};


#endif