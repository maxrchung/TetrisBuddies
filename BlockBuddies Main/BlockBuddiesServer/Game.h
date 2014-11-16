#pragma once
#include "Messager.h"
class Game
{
public:
	Game();
	~Game();

	Player player1;
	Player player2;
	int GameID;
	bool gameOver;

	void runGame();
	Message createDelta();

	std::queue<Message> inputs;


};

