#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#pragma comment(lib, "sfml-network.lib")

#include <iostream>

#include <SFML/Network.hpp>

class serverManager
{
public:

	serverManager();

	bool startListen(int portNumber);

	bool connectClient();

	void sendPlayer(std::string name, int playerID, int rank);

	void terminateConnection();


};

#endif