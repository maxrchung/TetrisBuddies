#include "Button.hpp"
#include "GraphicsManager.hpp"
#include "SFML/Window.hpp"
#include "ScreenManager.hpp"
#include "UIManager.hpp"
#include "InputManager.hpp"

Button::Button(Screens toScreen,
	           char* label,
			   float posX,
			   float posY,
			   float width,
			   float height)
	:toScreen(toScreen),
	 boundingRect(sf::RectangleShape(sf::Vector2f(width, height))),
	 label(sf::Text(label,
					GraphicsManager::getInstance()->labelFont,
					GraphicsManager::getInstance()->labelSize))
{
	// All buttons share the same color, set within the GraphicsManager
	this->boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
	this->label.setColor(GraphicsManager::getInstance()->labelColor);

	// All buttons are drawn from the center, which this setOrigin() sets
	// Funnily enough, and you can test this to verify it, I'm pretty sure that
	// the order of setOrigin()/setScale()/setPosition() does not matter
	this->boundingRect.setOrigin(GraphicsManager::getInstance()->getCenter(this->boundingRect));

	// Scales the button size according to the value GraphicsManager sets
	this->boundingRect.setScale(GraphicsManager::getInstance()->scale, GraphicsManager::getInstance()->scale);

	// Sets the text Position to be the center
	this->label.setOrigin(GraphicsManager::getInstance()->getCenter(this->label));
	this->boundingRect.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize())/2.0f);

	// Moves the button a certain distance based on the scale
	this->boundingRect.move(posX * GraphicsManager::getInstance()->scale, posY * GraphicsManager::getInstance()->scale);

	// Positions the text to be in the center of the button
	this->label.setPosition(this->boundingRect.getPosition());
}

void Button::update()
{
	// Checks for mouse click onto the button
	// Will need to be modified in the future because as of now it detects mouse presses
	// too quickly. May have to use some event polling, or think of some way to implement
	// a InputManager singleton
	if (InputManager::getInstance()->mouseReleased)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(GraphicsManager::getInstance()->window);
		if (boundingRect.getGlobalBounds().contains((float) mousePosition.x,
													(float) mousePosition.y))
	        ScreenManager::getInstance()->switchScreen(toScreen);
	
		// Somewhere in here we'll need to hang and verify the database with the server
	}
}

void Button::draw()
{
	GraphicsManager::getInstance()->window.draw(boundingRect);
	GraphicsManager::getInstance()->window.draw(label);
}