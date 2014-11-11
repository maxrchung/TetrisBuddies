#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Screen.hpp"
#include "ScreenManager.hpp"
#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include "Selectable.hpp"

// Is a UIElement, added into UIElements vector in UIManager
class Button : public UIElement, public Selectable
{
public:
	       // Tells what screen to go to
	       // Note that it takes in an enum. We want to avoid putting
	       // an entire Screen in directly because then the UIElements
	       // of the toScreen will be instantiated before we actually 
	       // need them
	Button(Screens toScreen,
	       char* label,	
		   
		   // Parameters for its boundingRect
		   // Note that posX and posY give the center coordinates
		   // for the button
		   float posX,
		   float posY,
		   float width,
		   float height);
	void update();
	void draw();

	Screens toScreen;

	// Displayed rect of the button
	sf::RectangleShape boundingRect;

	sf::Text label;

	// Boolean check on whether a button has been clicked on
	bool isActivated = false;
};

#endif BUTTON_HPP