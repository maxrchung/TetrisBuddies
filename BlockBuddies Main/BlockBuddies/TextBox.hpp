#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"

// TextBox for just displaying text on the screen, no
// flairs attached
class TextBox : public UIElement
{
public:
	TextBox(std::string message,
		float posX,
		float posY,
		float width,
		Alignments textAlignment = Alignments::CENTER,
		bool isTitle = false,
        bool borderOutline = false);

	void update();
	void draw();
	sf::Text message;

private:
	void textWrap();
	float boundingWidth;

	// Used to check if there is a change in the message
	sf::Text prevMessage;

	// Determines how the text is aligned
	Alignments textAlignment;

	// Target position is used in case we need to reposition the text
	// e.g. when a status is altered
	sf::Vector2f targetPosition;

    bool isTitle;
    bool borderOutline;
};

#endif TEXTBOX_HPP