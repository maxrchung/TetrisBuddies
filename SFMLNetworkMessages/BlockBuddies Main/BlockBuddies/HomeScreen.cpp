#include "HomeScreen.hpp"
#include "InputManager.hpp"

HomeScreen::HomeScreen()
	:buttons({ new Button(Screens::LOGIN,
	                      "Logout",
						  0.0f,
						  0.0f,
						  150.0f,
						  75.0f),

	           new Button(Screens::HOME,
			              "Home",
						  -175.0f,
						  -200.0f,
						  150.0f,
						  75.0f),

			   new Button(Screens::PROFILE,
		                  "Profile",
						  0.0f,
						  -200.0f,
						  150.0f,
						  75.0f),

	           new Button(Screens::GAMETYPE,
		                  "Play",
						  175.0f,
						  -200.0f,
						  150.0f,
						  75.0f) })
{
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