#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <iostream>
#include <SFML/Network.hpp>
#include "UserInfo.h"
#include <queue>
#include <mutex>
#include <thread>
#include "ClientMessages.hpp"


class ClientManager
{
public:
	//call using ClientManager::getInstance().functionname() to use.
	static ClientManager& getInstance()
	{
		static ClientManager server;
		return server;
	}

	bool initConnection(sf::IpAddress IP, int portNumber);

	void messageWait();
	bool loginUser(std::string username, std::string password);
	void requestStartGame();
	void requestSwap(sf::Uint8 p1row, sf::Uint8 p1col, sf::Uint8 p2row, sf::Uint8 p2col);
	bool registerUser(std::string username, std::string password);
	bool isConnected = false; // Denotes whether or not you are connected

	ClientMessages messageMaker;
	UserInfo player;
	void update();

private:
    std::queue<sf::Packet> receivedPackets;
    std::mutex queueAccess;
    std::thread messageThread;

	ClientManager() {}                                  // Private constructor
	~ClientManager() {}
	ClientManager(const ClientManager&);                 // Prevent copy-construction
	ClientManager& operator=(const ClientManager&);

	sf::TcpSocket socket;
};


#endif