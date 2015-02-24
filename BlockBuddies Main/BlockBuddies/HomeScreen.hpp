#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "Section.hpp"
#include "TextBox.hpp"

// Screen you get into when you first login or register an account
// Basically the central hub to take you to other parts
class HomeScreen: public Screen
{
public:
	HomeScreen();
	void update();
	void draw();
    void reload();

private:
    Section* backSection;
	Section* section;
    TextBox* title;
	TextBox* welcome;
    Button* networkedSinglePlayer;
	Button* multiplayer;
	Button* profile;
    Button* instruction;
    Button* logout;
};

#endif//HOMESCREEN_HPP