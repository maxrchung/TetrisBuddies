#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#pragma comment(lib, "sfml-network.lib")
#include <iostream>
#include <SFML/Network.hpp>

class clientManager
{
public:

	//call using clientManager::getInstance().functionname() to use.
	static clientManager& getInstance()
	{
		static clientManager server;
		return server;
	}

	bool initConnection(sf::IpAddress IP, int portNumber);

	void createUser();

	void run();

private:

	clientManager() {}                                  // Private constructor
	~clientManager() {}
	clientManager(const clientManager&);                 // Prevent copy-construction
	clientManager& operator=(const clientManager&);

	sf::TcpSocket socket;


};


#endif