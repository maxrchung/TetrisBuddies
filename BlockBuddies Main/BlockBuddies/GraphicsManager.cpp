#include "GraphicsManager.hpp"
#include <stdlib.h>
#include <time.h>
#include "InputManager.hpp"
#include "Game.hpp"

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
	window.create(sf::VideoMode::getDesktopMode(), 
				  "Block Buddies",
				  sf::Style::None);

	// In case we run into choppy display issues
	window.setVerticalSyncEnabled(true);

	// Sets a scale factor based on the height to an arbitrary number
	// I just chose 800.0f since that's the height of my default laptop
	// height resolution
	scale = GraphicsManager::window.getSize().y / 800.0f;

	// The font size of a title, such as LOGIN, REGISTER, RESULTS
	titleSize = 48 * scale;

	// The font size of a button label, such as the "Enter" text of an Enter Button
	labelSize = 24 * scale;

	// Font size of a message, i.e. for instructions, error messages, text display, etc.
	messageSize = 16 * scale;

	// This can be switched out, but I like this as a Title/Button font
	labelFont.loadFromFile("Roboto-Regular.ttf");

	// Font of the message, for now it is the same as label, but it can be switched out
	messageFont.loadFromFile("Roboto-Regular.ttf");	

	// Sets the framerate for the window drawing, note that I do not think this
	// actually applies for the actual game updates
	framerate = 60;
	window.setFramerateLimit(GraphicsManager::framerate);

	// Every time the game is opened, a random color is generated
	// Note that the colors all have the same hue but different shading
	srand(time(NULL));
	sf::Color c(rand() % 85, rand() % 85, rand() % 85);

	backgroundColor =	sf::Color(c.r + 85*2, c.g + 85*2, c.b + 85*2);
	sectionColor =		sf::Color(c.r + 85*1, c.g + 85*1, c.b + 85*1);
	buttonColor =		sf::Color(c.r + 85*0, c.g + 85*0, c.b + 85*0);

	// Select and Type color currently pull values from the above
	// They represent respectively the darkest and lightest colors
	selectColor =       buttonColor;
	typeColor =         backgroundColor;
}

// getCenter() is a utility function for getting the origin of an object
// Usually this will be combined with a setOrigin() call to set the Position to
// the center of an object
sf::Vector2f GraphicsManager::getCenter(const sf::Text& text, Bounds bounds)
{
	sf::FloatRect textRect;

	// Finding the center of a sf::Text object can be kind of tricky because
	// different letters give different heights, thus throwing off calculations.
	// I found the below solution on a stackoverflow post that seems to resolve
	// the issue. It uses getLocal/getGlobalBounds()'s top and left (which may not necessarily
	// be 0,0) for placement
	if (bounds == Bounds::LOCAL)
		textRect = text.getLocalBounds();
	else if (bounds == Bounds::GLOBAL)
		textRect = text.getGlobalBounds();

	return sf::Vector2f((float)(int)(textRect.left + textRect.width/2.0f),
                        (float)(int)(textRect.top + textRect.height / 2.0f));
}

// Basically does the same thing as getCenter except only applies any
// change in the y-direction
sf::Vector2f GraphicsManager::getLeftCenter(const sf::Text& text, Bounds bounds)
{
	sf::FloatRect textRect;

	if (bounds == Bounds::LOCAL)
		textRect = text.getLocalBounds();
	else if (bounds == Bounds::GLOBAL)
		textRect = text.getGlobalBounds();

	return sf::Vector2f((float)(int)(textRect.left),
                        (float)(int)(textRect.top + textRect.height / 2.0f));
}

// Finds the right center point of a Text object
sf::Vector2f GraphicsManager::getRightCenter(const sf::Text& text, Bounds bounds)
{
	sf::FloatRect textRect;

	if (bounds == Bounds::LOCAL)
		textRect = text.getLocalBounds();
	else if (bounds == Bounds::GLOBAL)
		textRect = text.getGlobalBounds();

	return sf::Vector2f((float)(int)(textRect.left + textRect.width),
                        (float)(int)(textRect.top + textRect.height / 2.0f));
}

// Overloaded getCenter() function for sf::RectangleShape
sf::Vector2f GraphicsManager::getCenter(const sf::RectangleShape& rectangle, Bounds bounds)
{
	sf::FloatRect rect;

	if (bounds == Bounds::LOCAL)
		rect = rectangle.getLocalBounds();
	else if (bounds == Bounds::GLOBAL)
		rect = rectangle.getGlobalBounds();
    
	return sf::Vector2f((float)(int)(rect.left + rect.width/2.0f),
                        (float)(int)(rect.top + rect.height/2.0f));		
}

// Returns the left-center point of a rectangle
sf::Vector2f GraphicsManager::getLeftCenter(const sf::RectangleShape& rectangle, Bounds bounds)
{
	sf::FloatRect rect;

	if (bounds == Bounds::LOCAL)
		rect = rectangle.getLocalBounds();
	else if (bounds == Bounds::GLOBAL)
		rect = rectangle.getGlobalBounds();

	return sf::Vector2f((float)(int)(rect.left),
                        (float)(int)(rect.top + rect.height/2.0f));		
}

// Finds the right center point of a rectangle
sf::Vector2f GraphicsManager::getRightCenter(const sf::RectangleShape& rectangle, Bounds bounds)
{
	sf::FloatRect rect;

	if (bounds == Bounds::LOCAL)
		rect = rectangle.getLocalBounds();
	else if (bounds == Bounds::GLOBAL)
		rect = rectangle.getGlobalBounds();

	return sf::Vector2f((float)(int)(rect.left + rect.width),
                        (float)(int)(rect.top + rect.height/2.0f));
}