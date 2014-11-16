#include "TextBox.hpp"
#include "GraphicsManager.hpp"

TextBox::TextBox(char* message,
                 float posX,
				 float posY,
				 float width,
				 Alignments textAlignment,
				 bool isTitle)
    :message(sf::Text(message,
                      GraphicsManager::getInstance()->messageFont,
					  GraphicsManager::getInstance()->messageSize)),
	 boundingWidth(width)
{
	// The isTitle parameter indicates whether or not the textbox is a larger title
	// e.g. "Login" for the LoginScreen, or just a normal instructions e.g. "Enter credentials below"
	// Right now, they are only differentiated by two different font sizes
	// If we would like, we could change the parameter to accept a font size, or
	// change the font of either within GraphicsManager
	if (isTitle)
		this->message.setCharacterSize(GraphicsManager::getInstance()->titleSize);

	textWrap();

	// Sets the message color of the TextBox
	this->message.setColor(GraphicsManager::getInstance()->typeColor);

	// Determines whether it is drawn based on the TextBox's left-center or by the center
	if (textAlignment == Alignments::LEFT)
		this->message.setOrigin(GraphicsManager::getInstance()->getLeftCenter(this->message));
	else if (textAlignment == Alignments::CENTER)
		this->message.setOrigin(GraphicsManager::getInstance()->getCenter(this->message));

	// Sets the message position, by first going to the center of the screen and then moving 
	// a scaled distance away
	this->message.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize())/2.0f);
    this->message.move(posX * GraphicsManager::getInstance()->scale, posY * GraphicsManager::getInstance()->scale);
}

// Snippet of code for dealing with text wraps
void TextBox::textWrap()
{
	// Lol. If a "\n" doesn't exist in the text, then you know you are
	// allowed to do textWrapping
	if (message.getString().find("\n") == sf::String::InvalidPos)
	{
		// If the text is greater than the given boundingWidth
		if (this->message.getLocalBounds().width > boundingWidth)
		{
			// We make a variable that will check from the first letter of message
			// until a letter that goes over the boundingWidth
			sf::Text checkBound(sf::Text("",
				                GraphicsManager::getInstance()->messageFont,
								GraphicsManager::getInstance()->messageSize));

			for (int i = 0; i < this->message.getString().getSize(); i++)
			{
				// Add in each letter of the message
				checkBound.setString(checkBound.getString() + this->message.getString()[i]);
				
				// If the check goes over the width
				if (checkBound.getLocalBounds().width > boundingWidth)
				{
					// Loop backwards from the end of the check
					for (int j = i; j >= 0; j--)
					{
						// Until you find a space
						if (this->message.getString()[j] == sf::String(" "))
						{
							// Then reset the normal message with a return character at that point
							sf::String checkReturn(this->message.getString());
							checkReturn.insert(j + 1, "\n"); // +1 to go after the designated point
							this->message.setString(checkReturn);
							checkBound.setString("");
							i++; // Add 1 to i so we don't reread the same letter we had before
							break;
						}
					}
				}
			}
		}
	}
}

void TextBox::update()
{
	// Check each loop if the message needs to be wrapped
	// This is needed in cases where, for example, the status is updated
	// and needs to be rewrapped again
	textWrap();
}

void TextBox::draw()
{
	GraphicsManager::getInstance()->window.draw(message);
}

void TextBox::setString(std::string newMessage)
{
	message.setString(newMessage);
}