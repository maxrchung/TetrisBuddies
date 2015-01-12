#include "InputManager.hpp"
#include "GraphicsManager.hpp"
#include "Game.hpp"
#include "ScreenManager.hpp"

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
	enter = false;
	tab = false;
    left = false;
    right = false;
    up = false;
    down = false;
    home = false;
    end = false;
    del = false;
    a = false;
	input = sf::String();
}

// Loops through window events and updates booleans to keep track of key/mouse presses
void InputManager::update()
{
	// Resets all booleans and inputs before starting future checks
	mouseReleased = false;
	backspace = false;
	enter = false;
	tab = false;
    escape = false;
    left = false;
    right = false;
    up = false;
    down = false;
    home = false;
    end = false;
    del = false;
    a = false;

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
            ScreenManager::getInstance()->closeGame();
			break;

	    // Checks for key down
		case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Left)
                left = true;
            else if(event.key.code == sf::Keyboard::Right)
                right = true;
            else if(event.key.code == sf::Keyboard::Up)
                up = true;
            else if(event.key.code == sf::Keyboard::Down)
                down = true;
			else if(event.key.code == sf::Keyboard::BackSpace)
				backspace = true;
			else if(event.key.code == sf::Keyboard::Return)
				enter = true;
			else if(event.key.code == sf::Keyboard::Tab)			
				tab = true;
            else if(event.key.code == sf::Keyboard::Escape)
                escape = true;
            else if(event.key.code == sf::Keyboard::Home)
                home = true;
            else if(event.key.code == sf::Keyboard::End)
                end = true;
            else if(event.key.code == sf::Keyboard::Delete)
                del = true;
            else if(event.key.code == sf::Keyboard::A)
                a = true;
			break;

		// Reads in any entered key, see Events Explained in SFML 2.1
		// for more details. Basically, anything you enter is read into
		// the input variable
		case sf::Event::TextEntered:
			// We start at unicode 31 so we avoid inputting things like
			// backspace and tab into input
			if (event.text.unicode > 31)
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