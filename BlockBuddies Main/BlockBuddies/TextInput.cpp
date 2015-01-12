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
					 Alignments drawAlignment,
					 Alignments textAlignment,

					 // isProtected denotes whether or not asterisks, e.g.
					 // ********, will be displayed in the place of text
					 bool isProtected)
    :boundingRect(sf::RectangleShape(sf::Vector2f(width, height))),
	 drawAlignment(drawAlignment),
	 textAlignment(textAlignment),
	 isProtected(isProtected),
	 input(sf::Text("",
	                GraphicsManager::getInstance()->messageFont,
					GraphicsManager::getInstance()->messageSize))
{
	// Sets the color, origin, scale, and position of the boundingRect
	boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
	if (drawAlignment == Alignments::LEFT)
		boundingRect.setOrigin(GraphicsManager::getInstance()->getLeftCenter(this->boundingRect));
	else if(drawAlignment == Alignments::CENTER)
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
	if (textAlignment == Alignments::LEFT)
		input.setOrigin(GraphicsManager::getInstance()->getLeftCenter(input));
	else if(textAlignment == Alignments::CENTER)
		input.setOrigin(GraphicsManager::getInstance()->getCenter(input));

	// If Alignment is left, then we can just put the input where the boundingRect is
	if (textAlignment == Alignments::LEFT)
	{
		input.setPosition(boundingRect.getPosition());
		// We move a small distance away so that the letters aren't drawn directly
		// on the boundingRect border
		input.move(5.0f, 0.0f);
	}
	// Otherwise, we'll need to recalculate to find the left-center point of the boundingRect
	// The input as of now always comes reads in from the left of the box
	else if (textAlignment == Alignments::CENTER)
		input.setPosition(GraphicsManager::getInstance()->getCenter(boundingRect, Bounds::GLOBAL));

	// Sets the inputCursor in position
	inputCursor.boundingRect.setPosition(GraphicsManager::getInstance()->getRightCenter(input));

	// At the end, we reset the string
	input.setString("");

    displayedInput = input;

	// If it is protected, setup the protected asterisks input
	if (isProtected)
	{
        // We temporarily set the string as "*" so we can align
        // the origin properly in place
		protectedInput = sf::Text("*",
			                      *input.getFont(),
								  input.getCharacterSize());
		protectedInput.setColor(input.getColor());
		if (textAlignment == Alignments::LEFT)
			protectedInput.setOrigin(GraphicsManager::getInstance()->getLeftCenter(protectedInput));
		else if(textAlignment == Alignments::CENTER)
			protectedInput.setOrigin(GraphicsManager::getInstance()->getCenter(protectedInput));
		protectedInput.setPosition(input.getPosition());
		protectedInput.setString("");
        displayedInput = protectedInput;
	}
}

void TextInput::update()
{	
	// We declare the variable here because multiple parts below reference it
	sf::Vector2i mousePosition = sf::Mouse::getPosition(GraphicsManager::getInstance()->window);

	// If the mouse is hovering over the TextInput, then the color is highlighted but
    // the button is NOT selected
	if (boundingRect.getGlobalBounds().contains((float)mousePosition.x,
		                                        (float)mousePosition.y))
	{
		boundingRect.setFillColor(GraphicsManager::getInstance()->backgroundColor);
		input.setColor(GraphicsManager::getInstance()->selectColor);
	}

	// Mouse clicks are checked to see whether or not if the TextInput is selected
	if(InputManager::getInstance()->mouseReleased)
	{
		// If it is, the button is selected
		if (boundingRect.getGlobalBounds().contains((float)mousePosition.x,
			                                        (float)mousePosition.y))
			isSelected = true;

		// Otherwise, deselect the TextInput
		else
        {
			isSelected = false;

            // Also deselect all
            selectAll = false;
        }
	}

	// If this textbox is currently selected
	if (isSelected)
	{
		//  Only delete if the String is empty
		if (InputManager::getInstance()->backspace)
		{
            // Delete all if selected
            if (selectAll)
            {
                selectAll = false;
                inputCursor.index = -1;
                input.setString("");
            }

			// Make sure to put this in a separate if check
			// because backspace still counts as a character
			else if(!input.getString().isEmpty())
			{
                // Only delete according to index if it is not protected
				sf::String deleted(input.getString());
                if(isProtected)
                {
                    deleted.erase(input.getString().getSize() - 1);
                }
                else
                {
                    // Don't do anything if we're at the -1 index
                    if (inputCursor.index == -1)
                        return;
                    deleted.erase(inputCursor.index);
                }

				input.setString(deleted);

                // Move the cursor backwards
                // Make sure this goes after all our calculations above
                inputCursor.index--;
			}
		}

        else if(InputManager::getInstance()->del)
        {
            // Delete all if selected
            if (selectAll)
            {
                selectAll = false;
                inputCursor.index = -1;
                input.setString("");
            }

            // Don't delete from empty inputs
            else if (!input.getString().isEmpty())
            {
                // Only non-protected inputs will be delete a character forward
                if (!isProtected)
                {
                    // If the cursor index is not at the last character in the input
                    // then we know we can delete the character afterwards
                    if(inputCursor.index + 1 < (int)input.getString().getSize())
                    {
                        sf::String deleted = input.getString();
                        deleted.erase(inputCursor.index + 1);
                        input.setString(deleted);

                        if (selectAll)
                        {
                            selectAll = false;
                            inputCursor.index = -1;
                            input.setString("");
                        }
                    }
                }
            }
        }

        // If ctrl+A is pressed, select all the text
        else if(InputManager::getInstance()->a && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
        {
            // Only select if there's actual input
            if((int) input.getString().getSize() > 0)
                selectAll = true;
        }

        // We can deselect all with escape
        else if(InputManager::getInstance()->escape)
        {
            selectAll = false;
        }

		// Add in the input text from the InputManager
		else if (!InputManager::getInstance()->input.isEmpty())
		{
            // Delete all but the given input if selected
            if (selectAll)
            {
                selectAll = false;
                inputCursor.index = 0;
                input.setString(InputManager::getInstance()->input);
            }

            else
            {
                // Don't add a letter if the input is over some limit
                if ((int)input.getString().getSize() > 30)
                    return;
            
                if (isProtected)
                {
                    input.setString(input.getString() + InputManager::getInstance()->input);
                }
                else
                {
                    sf::String addedInput = input.getString();
                    addedInput.insert(inputCursor.index + 1, InputManager::getInstance()->input);
                    input.setString(addedInput);
                    inputCursor.index++;
                }
            }
		}

        // This block handles the inputCursor scrolling and positioning
        if(!isProtected)
        {
            if(InputManager::getInstance()->left)
            {
                if(inputCursor.index > -1)
                    inputCursor.index--;

                // Turn off select if the cursor moves
                selectAll = false;
            }
            else if(InputManager::getInstance()->right)
            {
                // Make sure you have (int) casting because getSize() returns a std::size_t
                if(inputCursor.index < (int) input.getString().getSize() - 1)
                    inputCursor.index++;
                selectAll = false;
            }
            else if(InputManager::getInstance()->down || InputManager::getInstance()->end)
            {
                inputCursor.index = input.getString().getSize() - 1;
                selectAll = false;
            }
            // The -1 index puts it before the first index
            else if(InputManager::getInstance()->up || InputManager::getInstance()->home)
            {
                inputCursor.index = -1;
                selectAll = false;
            }

            float cursorLocation = 0.0f;
            if (inputCursor.index == -1)
                cursorLocation = GraphicsManager::getInstance()->getLeftCenter(input, Bounds::GLOBAL).x;
            else
            {
                // We use textMeasure to see how far we need to go for the cursor
                sf::Text textMeasure = input;
                textMeasure.setString(input.getString().substring(0, inputCursor.index + 1));
                    
                cursorLocation = GraphicsManager::getInstance()->getRightCenter(textMeasure, Bounds::GLOBAL).x;
            }

            inputCursor.boundingRect.setPosition(cursorLocation,
                                                 input.getPosition().y);

            displayedInput = input;

            // If the inputCursor goes past the boundingRect, then we loop backwards to find the correct
            // text that should fit within it
            // If greater than the right hand side
            if(inputCursor.boundingRect.getPosition().x > boundingRect.getGlobalBounds().left 
                                                              + boundingRect.getGlobalBounds().width - 5.0f)
            {
                sf::Text checkLength = input;
                sf::String inputString = input.getString();
                int inputIndex = inputCursor.index;
                sf::String grow;
                if(inputIndex > -1)
                    grow = inputString[inputIndex];
                checkLength.setString(grow);
                while(checkLength.getLocalBounds().width < boundingRect.getLocalBounds().width - 10.0f)
                {
                    // We set this here because the while statement checks if the NEXT character
                    // addition will exceed the length
                    displayedInput = checkLength;

                    // Make sure we don't have any negative indicies
                    if(--inputIndex <= 0)
                        break;

                    // Insert a new character in front
                    grow.insert(0, inputString[inputIndex]);
                    checkLength.setString(grow);
                }

                displayedInput.setOrigin(GraphicsManager::getInstance()->getRightCenter(displayedInput, Bounds::LOCAL).x,
                                         input.getOrigin().y);
                displayedInput.setPosition(boundingRect.getGlobalBounds().left + boundingRect.getGlobalBounds().width - 5.0f,
                                           input.getPosition().y);
                inputCursor.boundingRect.setPosition(displayedInput.getPosition().x,
                                                     input.getPosition().y);
            }
            // If the inputCursor is in the middle, we still have to check if the right hand text
            // goes past the boundingRect
            else if(input.getLocalBounds().width + 10.0f > boundingRect.getLocalBounds().width)
            {
                sf::Text checkLength = input;
                sf::String inputString = input.getString();
                sf::String grow = sf::String("");
                for(int inputIndex = 0; inputIndex < (int)inputString.getSize(); inputIndex++)
                {
                    grow += inputString[inputIndex];
                    checkLength.setString(grow);

                    if (checkLength.getLocalBounds().width < boundingRect.getLocalBounds().width - 10.0f)
                        displayedInput = checkLength;
                }
            }
        }

        else // if isProtected
        {
            // This sets the input cursor onto protected input
            inputCursor.boundingRect.setPosition(GraphicsManager::getInstance()->getRightCenter(protectedInput, Bounds::GLOBAL).x
				                                     + 1.0f * GraphicsManager::getInstance()->scale,
                                                 input.getPosition().y);

            // If it's protected, then we make sure that we loop through all the characters
            // and save them as asterisks to protectedInput
            sf::String asterisks("");
            for (int i = 0; i < input.getString().getSize(); i++)
                asterisks += "*";
            protectedInput.setString(asterisks);

            protectedInput.setColor(input.getColor());
            protectedInput.setPosition(input.getPosition());
            // Also set the origin so that it can draw from the middle if necessary
            if (textAlignment == Alignments::LEFT)
                protectedInput.setOrigin(GraphicsManager::getInstance()->getLeftCenter(protectedInput));
            else if (textAlignment == Alignments::CENTER)
                protectedInput.setOrigin(GraphicsManager::getInstance()->getCenter(protectedInput));

            displayedInput = protectedInput;
        }

		// Set the colors if it is selected
		boundingRect.setFillColor(GraphicsManager::getInstance()->backgroundColor);
		displayedInput.setColor(GraphicsManager::getInstance()->selectColor);

        // This block handles inputCursor blinking
		// If the cursor timer is greater than some constant
		if(inputCursor.blinkTimer.getElapsedTime().asMilliseconds() > 500)
		{
			// Check if it is currently displayed, if it is, set it to false, otherwise set it to true
			inputCursor.isDisplayed ? inputCursor.isDisplayed = false : inputCursor.isDisplayed = true;

			// Restart the timer
			inputCursor.blinkTimer.restart();
		}
	}

	// Else set the colors if it is not selected
	else // if !isSelected
	{
		boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
		displayedInput.setColor(GraphicsManager::getInstance()->typeColor);

		// If the box is not selected, do not display the cursor
		inputCursor.isDisplayed = false;
	}
}

void TextInput::draw()
{
	// Draw the background boundingRect
	GraphicsManager::getInstance()->window.draw(boundingRect);
    
    // Highlight all the text if we are selecting all
    if(selectAll)
    {
        sf::RectangleShape selectAll = sf::RectangleShape(sf::Vector2f(displayedInput.getLocalBounds().width,
                                                                       inputCursor.boundingRect.getLocalBounds().height));
        selectAll.setFillColor(GraphicsManager::getInstance()->sectionColor);
        selectAll.setOrigin(displayedInput.getOrigin().x,
                            inputCursor.boundingRect.getOrigin().y);
        selectAll.setPosition(displayedInput.getPosition().x,
                              inputCursor.boundingRect.getPosition().y);
        GraphicsManager::getInstance()->window.draw(selectAll);

        GraphicsManager::getInstance()->window.draw(displayedInput);
    }
    else
    {
        GraphicsManager::getInstance()->window.draw(displayedInput);
        inputCursor.draw();
    }
}

// Private InputCursor class for TextInput
TextInput::InputCursor::InputCursor()
     // Rectangle indicator for the cursor
    :boundingRect(sf::RectangleShape(sf::Vector2f(2.0f,
	                                              20.0f)))
{
	// We set some values for the boundingRect
	InputCursor::boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
	InputCursor::boundingRect.setScale(GraphicsManager::getInstance()->scale,
		                               GraphicsManager::getInstance()->scale);
	InputCursor::boundingRect.setOrigin(GraphicsManager::getInstance()->getLeftCenter(InputCursor::boundingRect));
}

void TextInput::InputCursor::update()
{
	// Nothing in here since the outside TextInput update() function
	// will handle updating the InputCursor's location and blinking
}

void TextInput::InputCursor::draw()
{
	if (InputCursor::isDisplayed)
		GraphicsManager::getInstance()->window.draw(InputCursor::boundingRect);
}