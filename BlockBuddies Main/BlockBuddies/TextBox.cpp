#include "TextBox.hpp"
#include "GraphicsManager.hpp"

TextBox::TextBox(char* message,
                 float posX,
				 float posY,
				 Alignment alignment,
				 bool isTitle)
    :message(sf::Text(message,
                      GraphicsManager::getInstance()->messageFont,
					  GraphicsManager::getInstance()->messageSize))
{
	// The isTitle parameter indicates whether or not the textbox is a larger title
	// e.g. "Login" for the LoginScreen, or just a normal instructions e.g. "Enter credentials below"
	// Right now, they are only differentiated by two different font sizes
	// If we would like, we could change the parameter to accept a font size, or
	// change the font of either within GraphicsManager
	if (isTitle)
		this->message.setCharacterSize(GraphicsManager::getInstance()->titleSize);

	this->message.setColor(GraphicsManager::getInstance()->typeColor);
	if (alignment == Alignment::LEFT)
		this->message.setOrigin(GraphicsManager::getInstance()->getLeftCenter(this->message));
	else if (alignment == Alignment::CENTER)
		this->message.setOrigin(GraphicsManager::getInstance()->getCenter(this->message));
	this->message.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize()) / 2.0f);
	this->message.move(posX * GraphicsManager::getInstance()->scale,
		               posY * GraphicsManager::getInstance()->scale);
}

void TextBox::update()
{
}

void TextBox::draw()
{
	GraphicsManager::getInstance()->window.draw(message);
}