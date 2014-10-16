#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "Screen.hpp"
#include "Button.hpp"

class ProfileScreen : public Screen
{
	ProfileScreen();
	~ProfileScreen();

	Button homeButton(Screen* toScreen);
	Button profileButton(Screen* toScreen);
	Button roomLobbyButton(Screen* toScreen);
};

#endif//PROFILE_HPP