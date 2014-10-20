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
	// Buttons should universally have the same color
	this->boundingRect.setFillColor(GraphicsManager::buttonColor);
	this->label.setColor(GraphicsManager::labelColor);
}

void Button::update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(GraphicsManager::window);
		if (boundingRect.getGlobalBounds().contains((float) mousePosition.x,
													(float) mousePosition.y))
			ScreenManager::switchScreen(toScreen);
	}
}

void Button::draw()
{
	GraphicsManager::window.draw(boundingRect);
	GraphicsManager::window.draw(label);
}