#include "Section.hpp"
#include "GraphicsManager.hpp"

Section::Section(float posX,
	             float posY,
				 float width,
				 float height)
    :boundingRect(sf::RectangleShape(sf::Vector2f(width, height)))
{
	boundingRect.setFillColor(GraphicsManager::getInstance()->sectionColor);
	boundingRect.setOrigin(GraphicsManager::getInstance()->getCenter(boundingRect));
	boundingRect.setScale(GraphicsManager::getInstance()->scale,
		                  GraphicsManager::getInstance()->scale);
	boundingRect.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize())/2.0f);
	boundingRect.move(posX * GraphicsManager::getInstance()->scale,
		              posY * GraphicsManager::getInstance()->scale);
}

void Section::update()
{
}


void Section::draw()
{
	GraphicsManager::getInstance()->window.draw(boundingRect);
}