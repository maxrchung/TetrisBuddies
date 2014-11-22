#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <iostream>
#include <SFML/Network.hpp>

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

	void createUser();
	void messageWait();
	bool loginUser(std::string username, std::string password);
	bool registerUser(std::string username, std::string password);

	void run();

private:

	ClientManager() {}                                  // Private constructor
	~ClientManager() {}
	ClientManager(const ClientManager&);                 // Prevent copy-construction
	ClientManager& operator=(const ClientManager&);

	sf::TcpSocket socket;
};


#endif