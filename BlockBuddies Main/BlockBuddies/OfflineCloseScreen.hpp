#ifndef OFFLINECLOSESCREEN_HPP
#define OFFLINECLOSESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Section.hpp"

// Screen to login with account
class OfflineCloseScreen : public Screen
{
public:
	OfflineCloseScreen();

    void update();
	void draw();

private:
	// All the various parts we create
	Section* section;
	TextBox* title;
	TextBox* status;

	Button* login;
    Button* exit;
    Button* cancel;
};

#endif//OFFLINECLOSESCREEN_HPP