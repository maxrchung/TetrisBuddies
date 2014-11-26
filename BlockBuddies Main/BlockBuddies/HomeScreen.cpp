#include "HomeScreen.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"

HomeScreen::HomeScreen()
	:section(new Section(0.0f,
	                     0.0f,
						 1000.0f,
						 600.0f))
{
	// If the game is connected
	if(ClientManager::getInstance().isConnected)
	{
		welcome = new TextBox("Welcome to Block Buddies!",
	                          0.0f,
							  0.0f,
							  300.0f);

		buttons = { new Button(Screens::HOME,
			                   "Home",
							   -175.0f,
							   -225.0f,
							   150.0f,
							   50.0f),

					new Button(Screens::PROFILE,
		                       "Profile",
							   0.0f,
							   -225.0f,
							   150.0f,
							   50.0f),

					 new Button(Screens::GAMETYPE,
					            "Play",
								175.0f,
								-225.0f,
								150.0f,
								50.0f) };
	}

	else // if not connected
	{
		welcome = new TextBox("Currently playing in offline mode",
	                          0.0f,
							  0.0f,
							  300.0f);

		buttons = { new Button(Screens::HOME,
			                   "Home",
							   -87.5f,
							   -225.0f,
							   150.0f,
							   50.0f),

					 new Button(Screens::GAMETYPE,
					            "Play",
								87.5f,
								-225.0f,
								150.0f,
								50.0f) };

	}
}

void HomeScreen::update()
{
	for(auto i : buttons)
		if (i->isActivated ||
			(InputManager::getInstance()->enter && i->isSelected))
		{
			ScreenManager::getInstance()->switchScreen(i->toScreen);
			break;
		}
}

void HomeScreen::draw()
{

}