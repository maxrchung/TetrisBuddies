#ifndef LOGINSCREEN_HPP
#define LOGINSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

class LoginScreen: public Screen
{
public:
	LoginScreen();
	void update();
	void draw();

	Button registerButton;
	//Button homeButton;
};

#endif//LOGINSCREEN_HPP