#include "TextInput.hpp"
#include "InputManager.hpp"
#include "GraphicsManager.hpp"

TextInput::TextInput(float posX,
	                 float posY,
					 float width,
					 float height,
					 // Alignment is either left or center, determines whether position
					 // refers to the left-center position of the object or the center
					 Alignment alignment,
					 // isProtected denotes whether or not asterisks, e.g.
					 // ********, will be displayed in the place of text
					 bool isProtected)
    :boundingRect(sf::RectangleShape(sf::Vector2f(width, height))),
	 alignment(alignment),
	 isProtected(isProtected),
	 isSelected(false),
	 input(sf::Text("",
	                GraphicsManager::getInstance()->messageFont,
					GraphicsManager::getInstance()->messageSize))
{
	// Sets the color, origin, scale, and position of the boundingRect
	boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
	if (alignment == Alignment::LEFT)
		boundingRect.setOrigin(GraphicsManager::getInstance()->getLeftCenter(this->boundingRect));
	else if(alignment == Alignment::CENTER)
		boundingRect.setOrigin(GraphicsManager::getInstance()->getCenter(this->boundingRect));
	boundingRect.setScale(GraphicsManager::getInstance()->scale, GraphicsManager::getInstance()->scale);
	boundingRect.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize()) / 2.0f);
	boundingRect.move(posX * GraphicsManager::getInstance()->scale, posY * GraphicsManager::getInstance()->scale);

	input.setColor(GraphicsManager::getInstance()->typeColor);
	input.setString("Wq");
	input.setOrigin(GraphicsManager::getInstance()->getLeftCenter(input));
	input.setString("");
	if (alignment == Alignment::LEFT)
		input.setPosition(boundingRect.getPosition());
	if (alignment == Alignment::CENTER)
		input.setPosition(GraphicsManager::getInstance()->getLeftCenter(boundingRect));
	// We move a small distance away so that the letters aren't drawn directly 
	// on the boundingRect border
	input.move(5.0f * GraphicsManager::getInstance()->scale, 0.0f);
}

void TextInput::update()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(GraphicsManager::getInstance()->window);

	// Mouse clicks are checked to see whether or not if the TextInput is currently selected
	if(InputManager::getInstance()->mouseReleased)
	{
		if (boundingRect.getGlobalBounds().contains((float)mousePosition.x,
			                                        (float)mousePosition.y))
		{			
			isSelected = true;
			boundingRect.setFillColor(GraphicsManager::getInstance()->backgroundColor);
			input.setColor(GraphicsManager::getInstance()->selectColor);
		}
		else
		{
			isSelected = false;
			boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
			input.setColor(GraphicsManager::getInstance()->typeColor);
		}
	}

	// If this textbox is currently selected
	if (isSelected)
	{
		if (InputManager::getInstance()->backspace)
		{
			if(!input.getString().isEmpty())
			{
				sf::String deleted(input.getString());
				deleted.erase(deleted.getSize() - 1);
				input.setString(deleted);
			}
		}
		else if (!InputManager::getInstance()->input.isEmpty())
			input.setString(input.getString() + InputManager::getInstance()->input);
	}
	else if (boundingRect.getGlobalBounds().contains((float)mousePosition.x,
		                                             (float)mousePosition.y))
	{
		boundingRect.setFillColor(GraphicsManager::getInstance()->backgroundColor);
		input.setColor(GraphicsManager::getInstance()->selectColor);
	}
	else
	{
		boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
		input.setColor(GraphicsManager::getInstance()->typeColor);
	}
}

void TextInput::draw()
{
	GraphicsManager::getInstance()->window.draw(boundingRect);
	if (isProtected)
	{
		sf::String asterisks("");
		for (int i = 0; i < input.getString().getSize(); i++)
			asterisks += "*";
		sf::Text protectedInput(asterisks,
			                    *input.getFont(),
								input.getCharacterSize());
		protectedInput.setColor(input.getColor());
		protectedInput.setOrigin(GraphicsManager::getInstance()->getLeftCenter(protectedInput));
		protectedInput.setPosition(input.getPosition());
		GraphicsManager::getInstance()->window.draw(protectedInput);
	}
	else 
		GraphicsManager::getInstance()->window.draw(input);
}