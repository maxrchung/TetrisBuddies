#include "TextInput.hpp"
#include "InputManager.hpp"
#include "GraphicsManager.hpp"

#include <iostream>

TextInput::TextInput(float posX,
	                 float posY,
					 float width,
					 float height,

					 // Alignment is either left or center, determines whether position
					 // refers to the left-center position of the object or the center
					 Alignments alignment,

					 // isProtected denotes whether or not asterisks, e.g.
					 // ********, will be displayed in the place of text
					 bool isProtected)
    :boundingRect(sf::RectangleShape(sf::Vector2f(width, height))),
	 alignment(alignment),
	 isProtected(isProtected),
	 input(sf::Text("",
	                GraphicsManager::getInstance()->messageFont,
					GraphicsManager::getInstance()->messageSize))
{
	// Sets the color, origin, scale, and position of the boundingRect
	boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
	if (alignment == Alignments::LEFT)
		boundingRect.setOrigin(GraphicsManager::getInstance()->getLeftCenter(this->boundingRect));
	else if(alignment == Alignments::CENTER)
		boundingRect.setOrigin(GraphicsManager::getInstance()->getCenter(this->boundingRect));
	boundingRect.setScale(GraphicsManager::getInstance()->scale, GraphicsManager::getInstance()->scale);
	boundingRect.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize()) / 2.0f);
	boundingRect.move(posX * GraphicsManager::getInstance()->scale, posY * GraphicsManager::getInstance()->scale);

	// Sets the color of the input text
	input.setColor(GraphicsManager::getInstance()->typeColor);

	// This chunk of code sets the origin of "Wq", the highest and lowest characters
	// I believe. This is here so that we don't have to recalculate the origin each time
	// a character is added into input and see shifting around
	input.setString("Wq");
	// Depending on the alignment, we either set the origin to the leftCenter
	// or the center of the input
	if (alignment == Alignments::LEFT)
		input.setOrigin(GraphicsManager::getInstance()->getLeftCenter(input));
	else if(alignment == Alignments::CENTER)
		input.setOrigin(GraphicsManager::getInstance()->getCenter(input));
	// At the end, we reset the string
	input.setString("");

	// If Alignment is left, then we can just put the input where the boundingRect is
	if (alignment == Alignments::LEFT)
		input.setPosition(boundingRect.getPosition());
	// Otherwise, we'll need to recalculate to find the left-center point of the boundingRect
	// The input as of now always comes reads in from the left of the box
	else if (alignment == Alignments::CENTER)
		input.setPosition(GraphicsManager::getInstance()->getCenter(boundingRect));

	// We move a small distance away so that the letters aren't drawn directly 
	// on the boundingRect border
	input.move(5.0f * GraphicsManager::getInstance()->scale, 0.0f);
}

void TextInput::update()
{	
	// We declare the variable here because multiple parts below reference it
	sf::Vector2i mousePosition = sf::Mouse::getPosition(GraphicsManager::getInstance()->window);

	// Mouse clicks are checked to see whether or not if the TextInput is currently selected
	if(InputManager::getInstance()->mouseReleased)
	{
		// If it is, the button is selected
		if (boundingRect.getGlobalBounds().contains((float)mousePosition.x,
			                                        (float)mousePosition.y))
			isSelected = true;

		// Otherwise, deselect the TextInput
		else
			isSelected = false;
	}

	// If this textbox is currently selected
	if (isSelected)
	{
		//  Only delete if the String is empty
		if (InputManager::getInstance()->backspace)
		{
			// Make sure to put this inside of the outer if loop
			// Because backspace still counts as a character
			if(!input.getString().isEmpty())
			{
				sf::String deleted(input.getString());
				deleted.erase(deleted.getSize() - 1);
				input.setString(deleted);
			}
		}

		// Add in the input text from the InputManager
		else if (!InputManager::getInstance()->input.isEmpty())
		{
			input.setString(input.getString() + InputManager::getInstance()->input);

			// If we are aligning it by the center, then we have to readjust the origin
			// and position so that it redraws from the center of the textbox each time
			// Left alignment is always set from the leftmost area, so we don't have to
			// worry about that
			if (alignment == Alignments::CENTER)
			{
				input.setOrigin(GraphicsManager::getInstance()->getCenter(input).x,
					            input.getOrigin().y);
				input.setPosition(boundingRect.getPosition());
			}
		}

		// Set the colors if it is selected
		boundingRect.setFillColor(GraphicsManager::getInstance()->backgroundColor);
		input.setColor(GraphicsManager::getInstance()->selectColor);
	}

	// Else set the colors if it is not selected
	else
	{
		boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
		input.setColor(GraphicsManager::getInstance()->typeColor);
	}

	// If the mouse is hovering over the TextInput, then it is selected
	if (boundingRect.getGlobalBounds().contains((float)mousePosition.x,
		                                        (float)mousePosition.y))
	{
		boundingRect.setFillColor(GraphicsManager::getInstance()->backgroundColor);
		input.setColor(GraphicsManager::getInstance()->selectColor);
	}
}

void TextInput::draw()
{
	GraphicsManager::getInstance()->window.draw(boundingRect);

	// If the TextInput is password protected, then create a new
	// asterisks Text to draw. Ideally, for efficiency, we may want
	// to move this into update() and make variables outside in the
	// class, but this small chunk of code nicely constrains everything
	// to this single area
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