#include "UIManager.hpp"

UIManager* UIManager::instance;

UIManager* UIManager::getInstance()
{
	if (!instance)
		instance = new UIManager;
	return instance;
}

void UIManager::init()
{
	UIElements = std::vector<UIElement*>();
}

void UIManager::add(UIElement* element)
{
	UIElements.push_back(element);
}

void UIManager::clear()
{
	// I'm not 100% sure if this works as intended since I'm not
	// too familiar with free(), but delete from what I've read
	// in a forward incrementing loop is inefficient since the
	// destructor is called for each element, which is bad for a vector 
	// since it'll push all the back elements forward. Thus, freeing the 
	// elements and then clearing the vector should be a bit more efficient
	for(auto i : UIElements)
		free(i);
	UIElements.clear();
}

void UIManager::update()
{
	// Because when we switch screens we may do some crazy shenanigans
	// deleting parts of a vector while iterating through the middle of 
	// said vector, we have to use this indexing format to avoid iterator 
	// incrementation errors
	for (int i = 0; i < UIElements.size(); i++)
		UIElements[i]->update();
}

void UIManager::draw()
{
	for (auto i : UIElements)
		i->draw();
}