#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

int main()
{
	Game game;

	while (game.isRunning)
		// Lets Game handle everything
		game.run();

	return 0;
}