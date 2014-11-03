#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "SFML/Graphics.hpp"

class InputManager
{
public:
	static InputManager* getInstance();
	void init();
	void update();
	bool mouseReleased;
	sf::String input;
	bool backspace;
	
private:
	InputManager(){};
	InputManager(InputManager const&){};
	InputManager& operator=(InputManager const&){};

	static InputManager* instance;
};

#endif//INPUTMANAGER_HPP