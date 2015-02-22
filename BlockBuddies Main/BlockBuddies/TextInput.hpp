#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
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
			  Alignments drawAlignment = Alignments::CENTER,
			  Alignments textAlignment = Alignments::CENTER,
			  bool isProtected = false);
	void update();
	void draw();

    // input is what the user types in
    // protectedInput is only used when the TextInput's isProtected is true,
    //     and it changes the input to all asterisks
    // displayedInput is what is actually drawn to the screen, may be different
    //     depending if letters are past the TextInput's boundingRect
	sf::Text input;
	sf::Text protectedInput;
    sf::Text displayedInput;

	// Private class for handling the cursor within TextInput
	class InputCursor {
	public:
		InputCursor();
		void update();
		void draw();

		sf::Clock blinkTimer;

		// Whether or not it is currently displayed or not
		bool isDisplayed = true;

        // Position of the cursor relative to the input index
        int index = -1;

		// We leave this public so that we can access it within TextInput
		sf::RectangleShape boundingRect;
	} inputCursor;

	sf::RectangleShape boundingRect;
	
private:
	Alignments drawAlignment;
	Alignments textAlignment;
	bool isProtected;
    bool selectAll = false;
};

#endif//TEXTINPUT_HPP