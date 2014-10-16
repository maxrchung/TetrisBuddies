#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

class HomeScreen : public Screen
{
public:
	HomeScreen();
	~HomeScreen();

	Button homeButton(Screen* toScreen);
	Button profileButton(Screen* toScreen);
	Button roomLobbyButton(Screen* toScreen);
};

#endif//HOMESCREEN_HPP