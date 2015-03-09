#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

int main()
{
    // Initialize game
    Game::getInstance()->init();
    sf::Clock frameLimiter;

	while (Game::getInstance()->isRunning)
		// Lets Game handle everything
        if(frameLimiter.getElapsedTime().asMilliseconds() > 16)
        {
            Game::getInstance()->run();
        }

	return 0;
}