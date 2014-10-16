#ifndef ROOMLOBBYSCREEN_HPP
#define ROOMLOBBYSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

class RoomLobbyScreen : public Screen
{
	RoomLobbyScreen();
	~RoomLobbyScreen();

	Button HomeButton(Screen* toScreen);
	Button ProfileButton(Screen* toScreen);
	Button RoomLobbyButton(Screen* toScreen);
};

#endif//ROOMLOBBYSCREEN_HPP