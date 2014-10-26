#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP

#include "SFML/Graphics.hpp"

class GraphicsManager
{
public:
	static GraphicsManager* getInstance();
	void init();

	sf::Vector2f getCenter(const sf::Text& text);
	sf::Vector2f getCenter(const sf::RectangleShape& rectangle);

	sf::RenderWindow window;
	float scale;
	sf::RectangleShape background;
	sf::Font labelFont;
	int framerate;
	int labelSize;
	sf::Color backgroundColor;
	sf::Color buttonColor;
	sf::Color sectionColor;
	sf::Color labelColor;
private:
	GraphicsManager(){};
	GraphicsManager(GraphicsManager const&){};
	GraphicsManager& operator=(GraphicsManager const&){};

	static GraphicsManager* instance;
};

#endif//GRAPHICSMANAGER_HPP