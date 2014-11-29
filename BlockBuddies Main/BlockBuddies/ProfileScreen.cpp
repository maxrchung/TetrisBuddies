#include "ProfileScreen.hpp"
#include "InputManager.hpp"

ProfileScreen::ProfileScreen()
	:section(new Section(0.0f,
	                     0.0f,
						 1000.0f,
						 600.0f)),

	 home(new Button(Screens::HOME,
                     "Home",
                     -175.0f,
                     -225.0f,
                     150.0f,
                     50.0f)),

     profile(new Button(Screens::PROFILE,
                        "Profile",
                        0.0f,
                        -225.0f,
                        150.0f,
                        50.0f)),

     gameType(new Button(Screens::GAMETYPE,
    		             "Play",
                         175.0f,
                         -225.0f,
                         150.0f,
                         50.0f))
{
    UIElements = { section,
                   home,
                   profile,
                   gameType };

    selectables = { home,
                    profile,
                    gameType };
}

void ProfileScreen::update()
{
    Screen::update();

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }

    else if (profile->isActivated ||
             (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }

    else if (gameType->isActivated ||
             (InputManager::getInstance()->enter && gameType->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(gameType->toScreen);
    }
}

void ProfileScreen::draw()
{
    Screen::draw();
}