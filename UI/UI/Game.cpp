#include "Game.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "LoginScreen.hpp"

Game::Game()
{
	GraphicsManager::init();
	ScreenManager::init();
}

void Game::run() 
{
	update();
	draw();
}

void Game::update()
{
	sf::Event event;
	while (GraphicsManager::window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			GraphicsManager::window.close();
	}

	ScreenManager::currentScreen->update();
}

void Game::draw()
{
	GraphicsManager::window.clear();

	GraphicsManager::window.draw(GraphicsManager::background);
	ScreenManager::currentScreen->draw();

	GraphicsManager::window.display();
}