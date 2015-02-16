#include "Section.hpp"

Section::Section(float posX,
	             float posY,
				 float width,
				 float height,
                 sf::Color color)
    :boundingRect(sf::RectangleShape(sf::Vector2f(width, height))), color(color)
{
	// Sets the color, origin, scale, and position of the section
	// These are always centered so there are no Alignments to take care of
	boundingRect.setFillColor(color);
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

#include <iostream>
void Section::draw()
{
    sf::Color adjustColor = boundingRect.getFillColor();
    adjustColor.a = fade.value;
    if(boundingRect.getFillColor() != sf::Color::Transparent)
        boundingRect.setFillColor(adjustColor);
    else
    {
        adjustColor = boundingRect.getOutlineColor();
        adjustColor.a = fade.value;
        boundingRect.setOutlineColor(adjustColor);
    }
    float scaleFactor = GraphicsManager::getInstance()->scale * (fade.value/255.0f / 4.0f + 0.75f);
    boundingRect.setScale(sf::Vector2f(scaleFactor, scaleFactor));
	GraphicsManager::getInstance()->window.draw(boundingRect);
}