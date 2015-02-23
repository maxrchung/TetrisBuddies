#include "Section.hpp"

Section::Section(float posX,
	             float posY,
				 float width,
				 float height,
                 sf::Color color,
                 bool drawBorder)
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

    float scale = GraphicsManager::getInstance()->scale;
    if(drawBorder)
    {
        for(int i = 0; i < 16; i++)
        {
            float side = (float)(rand() % 50 + 10);
            sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(side, side));
            block.setPosition(boundingRect.getPosition());

            // Decides which side of the border to go
            int direction = rand() % 6;

            // top
            if(direction == 0)
            {
                int width = boundingRect.getLocalBounds().width - block.getLocalBounds().width;
                width = rand() % width;
                block.move(ceil((-boundingRect.getLocalBounds().width/2+ width) * scale),
                           ceil((-boundingRect.getLocalBounds().height/2 -block.getLocalBounds().width)) * scale);
            }

            // left
            else if(direction == 1 || direction == 2)
            {
                int height = boundingRect.getLocalBounds().height - block.getLocalBounds().height;
                height = rand() % height;
                block.move(ceil((-boundingRect.getLocalBounds().width/2 - block.getLocalBounds().width)) * scale,
                           ceil(-boundingRect.getLocalBounds().height /2.0f + height) * scale);
            }

            // Right
            else if(direction == 3 || direction == 4)
            {
                int height = boundingRect.getLocalBounds().height - block.getLocalBounds().height;
                height = rand() % height;
                block.move(ceil((boundingRect.getLocalBounds().width/2.0f)) * scale,
                           ceil((-boundingRect.getLocalBounds().height/2.0f + height)) * scale);
            }

            // Bottom
            else if (direction == 5)
            {
                int width = boundingRect.getLocalBounds().width - block.getLocalBounds().width;
                width = rand() % width;
                block.move(ceil((-boundingRect.getLocalBounds().width/2.0f + width) * scale),
                           ceil(boundingRect.getLocalBounds().height/2.0f) * scale);
            }

            sf::Vector2f center = GraphicsManager::getInstance()->getCenter(block);
            block.setOrigin(center);
            block.move(center.x * scale, center.y * scale);

            bool toContinue = false;
            for(auto& placedBlock : blockBorder)
            {
                if(placedBlock.getGlobalBounds().intersects(block.getGlobalBounds()))
                {
                    i--;
                    toContinue = true;
                    break;
                }
            }

            if(toContinue)
                continue;

            blockBorder.push_back(block);
        }

    }
}

void Section::update()
{
}

#include <iostream>
void Section::draw()
{
    sf::Color adjustColor = boundingRect.getFillColor();
    adjustColor.a = colorFade.value;
    if(boundingRect.getFillColor() != sf::Color::Transparent)
        boundingRect.setFillColor(adjustColor);
    else
    {
        adjustColor = boundingRect.getOutlineColor();
        adjustColor.a = colorFade.value;
        boundingRect.setOutlineColor(adjustColor);
    }
    float scaleFactor = GraphicsManager::getInstance()->scale * (fade.value/255.0f / 4.0f + 0.75f);
    boundingRect.setScale(sf::Vector2f(scaleFactor, scaleFactor));

    sf::Vector2f prevPosition = boundingRect.getPosition();

    if(fade.state == FadeStates::FADING_IN)
        boundingRect.move(sf::Vector2f(0, (1 - fade.value/255.0f) * -128));
    else if(fade.state == FadeStates::FADING_OUT)
        boundingRect.move(sf::Vector2f(0, (1 - fade.value/255.0f) * 128));

	GraphicsManager::getInstance()->window.draw(boundingRect);

    boundingRect.setPosition(prevPosition);

    for(auto& block : blockBorder)
    {
        block.setFillColor(adjustColor);
        block.setScale(sf::Vector2f(scaleFactor, scaleFactor));
        prevPosition = block.getPosition();
        if (fade.state == FadeStates::FADING_IN)
            block.move(sf::Vector2f(0, (1 - fade.value / 255.0f) * -128));
        else if (fade.state == FadeStates::FADING_OUT)
            block.move(sf::Vector2f(0, (1 - fade.value / 255.0f) * 128));
        GraphicsManager::getInstance()->window.draw(block);
        block.setPosition(prevPosition);
    }
}