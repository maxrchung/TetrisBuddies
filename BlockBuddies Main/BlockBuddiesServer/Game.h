#pragma once
#include "Message.h"
#include <queue>
#include "Player.h"
#include "GameLogic.hpp"
#include <queue>
class Game
{
public:
	Game();
	~Game();

	Player* player1;
	Player* player2;
	int GameID;
	bool gameOver;
	GameLogic playerOneGame;
	GameLogic playerTwoGame;
	//These may not be needed. 
	std::queue<sf::Packet*> packetQueue1;
	std::queue<sf::Packet*> packetQueue2;

	void runGame();

private:

};

