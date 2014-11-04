#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP

#include "SFML/Graphics.hpp"

// Holds the window used for drawing everything
// Has a few utility functions to finding points easier
// Holds a bunch of variables for scaling, font sizes,
// colors, etc. related to graphics
class GraphicsManager
{
public:
	// Singleton getInstance function
	static GraphicsManager* getInstance();
	void init();

	// Utility/overloaded functions for some efficiency
	sf::Vector2f getCenter(const sf::Text& text);
	sf::Vector2f getCenter(const sf::RectangleShape& rectangle);
	sf::Vector2f getLeftCenter(const sf::Text& text);
	sf::Vector2f getLeftCenter(const sf::RectangleShape& rectangle);

	// What everything is drawn to
	sf::RenderWindow window;

	// Scale factor based off of the height compared to arbitrary 
	// number. For now, I've set it as 800, my base resolution
	float scale;

	// Since it's going to be the same for every screen, the background
	// is just made here
	sf::RectangleShape background;

	// Font sizes
	int titleSize;
	int labelSize;
	int messageSize;

	// Different fonts
	// For now, I've set it as the same, but we can consider changing
	// them if we'd like. Personally, I like just sticking with one
	sf::Font labelFont;
	sf::Font messageFont;

	// Framerate of the window draws, right now is at 60FPS
	int framerate;

	// Colors to choose from
	// typeColor = backgroundColor and selectColor = buttonColor 
	// at the moment. I like how we use very few colors, but this
	// can be changed also
	sf::Color selectColor;
	sf::Color backgroundColor;
	sf::Color sectionColor;
	sf::Color buttonColor;
	sf::Color typeColor;
private:
	// Singleton overhead stuff to take care of
	GraphicsManager(){};
	GraphicsManager(GraphicsManager const&){};
	GraphicsManager& operator=(GraphicsManager const&){};

	static GraphicsManager* instance;
};

#endif//GRAPHICSMANAGER_HPP