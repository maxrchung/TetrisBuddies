#include "GraphicsManager.hpp"


sf::RenderWindow GraphicsManager::window(sf::VideoMode::getFullscreenModes()[0], 
										 "Block Buddies", 
										 sf::Style::Fullscreen);
sf::RectangleShape GraphicsManager::background(sf::Vector2f(GraphicsManager::window.getSize()));
sf::Font GraphicsManager::labelFont;
int GraphicsManager::labelSize = 20;
int GraphicsManager::framerate = 60;
sf::Color GraphicsManager::backgroundColor;
sf::Color GraphicsManager::buttonColor;
sf::Color GraphicsManager::sectionColor;
sf::Color GraphicsManager::labelColor;

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
	center += (rectangle.getSize() / 2.0f);
	return center;
}

void GraphicsManager::setCenter(sf::Text& text, const sf::Vector2f position)
{
	text.setPosition(position.x - text.getGlobalBounds().width / 2.0f,
					 position.y - text.getGlobalBounds().height / 2.0f);
}

void GraphicsManager::setCenter(sf::RectangleShape& rectangle, const sf::Vector2f position)
{
	rectangle.setPosition(position.x - rectangle.getSize().x / 2.0f,
						  position.y - rectangle.getSize().y / 2.0f);
}