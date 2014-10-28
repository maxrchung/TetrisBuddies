#include "UIElement.hpp"
#include "UIManager.hpp"

UIElement::UIElement()
{
	// Add it onto the manager so that it can handle all the updates and draws
	UIManager::getInstance()->add(this);
}