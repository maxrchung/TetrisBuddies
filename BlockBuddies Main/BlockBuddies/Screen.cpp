#include "Screen.hpp"
#include "InputManager.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "ClientManager.h"
#include "TextInput.hpp"

Screen::Screen()
    :close(new Button(Screens::CLOSE,
                      "X",
                      (GraphicsManager::getInstance()->window.getSize().x / 2.0f) / GraphicsManager::getInstance()->scale - 20.0f,
                      -(GraphicsManager::getInstance()->window.getSize().y / 2.0f) / GraphicsManager::getInstance()->scale + 20.0f,
                      30.0f,
                      30.0f))
{
    UIElements.push_back(close);
}

// Updates selectables and UIElements
void Screen::update()
{
    if (close->isActivated)
    {
        close->isActivated = false;
        if(ClientManager::getInstance().isConnected)
            ScreenManager::getInstance()->addScreen(close->toScreen);
        else
            ScreenManager::getInstance()->addScreen(Screens::OFFLINECLOSE);
    }

    // If the player hits tab, it iterates forward in our Selectable vector
	if (InputManager::getInstance()->tab)
	{
		// This is to check if any Selectable element is currently selected
		// The for loop below will loop through the entire vector, so if none
		// of these elements have isSelected == true, then selected will
		// remain false
		bool selected = false;

		// If the player holds shift and hits tab, it iterates backwards
		for (int i = 0; i < selectables.size(); i++)
		{
			if (selectables[i]->isSelected)
			{
				selected = true;
				selectables[i]->isSelected = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					// We check i > 0 to avoid edge case problems, or else you'll run
					// into some errors accessing things that don't exist
					if (i > 0)
						selectables[i - 1]->isSelected = true;
					break;
				}
				else
				{
					// We also check i < selectables.size() - 1 for edge case problems
					if (i < selectables.size() - 1)
						selectables[i + 1]->isSelected = true;
					break;
				}
			}
		}

		// If nothing is selected then we set either the first or the last
		// element as selected, depending on whether we do tab or shift-tab
		if (!selected)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				selectables[selectables.size() - 1]->isSelected = true;
			else
				selectables[0]->isSelected = true;
		}
	}

	// If we mouse click, we deselect everything and let the individual 
	// UIElements handle mouseReleased events
	if(InputManager::getInstance()->mouseReleased)
		for (auto& i : selectables)
			i->isSelected = false;

    // Updates all the UIelements
    for(auto& a : UIElements)
    {
        if(a->isDisplayed)
            a->update();
    }
}

void Screen::draw()
{
    for(auto& a : UIElements)
    {
        if(a->isDisplayed)
            a->draw();
    }
}

void Screen::deselect()
{
    for(auto selectable : selectables)
        selectable->isSelected = false;
}

void Screen::deactivate()
{
    for(auto& UIElement : UIElements)
    {
        Button* button = dynamic_cast<Button*>(UIElement);
        if(button)
        {
            button->isActivated = false;
            button->boundingRect.setFillColor(GraphicsManager::getInstance()->buttonColor);
            button->label.setColor(GraphicsManager::getInstance()->backgroundColor);
        }

        else
        {
            TextInput* textInput = dynamic_cast<TextInput*>(UIElement);
            if (textInput)
            {
                textInput->input.setString("");
                textInput->protectedInput.setString("");
            }
        }

    }
}