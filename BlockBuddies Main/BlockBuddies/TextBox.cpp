#include "TextBox.hpp"
#include "GraphicsManager.hpp"

TextBox::TextBox(char* message,
                 float posX,
				 float posY,
				 Alignments alignment,
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

	// Sets the message color of the TextBox
	this->message.setColor(GraphicsManager::getInstance()->typeColor);

	// Determines whether it is drawn based by the TextBox's left-center or by the center
	if (alignment == Alignments::LEFT)
		this->message.setOrigin(GraphicsManager::getInstance()->getLeftCenter(this->message));
	else if (alignment == Alignments::CENTER)
		this->message.setOrigin(GraphicsManager::getInstance()->getCenter(this->message));

	// Sets the message position, by first going to the center of the screen and then moving 
	// a scaled distance away
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

void TextBox::setString(std::string newMessage)
{
	message.setString(newMessage);
}