#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "SFML/Graphics.hpp"
#include "UIElement.hpp"

class Button : public UIElement
{
public:
	Button(Screens toScreen,
	       char* label,	
		   float x,
		   float y,
		   float width,
		   float height);
	void update();
	void draw();

	Screens toScreen;
	sf::RectangleShape boundingRect;
	sf::Text label;
};

#endif BUTTON_HPP