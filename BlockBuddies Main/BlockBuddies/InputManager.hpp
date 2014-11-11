#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "SFML/Graphics.hpp"

// Manages input
// Parts of the program can call and check if booleans
// corresponding to a key is pressed down.
class InputManager
{
public:
	static InputManager* getInstance();
	void init();
	void update();

	// Checks for mouse up
	bool mouseReleased;

	// Takes in any pressed down key
	sf::String input;

	// Checks for key down
	bool backspace;
	bool enter;
	bool tab;
	
private:
	InputManager(){};
	InputManager(InputManager const&){};
	InputManager& operator=(InputManager const&){};

	static InputManager* instance;
};

#endif//INPUTMANAGER_HPP