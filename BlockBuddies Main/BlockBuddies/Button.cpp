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
	// Sets the color, origin, position, and scale of the boundingRect
	// The position is first set to the center of the screen and then placed a set
	// scaled distance away
	boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
	boundingRect.setOrigin(GraphicsManager::getInstance()->getCenter(boundingRect));
	boundingRect.setScale(GraphicsManager::getInstance()->scale, GraphicsManager::getInstance()->scale);
	boundingRect.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize())/2.0f);
	boundingRect.move(posX * GraphicsManager::getInstance()->scale, posY * GraphicsManager::getInstance()->scale);

	// Sets the color, origin, and position of the text label
	// The position is set to the center of the boundingRect
	// We use this-> because of naming issues, it may be a good idea to change the parameter
	// name to resolve this issue; I can foresee this being an issue possibly in the future,
	// but because I want to stick to convention, after some thought, I decided not to change it
	this->label.setColor(GraphicsManager::getInstance()->typeColor);
	this->label.setOrigin(GraphicsManager::getInstance()->getCenter(this->label));
	this->label.setPosition(boundingRect.getPosition());
}

void Button::update()
{
	// We initialize this outside so we don't make new 
	// variables for it further down
	sf::Vector2i mousePosition = sf::Mouse::getPosition(GraphicsManager::getInstance()->window);

	// Checks if the mouse is hovering over the button,
	// if so then change to the selected color
	if (boundingRect.getGlobalBounds().contains((float) mousePosition.x,
                                                (float) mousePosition.y) ||
		isSelected)
	{
		boundingRect.setFillColor(GraphicsManager::getInstance()->backgroundColor);
		label.setColor(GraphicsManager::getInstance()->selectColor);
	}

	// Else return the color to its original state
	else
	{
		boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
		label.setColor(GraphicsManager::getInstance()->typeColor);
	}

	// Checks for mouse click onto the button
	// This needs to be at the end of update() because if we switchScreen too early,
	// we may end up referencing variables that are already deleted
	if (InputManager::getInstance()->mouseReleased)
	{
		// If inside the bounds, then activate the button
		// The Screen will verify that a button is updated and switchscreens
		if (boundingRect.getGlobalBounds().contains((float) mousePosition.x,
													(float) mousePosition.y))
		    isActivated = true;
	}
}

void Button::draw()
{
	GraphicsManager::getInstance()->window.draw(boundingRect);
	GraphicsManager::getInstance()->window.draw(label);
}

