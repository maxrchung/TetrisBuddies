#include "Game.h"
#include <time.h>
Game::Game(int numberOfPlayers)
	:playerCount(numberOfPlayers)
{
	if (playerCount == 1)
	player1 = nullptr;
	else
	{
		player2 = nullptr;
		player1 = nullptr;
	}
	gameOver = false;

	//Where am I assingend? Look that up
}

Game::~Game()
{
}

void Game::runGame()
{
	if (playerCount == 1)
		playerOneGame.GameTick();
	else
	{
		playerOneGame.GameTick();
		playerTwoGame.GameTick();
	}
}