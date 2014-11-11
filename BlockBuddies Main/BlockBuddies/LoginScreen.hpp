#ifndef LOGINSCREEN_HPP
#define LOGINSCREEN_HPP

#include "Screen.hpp"
#include <vector>
#include "Button.hpp"
#include "TextBox.hpp"
#include "TextInput.hpp"
#include "Section.hpp"
#include "Selectable.hpp"

// Screen to login with account
class LoginScreen : public Screen
{
public:
	LoginScreen();

	// Use the update() function to handle larger picture
	// actions that require multiple parts of this screen
	// i.e. sending a message to check username/pass to the
	// server
	// For smaller things, like adding a particle effect on
	// a button, that's probably better left handled in the
	// Button's update() and draw()
	void update();

	void draw();

	// All the various parts we create
	Section* section;
	TextBox* title;
	TextBox* status;

	// Note that the Tag indicates a descriptor, as in the "Username:"
	// tag that appears on the left of the TextInput
	TextBox* usernameTag;
	TextBox* passwordTag;
	TextInput* username;
	TextInput* password;
	std::vector<Button*> buttons;
};

#endif//LOGINSCREEN_HPP