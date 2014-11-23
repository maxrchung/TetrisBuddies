#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

// Basically, anything you want to display on the screen
// (at least for menus anyways), should be inherited from
// this class. Buttons, textboxes, etc. will all be automatically
// placed into the UIManager and will update/draw from there
class UIElement
{
public:
	UIElement();
	virtual void update() = 0;
	virtual void draw() = 0;
};

#endif//UIELEMENT_HPP