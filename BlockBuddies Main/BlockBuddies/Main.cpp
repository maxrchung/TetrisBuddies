#include "Game.hpp"

int main()
{
	Game game;

	while (game.isRunning)
		// Lets Game basically handle everything
		game.run();

	return 0;
}