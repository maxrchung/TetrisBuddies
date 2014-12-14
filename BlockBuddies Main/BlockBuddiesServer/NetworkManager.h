#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "Player.h"
#include <mutex>
#include <thread>
#include "GameLogic.hpp"

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
	void newHighScore(int newScore, std::string username);
	void addWin(std::string username, bool win);
    std::list<Player> connectPlayers;

	GameLogic gameHandler;
	sf::Clock clock;
	sf::Time tick;
	bool running = true;

private:
    std::mutex queueAccess;
    sf::SocketSelector connections;
	sf::TcpListener listener;
    std::thread messageThread;

    // Sends a periodic alive message to all clients
    // based on set interval
    sf::Clock sendAliveTimer;
    int sendAliveInterval = 4;

    static NetworkManager* instance;
	
	NetworkManager(const NetworkManager&);                 
	NetworkManager& operator=(const NetworkManager&);
	NetworkManager() {}
};