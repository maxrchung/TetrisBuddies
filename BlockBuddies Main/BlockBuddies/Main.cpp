#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

int main()
{
    // Initialize game
    Game::getInstance()->init();

	while (Game::getInstance()->isRunning)
		// Lets Game handle everything
        if(Game::getInstance()->frameLimiter.getElapsedTime().asMilliseconds() > 16)
        {
            Game::getInstance()->frameLimiter.restart();
            Game::getInstance()->run();
        }

	return 0;
}