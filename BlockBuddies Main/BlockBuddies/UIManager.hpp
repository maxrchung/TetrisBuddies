#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include "UIElement.hpp"
#include <vector>

class UIManager
{
public:
	static UIManager* getInstance();
	void init();
	void add(UIElement* element);
	void clear();
	void update();
	void draw();

	// Pointers because of polymorphism
	std::vector<UIElement*> UIElements;
private:	
	UIManager(){};
	UIManager(UIManager const&){};
	UIManager& operator=(UIManager const&){};

	static UIManager* instance;
};

#endif//UIMANAGER_HPP