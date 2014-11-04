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
	// Resets all booleans and inputs before starting future checks
	mouseReleased = false;
	backspace = false;

	// Input is an sf::String, so we clear it before the events check
	input.clear();

	// Our while loop to check for each event in our event queue for
	// the GraphicManager's window
	sf::Event event;	
	while (GraphicsManager::getInstance()->window.pollEvent(event))
	{
		switch (event.type)
		{
		// This should run in the case of alt+f4
		case sf::Event::Closed:

			// May need to put more 
			Game::isRunning = false;
			break;

	    // Checks for key down
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::BackSpace)
				backspace = true;
			break;

		// Reads in any entered key, see Events Explained in SFML 2.1
		// for more details. Basically, anything you enter is read into
		// the input variable
		case sf::Event::TextEntered:
			input = event.text.unicode;
			break;

		// Checks for mouse up
		case sf::Event::MouseButtonReleased:
			mouseReleased = true;
			break;
			
		default:
			break;
		}
	}
}