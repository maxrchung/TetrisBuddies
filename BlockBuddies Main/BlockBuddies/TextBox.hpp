#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include "UIManager.hpp"

class TextBox : public UIElement
{
public:
	TextBox(char* message,
		    float posX,
		    float posY,
			Alignment alignment = Alignment::CENTER,
			bool isTitle = false);
	void update();
	void draw();

	sf::Text message;
};

#endif TEXTBOX_HPP