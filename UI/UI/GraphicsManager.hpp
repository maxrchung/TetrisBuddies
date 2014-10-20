#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP

#include "SFML/Graphics.hpp"

class GraphicsManager
{
public:
	static void init();
	static sf::Vector2f getCenter(const sf::Text& text);
	static sf::Vector2f getCenter(const sf::RectangleShape& rectangle);
	static void setCenter(sf::Text& text, const sf::Vector2f position);
	static void setCenter(sf::RectangleShape& rectangle, const sf::Vector2f position);

	static sf::RenderWindow window;
	static sf::RectangleShape background;
	static sf::Font labelFont;
	static int framerate;
	static int labelSize;
	static sf::Color backgroundColor;
	static sf::Color buttonColor;
	static sf::Color sectionColor;
	static sf::Color labelColor;
};

#endif//GRAPHICSMANAGER_HPP