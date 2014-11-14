#include "Game.hpp"
#include "DatabaseManager.h"
int main()
{
	
	Game game;
	while (game.isRunning)
		// Lets Game handle everything
		game.run();
	
	return 0;
}