#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

// Screen you get into when you first login or register an account
// Basically the central hub to take you to other parts
class HomeScreen: public Screen
{
public:
	HomeScreen();
	void update();

	std::vector<Button*> buttons;
};

#endif//HOMESCREEN_HPP