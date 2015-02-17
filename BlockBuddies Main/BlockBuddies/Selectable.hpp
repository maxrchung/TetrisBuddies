#ifndef SELECTABLE_HPP
#define SELECTABLE_HPP

#include "Fade.hpp"

// Selectable is a class used for tabbing between buttons
// e.g. TextInput and Button are selectable objects, but
// a typical TextBox is not
class Selectable {
public:
    Selectable();

	// Boolean indicating whether or not the element is
	// currently selected or not
	bool isSelected = false;

    // Determines whether to draw the select outline
    // We want this set to false for the close button
    bool drawSelector = true;

    Fade selectFade; // Border around any selected/hovered over elements
};

#endif//SELECTABLE_HPP