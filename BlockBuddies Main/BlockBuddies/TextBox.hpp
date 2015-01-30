#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"

// TextBox for just displaying text on the screen, no
// flairs attached
class TextBox : public UIElement
{
public:
	TextBox(char* message,
		    float posX,  
		    float posY,
			float width,

			// Alignment denotes where it is drawn from.
			// By default it is by the center, but for some
			// uses it could be drawn from the left
			Alignments textAlignment = Alignments::CENTER,
			// Denotes whether to use a larger font to
			// indicate that this is a title
			bool isTitle = false);

	TextBox(std::string message,
		float posX,
		float posY,
		float width,
		Alignments textAlignment = Alignments::CENTER,
		bool isTitle = false);

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
};

#endif TEXTBOX_HPP