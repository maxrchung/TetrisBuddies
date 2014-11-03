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
	sf::Vector2f getLeftCenter(const sf::Text& text);
	sf::Vector2f getLeftCenter(const sf::RectangleShape& rectangle);

	sf::RenderWindow window;
	float scale;
	sf::RectangleShape background;
	int titleSize;
	sf::Font labelFont;
	int labelSize;
	sf::Font messageFont;
	int messageSize;
	int framerate;
	sf::Color selectColor;
	sf::Color backgroundColor;
	sf::Color sectionColor;
	sf::Color buttonColor;
	sf::Color typeColor;
private:
	GraphicsManager(){};
	GraphicsManager(GraphicsManager const&){};
	GraphicsManager& operator=(GraphicsManager const&){};

	static GraphicsManager* instance;
};

#endif//GRAPHICSMANAGER_HPP