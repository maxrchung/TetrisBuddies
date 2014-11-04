#include "HomeScreen.hpp"
#include "ProfileScreen.hpp"
#include "GameTypeScreen.hpp"

ProfileScreen::ProfileScreen()
	:buttons({ new Button(Screens::HOME,
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

void ProfileScreen::update()
{
	for(auto i : buttons)
		if (i->isActivated)
		{
			ScreenManager::getInstance()->switchScreen(i->toScreen);
			break;
		}
}