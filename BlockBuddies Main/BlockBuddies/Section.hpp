#ifndef SECTION_HPP
#define SECTION_HPP

#include "UIElement.hpp"
#include "SFML/Graphics.hpp"

// This is a UIElement that is basically responsible for just
// displaying a colored rectangle. It's basically a glorified
// RectangleShape object, positioned and centered properly
class Section : public UIElement
{
public:
	// Sections are always drawn from its center
	Section(float posX,
		    float posY,
			float width,
			float height);
	void update();
	void draw();

private:
	sf::RectangleShape boundingRect;
};

#endif//SECTION_HPP