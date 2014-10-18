#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Screen.hpp"
#include "SFML/Graphics.hpp"

class Button 
{
public:
	Button(Screen& toScreen,
		   sf::RectangleShape boundingRect,
		   sf::Text label);
	~Button();
	void update();
	void draw();

	Screen& toScreen;
	sf::RectangleShape boundingRect;
	sf::Text label;
};

#endif BUTTON_HPP