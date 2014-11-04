#ifndef REGISTERSCREEN_HPP
#define REGISTERSCREEN_HPP

#include "Screen.hpp"
#include <vector>
#include "Button.hpp"
#include "TextBox.hpp"
#include "TextInput.hpp"
#include "Section.hpp"

// Register an account on this screen
class RegisterScreen : public Screen
{
public:
	RegisterScreen();
	void update();

	Section* section;
	TextBox* title;
	TextBox* status;
	TextBox* status2;
	TextBox* usernameTag;
	TextBox* passwordTag;

	// We have two password inputs for verification	
	TextBox* password2Tag;

	TextInput* username;
	TextInput* password;
	TextInput* password2;
	std::vector<Button*> buttons;
};

#endif//REGISTERSCREEN_HPP