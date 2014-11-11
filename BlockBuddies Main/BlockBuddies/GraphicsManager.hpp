#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP

#include "SFML/Graphics.hpp"

// Indicates whether to find a local or global bound
enum Bounds 
{
	LOCAL,
	GLOBAL
};

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
	// The Bounds parameter indicates whether to find a local bound or a global bound
	// Situations using either or may vary. When manipulating the origin of objects,
	// for example, I needed to always use getLocalBound(), but when finding position,
	// getGlobalBound() is more used
	// The default parameter is as noted, local
	sf::Vector2f getCenter(const sf::Text& text, Bounds = Bounds::LOCAL);
	sf::Vector2f getCenter(const sf::RectangleShape& rectangle, Bounds = Bounds::LOCAL);
	sf::Vector2f getLeftCenter(const sf::Text& text, Bounds = Bounds::LOCAL);
	sf::Vector2f getLeftCenter(const sf::RectangleShape& rectangle, Bounds = Bounds::LOCAL);
	sf::Vector2f getRightCenter(const sf::Text& text, Bounds = Bounds::LOCAL);
	sf::Vector2f getRightCenter(const sf::RectangleShape& rectangle, Bounds = Bounds::LOCAL);

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