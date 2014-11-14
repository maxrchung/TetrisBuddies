#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include "UIManager.hpp"

// TextBox for just displaying text on the screen, no
// flairs attached
class TextBox : public UIElement
{
public:
	TextBox(char* message,
		    float posX,
		    float posY,

			// Alignment denotes where it is drawn from.
			// By default it is by the center, but for some
			// uses it could be drawn from the left
			Alignments alignment = Alignments::CENTER,
			// Denotes whether to use a larger font to
			// indicate that this is a title
			bool isTitle = false);
	void update();
	void draw();
	void setString(std::string newMessage);

private:
	sf::Text message;
};

#endif TEXTBOX_HPP