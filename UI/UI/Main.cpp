#include "Game.hpp"

int main()
{
	Game game;

	while (game.isRunning)
	{
		game.run();
	}

	return 0;
}