#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include "UIManager.hpp"

class TextInput: public UIElement
{
public:
	TextInput(float posX,
		      float posY,
			  float width,
			  float height,
			  Alignment alignment = Alignment::CENTER,
			  bool isProtected = false);
	void update();
	void draw();
	
	sf::RectangleShape boundingRect;
	Alignment alignment;
	bool isProtected;

	// Boolean check for whether or not the textbox is clicked on
	// and thus selected
	bool isSelected;
	sf::Text input;
};

#endif//TEXTINPUT_HPP