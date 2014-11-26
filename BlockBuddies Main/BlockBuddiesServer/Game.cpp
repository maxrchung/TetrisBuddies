#include "Game.h"
#include <time.h>
Game::Game()
{
	player1 = nullptr;
	player2 = nullptr;
	GameID = (int)time(NULL);
	gameOver = false;


}

Game::~Game()
{
}

void Game::runGame()
{

}