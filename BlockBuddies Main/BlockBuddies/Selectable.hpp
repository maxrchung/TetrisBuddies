#ifndef SELECTABLE_HPP
#define SELECTABLE_HPP

// Selectable is a class used for tabbing between buttons
// e.g. TextInput and Button are selectable objects, but
// a typical TextBox is not
class Selectable {
public:
	// Boolean indicating whether or not the element is
	// currently selected or not
	bool isSelected = false;
};

#endif//SELECTABLE_HPP