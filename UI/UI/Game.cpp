#include "Game.hpp"
#include "Graphics.hpp"

Game::Game()
{
	Graphics::window.create(sf::VideoMode::getFullscreenModes()[0], "Block Buddies", sf::Style::Fullscreen);
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
	while (Graphics::window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			Graphics::window.close();
	}
}

void Game::draw()
{
	Graphics::window.clear();
	Graphics::window.display();
}