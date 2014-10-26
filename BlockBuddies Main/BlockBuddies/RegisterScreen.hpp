#ifndef REGISTERSCREEN_HPP
#define REGISTERSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

class RegisterScreen : public Screen
{
public:
	RegisterScreen();
	void update();
	void draw();

	//Button LoginScreen;
	//Button HomeScreen;
};

#endif//REGISTERSCREEN_HPP