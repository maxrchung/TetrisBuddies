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
	backspace = false;
	input = sf::String();
}

// Loops through window events and updates booleans to keep track of key/mouse presses
void InputManager::update()
{
	mouseReleased = false;
	backspace = false;
	input.clear();

	sf::Event event;	
	while (GraphicsManager::getInstance()->window.pollEvent(event))
	{
		switch (event.type)
		{
		// This should run in the case of alt+f4
		case sf::Event::Closed:
			Game::isRunning = false;
			break;
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::BackSpace)
			{
				backspace = true;
				break;
			}
			break;
		case sf::Event::TextEntered:
			if (event.text.unicode < 128)
				input = event.text.unicode;
			break;
		case sf::Event::MouseButtonReleased:
			mouseReleased = true;
			break;
		default:
			break;
		}
	}
}