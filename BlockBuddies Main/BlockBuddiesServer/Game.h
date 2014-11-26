#pragma once
#include "Message.h"
#include <queue>
#include "Player.h"
class Game
{
public:
	Game();
	~Game();

	Player* player1;
	Player* player2;
	int GameID;
	bool gameOver;

	void runGame();
//	Message createDelta();

	//std::queue<Message> inputs;


};

