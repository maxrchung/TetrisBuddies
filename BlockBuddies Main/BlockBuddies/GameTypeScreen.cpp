#include "GameTypeScreen.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"

GameTypeScreen::GameTypeScreen()
	:section(new Section(0.0f,
	                     0.0f,
						 1000.0f,
						 600.0f))
{
	if (ClientManager::getInstance().isConnected)
	{
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
								50.0f),

	                 new Button(Screens::GAME,
                                "Start Game",	 
								0.0f,
								0.0f,
								150.0f,
								50.0f) };
	}

	else // if not connected
	{
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
							   50.0f),

	                 new Button(Screens::GAME,
                                "Start Game",	 
								0.0f,
								0.0f,
								150.0f,
								50.0f) };
	}
}

void GameTypeScreen::update()
{
	for(auto i : buttons)
		if (i->isActivated ||
			(InputManager::getInstance()->enter && i->isSelected))
		{
			ScreenManager::getInstance()->switchScreen(i->toScreen);
			break;
		}
}

void GameTypeScreen::draw()
{

}