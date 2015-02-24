#ifndef CLOSESCREEN_HPP
#define CLOSESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Section.hpp"

// Screen to login with account
class CloseScreen : public Screen
{
public:
	CloseScreen();

    void update();
	void draw();
    void reload();

	Button* login;

private:
    Section* backSection;
	// All the various parts we create
	Section* section;
	TextBox* title;
	TextBox* status;

    Button* home;
    Button* exit;
    Button* cancel;
};

#endif//CLOSESCREEN_HPP