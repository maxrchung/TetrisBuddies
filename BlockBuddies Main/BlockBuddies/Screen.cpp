#include "Screen.hpp"
#include "InputManager.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "ClientManager.h"
#include "TextInput.hpp"
#include "Section.hpp"
#include "RegisterScreen.hpp"
#include "LoginScreen.hpp"
#include "CloseScreen.hpp"
#include "AnimationManager.hpp"

Screen::Screen()
    :close(new Button(Screens::CLOSE,
                      "X",
                      (GraphicsManager::getInstance()->window.getSize().x / 2.0f) / GraphicsManager::getInstance()->scale - 25.0f,
                      -(GraphicsManager::getInstance()->window.getSize().y / 2.0f) / GraphicsManager::getInstance()->scale + 25.0f,
                      30.0f,
                      30.0f)),
     cursorArea(0.0f, 0.0f, 0.0f, 0.0f)
{
    fade = Fade();
    colorFade = Fade((int)(255 * 0.64f));
    close->fade.value = 255;
    close->fade.state = FadeStates::FADED_IN;
}

// Updates selectables and UIElements
void Screen::update()
{
    if (close->isActivated)
    {
		AnimationManager::getInstance()->pauseAnimation();
        close->isActivated = false;

        if(ClientManager::getInstance().isConnected)
        {
            ScreenManager::getInstance()->addScreen(close->toScreen);
        }
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
            if(!selectables.empty())
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    selectables[selectables.size() - 1]->isSelected = true;
                else
                    selectables[0]->isSelected = true;
            }
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
        if(a->isDisplayed && a->isUpdatable)
        {
            a->update();
        }
    }

    if(close->isDisplayed && close->isUpdatable)
    {
        close->update();
        sf::Vector2i mousePosition = sf::Mouse::getPosition(GraphicsManager::getInstance()->window);
        if (close->boundingRect.getGlobalBounds().contains((float)mousePosition.x,
            (float)mousePosition.y) ||
            close->isSelected)
        {
            close->boundingRect.setFillColor(GraphicsManager::getInstance()->sectionColor);
        }
    }
}

void Screen::draw()
{
    // For slightly bad reasons, we put the fade.update() here rather than in Screen::update()
    // because there are cases where we do not want to allow Screen::update() to run and only
    // draw the screen. The alternative would be to include some variable within Screen::update()
    // and only allow fade.update() to run if this variable is true. However, I feel this is
    // somewhat too complicated and can get unwieldy if we forget to change the a variable 
    // properly in another section.
    fade.update();
    colorFade.state = fade.state;
    colorFade.update();

    for(auto& UIElement : UIElements)
    {
        // Not sure if this is the best way to handle fade, but I think it'll suffice
        UIElement->fade = fade;
        UIElement->colorFade = colorFade;
        if(UIElement->isDisplayed) // Avoid drawing the close X in the corner
            UIElement->draw();
    }

    if(close->isDisplayed)
        close->draw();
}

// Does nothing since the basic screen does nothing
void Screen::reload()
{

}

// Deselects all the selectables
void Screen::deselect()
{
    for(auto selectable : selectables)
    {
        selectable->isSelected = false;
        selectable->selectFade.state = FadeStates::FADING_OUT;
    }
}

// Deactivates all the UIElements
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
                textInput->displayedInput.setString("");
                textInput->inputCursor.index = -1;
            }
        }
    }
}