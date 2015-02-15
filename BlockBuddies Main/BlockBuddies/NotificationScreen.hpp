#ifndef NOTIFICATIONSCREEN_HPP
#define NOTIFICATIONSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Section.hpp"

// Screen to login with account
class NotificationScreen : public Screen
{
public:
	NotificationScreen();

    void update();
	void draw();
    void reload();

	TextBox* status;

private:
    Section* backSection;
	// All the various parts we create
	Section* section;
	TextBox* title;

    Button* back;
};

#endif//NOTIFICATIONSCREEN_HPP