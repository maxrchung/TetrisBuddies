#include "Button.hpp"
#include "GraphicsManager.hpp"
#include "SFML/Window.hpp"
#include "ScreenManager.hpp"

Button::Button()
{

}

Button::Button(Screen* toScreen)
	:toScreen(toScreen)
{

}

Button::~Button()
{

}

void Button::draw()
{
	sf::CircleShape shape(100.f);
	GraphicsManager::window.draw(shape);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i localPosition = sf::Mouse::getPosition(GraphicsManager::window);
		if (localPosition.x > 0 && localPosition.x < 100 &&
			localPosition.y > 0 && localPosition.y < 100)
		{
			ScreenManager::switchScreen(toScreen);
		}
	}
}