#include "Screen.hpp"
#include "InputManager.hpp"

// Updates selectables and UIElements
void Screen::update()
{
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
        a->update();
}

void Screen::draw()
{
    for(auto& a : UIElements)
        a->draw();
}

void Screen::deselect()
{
    for(auto selectable : selectables)
        selectable->isSelected = false;
}