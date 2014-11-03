#ifndef SECTION_HPP
#define SECTION_HPP

#include "UIElement.hpp"
#include "SFML/Graphics.hpp"

class Section : public UIElement
{
public:
	Section(float posX,
		    float posY,
			float width,
			float height);
	void update();
	void draw();

	sf::RectangleShape boundingRect;
};

#endif//SECTION_HPP