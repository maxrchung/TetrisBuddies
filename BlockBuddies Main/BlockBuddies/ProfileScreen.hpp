#ifndef PROFILESCREEN_HPP
#define PROFILESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

class ProfileScreen: public Screen
{
public:
	ProfileScreen();
	void update();

	std::vector<Button*> buttons;
};

#endif//PROFILESCREEN_HPP