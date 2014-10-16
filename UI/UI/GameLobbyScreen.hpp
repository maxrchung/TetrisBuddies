#ifndef GAMELOBBYSCREEN_HPP
#define GAMELOBBYSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

class GameLobbyScreen : public Screen
{
	GameLobbyScreen();
	~GameLobbyScreen();

	Button roomLobbyButton(Screen* toScreen);
	Button gameButton(Screen* toScreen);
};

#endif GAMELOBBYSCREEN_HPP