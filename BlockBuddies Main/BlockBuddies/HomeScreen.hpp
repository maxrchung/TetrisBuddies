#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

class HomeScreen: public Screen
{
public:
	HomeScreen();
	void update();

	std::vector<Button*> buttons;
};

#endif//HOMESCREEN_HPP