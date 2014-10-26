#include "GraphicsManager.hpp"
#include <stdlib.h>
#include <time.h>

GraphicsManager* GraphicsManager::instance = NULL;

// Gets the instance to do things with
// Only makes a new GraphicsManager at initialization
GraphicsManager* GraphicsManager::getInstance()
{
	if(!instance)
		instance = new GraphicsManager;
	return instance;
}

// No constructor allowed for a singleton, so we have a init() function that basically 
// does that job
void GraphicsManager::init()
{
	// Sets window to fullscreen
	window.create(sf::VideoMode::getFullscreenModes()[0], 
				  "Block Buddies", 
				  sf::Style::Fullscreen);

	// Sets a scale factor based on the height to an arbitrary number
	// I just chose 800.0f since that's the height of my default laptop
	// height resolution
	scale = GraphicsManager::window.getSize().y / 800.0f;

	// The font size of a button label, such as the "Login" text of the login Button
	labelSize = 25 * scale;

	// This can be switched out, but I like this as a Title/Button font
	// This is also the standard Android font I believe
	labelFont.loadFromFile("Roboto-Thin.ttf");

	// Sets the framerate for the window drawing, note that I do not think this
	// actually applies for the actual game updates
	framerate = 60;
	window.setFramerateLimit(GraphicsManager::framerate);

	// Every time the game is opened, a random color is generated
	// Note that the colors all have the same hue but different shading
	srand(time(NULL));
	sf::Color c(rand() % 64, rand() % 64, rand() % 64);
	backgroundColor =	sf::Color(c.r + 64*2, c.g + 64*2, c.b + 64*2);
	sectionColor =		sf::Color(c.r + 64*1, c.g + 64*1, c.b + 64*1);
	buttonColor =		sf::Color(c.r + 64*0, c.g + 64*0, c.b + 64*0);
	labelColor =		sf::Color(255, 255, 255);

	// Since the background is always going to be the same, we might as well
	// just put it in here so that it so it's reachable by everything
	background = sf::RectangleShape(sf::Vector2f(window.getSize()));
	background.setFillColor(GraphicsManager::backgroundColor);
}

// getCenter() is a utility function for getting the origin of an object
// Usually this will be combined with a setOrigin() call to set the Position to
// the center of an object
sf::Vector2f GraphicsManager::getCenter(const sf::Text& text)
{
	// The y offset needs to be lifted a bit because of (what I think are) line
	// spacing issues
	sf::Vector2f center = text.getPosition();
	center += sf::Vector2f(text.getGlobalBounds().width / 2.0f,
						   text.getGlobalBounds().height / 2.0f
						   + labelFont.getLineSpacing(labelSize)
						   - labelSize); 
	return center;
}

// There are different calculations for finding the center of a Text object and
// a RectangleShape object, so that's why there are multiple getCenter() functions
sf::Vector2f GraphicsManager::getCenter(const sf::RectangleShape& rectangle)
{
	sf::Vector2f center = rectangle.getPosition();
	center += rectangle.getSize() / 2.0f;
	return center;
}