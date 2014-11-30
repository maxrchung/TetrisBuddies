#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

// Denotes whether the UIElement is drawn with the Left-Center
// or the Center as the origin point
enum Alignments
{
    LEFT,
    CENTER
};

// Basically, anything you want to display on the screen
// (at least for UI anyways), should be inherited from
// this class. Buttons, textboxes, etc.
class UIElement
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;

    // Determines whether to display the element or not
    bool isDisplayed = true;
};

#endif//UIELEMENT_HPP