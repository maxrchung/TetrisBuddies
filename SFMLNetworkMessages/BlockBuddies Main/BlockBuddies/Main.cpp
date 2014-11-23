#include "Game.hpp"
#include "DatabaseManager.h"
#include "ClientManager.h"
int main()
{
	clientManager::getInstance();
	sf::Thread thread(&clientManager::messageWait, &clientManager::getInstance());
	thread.launch();
	
	Game game;
	while (game.isRunning)
		// Lets Game handle everything
		game.run();
	
	return 0;
}