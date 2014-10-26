#include "Button.hpp"
#include "GraphicsManager.hpp"
#include "SFML/Window.hpp"
#include "ScreenManager.hpp"

Button::Button(Screen* toScreen,
			   sf::RectangleShape boundingRect,
			   sf::Text label)
	:toScreen(toScreen),
	 boundingRect(boundingRect),
	 label(label)
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
}

void Button::update()
{
	// Checks for mouse click onto the button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(GraphicsManager::getInstance()->window);
		if (boundingRect.getGlobalBounds().contains((float) mousePosition.x,
													(float) mousePosition.y))
			ScreenManager::getInstance()->switchScreen(toScreen);
	}
}

void Button::draw()
{
	GraphicsManager::getInstance()->window.draw(boundingRect);
	GraphicsManager::getInstance()->window.draw(label);
}