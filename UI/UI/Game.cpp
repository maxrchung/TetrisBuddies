#include "Game.hpp"
#include "GraphicsManager.hpp"

Game::Game()
{
	GraphicsManager::window.create(sf::VideoMode::getFullscreenModes()[0], "Block Buddies", sf::Style::Fullscreen);
}

Game::~Game()
{

}

void Game::run()
{
	if (fpsClock.getElapsedTime().asMilliseconds() > 1000.0f / 60.0f) // Limits to 60FPS
	{
		update();
		draw();
		fpsClock.restart();
	}
}

void Game::update()
{
	sf::Event event;
	while (GraphicsManager::window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			GraphicsManager::window.close();
	}
}

void Game::draw()
{
	GraphicsManager::window.clear();

	ScreenManager::currentScreen->draw();

	GraphicsManager::window.display();
}