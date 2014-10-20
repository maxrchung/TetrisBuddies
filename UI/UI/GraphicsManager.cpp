#include "GraphicsManager.hpp"
#include <stdlib.h>
#include <time.h>


sf::RenderWindow GraphicsManager::window(sf::VideoMode::getFullscreenModes()[0], 
										 "Block Buddies", 
										 sf::Style::Fullscreen);
sf::RectangleShape GraphicsManager::background(sf::Vector2f(GraphicsManager::window.getSize()));
sf::Font GraphicsManager::labelFont;
int GraphicsManager::labelSize = 30;
int GraphicsManager::framerate = 60;
sf::Color GraphicsManager::backgroundColor;
sf::Color GraphicsManager::buttonColor;
sf::Color GraphicsManager::sectionColor;
sf::Color GraphicsManager::labelColor;

void GraphicsManager::init()
{
	// Random colors that have the same hue but different shade
	srand(time(NULL));
	sf::Color c(rand() % 64, rand() % 64, rand() % 64);
	backgroundColor =	sf::Color(c.r + 64*2, c.g + 64*2, c.b + 64*2);
	sectionColor =		sf::Color(c.r + 64*1, c.g + 64*1, c.b + 64*1);
	buttonColor =		sf::Color(c.r + 64*0, c.g + 64*0, c.b + 64*0);
	labelColor =		sf::Color(255, 255, 255);

	// Since background will most likely be universal, I just made it in here
	background.setFillColor(GraphicsManager::backgroundColor);

	window.setFramerateLimit(GraphicsManager::framerate);
	labelFont.loadFromFile("Roboto-Thin.ttf");
}

// getCenter() and setCenter() are utility functions to make placement of objects 
// easier. They are not inherently provided by SFML
sf::Vector2f GraphicsManager::getCenter(const sf::Text& text)
{
	sf::Vector2f center = text.getPosition();
	center += sf::Vector2f(text.getGlobalBounds().width / 2.0f,
						   text.getGlobalBounds().height / 2.0f);
	return center;
}

sf::Vector2f GraphicsManager::getCenter(const sf::RectangleShape& rectangle)
{
	sf::Vector2f center = rectangle.getPosition();
	center += rectangle.getSize() / 2.0f;
	return center;
}

void GraphicsManager::setCenter(sf::Text& text, const sf::Vector2f position)
{
	// The y offset needs to be lifted a bit because of (what I think are) line
	// spacing issues
	text.setPosition(position.x - text.getGlobalBounds().width / 2.0f,
					 position.y - text.getGlobalBounds().height / 2.0f 
						- labelFont.getLineSpacing(labelSize)
						+ labelSize); 
}

void GraphicsManager::setCenter(sf::RectangleShape& rectangle, const sf::Vector2f position)
{
	rectangle.setPosition(position.x - rectangle.getSize().x / 2.0f,
						  position.y - rectangle.getSize().y / 2.0f);
}