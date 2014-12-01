#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Screen.hpp"
#include "SFML/Graphics.hpp"
#include "UIElement.hpp"
#include "Selectable.hpp"

enum Screens;

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
		   float height,
		   Alignments drawAlignment = Alignments::CENTER);
	void update();
	void draw();
	
	// I thought about leaving these two private and then having
	// const getter functions access these. But I prefer the ease in
	// just accessing these with a little bit shorter code and
	// not having to write additional code for both getter/setter checks.
	// May be loose holes later on when we access these everywhere and
	// potentially accidentally manipulate them
	Screens toScreen;
	// Boolean check on whether a button has been clicked on
	bool isActivated = false;
	sf::Text label;
	sf::RectangleShape boundingRect;
};

#endif//BUTTON_HPP