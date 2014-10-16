#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Screen.hpp"

class Button 
{
public:
	Button();
	Button(Screen* toScreen);
	~Button();

	void draw();

	Screen* toScreen;
};

#endif BUTTON_HPP