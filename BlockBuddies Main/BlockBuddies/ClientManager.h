#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

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
	void messageWait();
	bool loginUser(std::string username, std::string password);
	bool registerUser(std::string username, std::string password);

	void run();

private:

	clientManager() {}                                  // Private constructor
	~clientManager() {}
	clientManager(const clientManager&);                 // Prevent copy-construction
	clientManager& operator=(const clientManager&);

	sf::TcpSocket socket;
};


#endif