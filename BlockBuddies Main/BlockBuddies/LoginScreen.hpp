#ifndef LOGINSCREEN_HPP
#define LOGINSCREEN_HPP

#include "Screen.hpp"
#include <vector>
#include "Button.hpp"
#include "TextBox.hpp"
#include "TextInput.hpp"
#include "Section.hpp"

class LoginScreen: public Screen
{
public:
	LoginScreen();
	void update();

	Section* section;
	TextBox* title;
	TextBox* status;
	TextBox* usernameTag;
	TextBox* passwordTag;
	TextInput* username;
	TextInput* password;
	std::vector<Button*> buttons;
};

#endif//LOGINSCREEN_HPP