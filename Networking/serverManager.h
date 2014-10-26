#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#pragma comment(lib, "sfml-network.lib")
#include <iostream>
#include <SFML/Network.hpp>
class clientManager
{
	static bool startListen(int portNumber);

	static bool connectClient();

	static std::string sendMessage(char *temp);

	static void recieveMessagey();

	static void sendPlayer(std::string name, int playerID, int rank);

	static void terminateConnection();
}
#endif