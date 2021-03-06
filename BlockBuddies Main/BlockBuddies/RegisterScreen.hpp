#ifndef REGISTERSCREEN_HPP
#define REGISTERSCREEN_HPP

#include "Screen.hpp"
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
	void draw();

private:
    Section* backSection;
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

    Button* login;
    Button* home;
};

#endif//REGISTERSCREEN_HPP