#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP

#include "UIElement.hpp"
#include <vector>

// Denotes how text should be aligned, by default most
// parameters should indicate CENTER, but there are cases
// where LEFT (to be more precise, Left-Center), are
// convenient
enum Alignments {LEFT, CENTER};

// The UIManager basically handles the update() and draw()
// of each UIElement. It holds a vector of the elements and
// runs through them each frame
class UIManager
{
public:
	static UIManager* getInstance();
	void init();
	void add(UIElement* element);
	void clear();
	void update();
	void draw();

private:
	// Pointers because of polymorphism
	std::vector<UIElement*> UIElements;

	UIManager(){};
	UIManager(UIManager const&){};
	UIManager& operator=(UIManager const&){};

	static UIManager* instance;
};

#endif//UIMANAGER_HPP