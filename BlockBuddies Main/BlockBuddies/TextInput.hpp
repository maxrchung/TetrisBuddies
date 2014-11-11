#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include "UIManager.hpp"
#include "Selectable.hpp"

// A UIElement that takes in input from the user
// The user must click on the box in order to select it
// for taking in input
class TextInput: public UIElement, public Selectable
{
public:
	TextInput(float posX,
		      float posY,
			  float width,
			  float height,

			  // Denotes how the TextInput is drawn, whether from
			  // the default center or by the left-center coordinate
			  Alignments alignment = Alignments::CENTER,
			  bool isProtected = false);
	void update();
	void draw();
	
	sf::RectangleShape boundingRect;
	Alignments alignment;
	bool isProtected;

	sf::Text input;
};

#endif//TEXTINPUT_HPP