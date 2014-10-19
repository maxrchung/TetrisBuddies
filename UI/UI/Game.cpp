#include "Game.hpp"
#include "GraphicsManager.hpp"
#include <stdlib.h>
#include <time.h>
#include "LoginScreen.hpp"

Game::Game()
{
	srand(time(NULL));
	GraphicsManager::backgroundColor =	sf::Color(rand() % 64 + 64*3, rand() % 64 + 64*3, rand() % 64 + 64*3);
	GraphicsManager::sectionColor =		sf::Color(rand() % 64 + 64*2, rand() % 64 + 64*2, rand() % 64 + 64*2);
	GraphicsManager::buttonColor =		sf::Color(rand() % 64 + 64*1, rand() % 64 + 64*1, rand() % 64 + 64*1);
	GraphicsManager::labelColor =		sf::Color(255, 255, 255);

	GraphicsManager::window.setFramerateLimit(GraphicsManager::framerate);
	GraphicsManager::labelFont.loadFromFile("Roboto-Thin.ttf");
	GraphicsManager::background.setFillColor(GraphicsManager::backgroundColor);

	ScreenManager::switchScreen(new LoginScreen());
}

Game::~Game()
{
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