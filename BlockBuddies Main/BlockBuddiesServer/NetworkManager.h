#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "Player.h"
#include <mutex>
#include <thread>

enum PacketDecode
{
    LOGIN,
    REGISTER
};

//The following code will create a thread for checking connections
//This will also work if you have any class and you replace everything with your input.

//NetworkManager postMaster;
//sf::Thread thread(&NetworkManager::checkForConnections, &postMaster);
//thread.launch();

class NetworkManager
{
public:
    static NetworkManager* getInstance();
    void init();
    void update();
	void checkForConnections();
	void makeNewPlayer();
    
    std::list<Player> connectPlayers;

	bool running = true;

private:
    std::mutex queueAccess;
    sf::SocketSelector connections;
	sf::TcpListener listener;
    std::thread messageThread;

    static NetworkManager* instance;
	
	NetworkManager(const NetworkManager&);                 
	NetworkManager& operator=(const NetworkManager&);
	NetworkManager() {}
};