#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#pragma comment(lib, "sfml-network.lib")
#include <iostream>
#include <SFML/Network.hpp>

class clientManager
{
public:

	static bool initConnection(sf::IpAddress IP, int portNumber);

	static std::string sendMessage(std::string toSend);

	static void recieveMessage();

	static void createUser();

}


#endif