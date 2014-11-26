#include "ProfileScreen.hpp"
#include "InputManager.hpp"

ProfileScreen::ProfileScreen()
	:section(new Section(0.0f,
	                     0.0f,
						 1000.0f,
						 600.0f)),

	 buttons({ new Button(Screens::HOME,
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
						  50.0f) })
{
}

void ProfileScreen::update()
{
	for(auto i : buttons)
		if (i->isActivated ||
			(InputManager::getInstance()->enter && i->isSelected))
		{
			ScreenManager::getInstance()->switchScreen(i->toScreen);
			break;
		}
}

void ProfileScreen::draw()
{

}