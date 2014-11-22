#include "Game.hpp"
#include "ClientManager.h"
int main()
{
	/*
	ClientManager::getInstance();
	sf::Thread thread(&ClientManager::messageWait, &ClientManager::getInstance());
	thread.launch();
	*/
	Game game;
	while (game.isRunning)
		// Lets Game handle everything
		game.run();
	
	return 0;
}