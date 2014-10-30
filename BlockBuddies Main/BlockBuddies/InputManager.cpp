#include "InputManager.hpp"
#include "GraphicsManager.hpp"
#include "Game.hpp"

InputManager* InputManager::instance;

InputManager* InputManager::getInstance()
{
	if (!instance)
		instance = new InputManager();

	return instance;
}

void InputManager::init()
{
	mouseReleased = false;
}

// Loops through window events and updates booleans to keep track of key/mouse presses
void InputManager::update()
{
	mouseReleased = false;

	sf::Event event;	
	while (GraphicsManager::getInstance()->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
			mouseReleased = true;
			break;
		// This should run in the case of alt+f4
		case sf::Event::Closed:
			Game::isRunning = false;
			break;
		default:
			break;
		}
	}
}