#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

int main()
{
    // Initialize game
    Game::getInstance()->init();

	while (Game::getInstance()->isRunning)
		// Lets Game handle everything
		Game::getInstance()->run();

	return 0;
}