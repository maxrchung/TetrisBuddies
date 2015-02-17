#pragma once
#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "Player.h"
#include <mutex>
#include <thread>
#include <vector>
#include "GameLogic.hpp"
#include "Game.h"
#include "MatchMakingHandler.h"
#include "SinglePlayerHandler.h"
#include <algorithm>
#include "DatabaseManager.h"

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
	bool isLoggedIn(std::string user);
	void newHighScore(int newScore, std::string username);
	void addWin(std::string username, bool win);
    std::list<Player*> connectPlayers;
	std::list<Player*> toRemove;
	std::list<std::string> userNamesLoggedIn;


	GameLogic gameHandler;
	sf::Clock clock;
	sf::Time tick;
	bool running = true;
	MatchMakingHandler multiplayer;
    SinglePlayerHandler singlePlayer;

private:
    std::mutex queueAccess;
	std::mutex databaseAccess;
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