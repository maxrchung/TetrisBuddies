#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <iostream>
#include <SFML/Network.hpp>
#include "UserInfo.h"
#include <queue>
#include <mutex>
#include <thread>
#include "ClientMessages.hpp"
#include "GameLogic.hpp"

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
    void joinQueue();
    void leaveQueue();
	void sendCursorUpdate(int x, int y);
	void leaveGameEarly();
    void acceptGame();
    void rejectGame();
	void requestNewRow();
	void insertPenaltyRow();
	void requestStartGame();
	void requestMultiplayerGame();
	void requestSwap(sf::Uint8 p1row, sf::Uint8 p1col, sf::Uint8 p2row, sf::Uint8 p2col);
	bool registerUser(std::string username, std::string password);
	bool isConnected = false; // Denotes whether or not you are connected
	bool isMultiplayer();

    bool wonGame = false; // Set to true/false after a game over

	GameLogic gameLogicHandler;

	ClientMessages messageMaker;
	UserInfo player;
	GameStateObject currentGSO;
	GameStateObject secondGSO;
	int packetCount = 0;
	int lastScore;
	bool multiplayer;
	bool isUpdated;
	bool isPlayerTwo;
	bool isOpponentUpdated;
	bool infoUpdate;
	void update();
    void closeConnection();
	bool gameOver;
    std::thread messageThread;
	sf::TcpSocket socket;

private:
    std::queue<sf::Packet> receivedPackets;
    std::mutex queueAccess;

    // Periodically sends an alive message
    sf::Clock sendAliveTimer;
    // Sends an alive message after a set time
    int sendAliveInterval = 4;

    // Checks for an alive message from server
    sf::Clock receiveAliveTimer;
    // Disconnects if no response after set time
    int receiveAliveLimit = 10;

	ClientManager() {}                                  // Private constructor
	~ClientManager() {}
	ClientManager(const ClientManager&);                 // Prevent copy-construction
	ClientManager& operator=(const ClientManager&);
};


#endif