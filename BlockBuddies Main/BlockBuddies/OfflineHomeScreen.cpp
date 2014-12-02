#include "OfflineHomeScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "SoundManager.h"

OfflineHomeScreen::OfflineHomeScreen()
    :section(new Section(0.0f,
                         0.0f,
                         1000.0f,
                         600.0f)),

     welcome(new TextBox("Currently playing in offline mode",
                         0.0f,
                         0.0f,
                         300.0f)),

     offlineHome(new Button(Screens::OFFLINEHOME,
                            "Home",
                            -87.5f,
                            -225.0f,
                            150.0f,
                            50.0f)),

     offlineGameType(new Button(Screens::OFFLINEGAMETYPE,
                                "Play",
                                87.5f,
                                -225.0f,
                                150.0f,
                                50.0f))
{
    UIElements.push_back(section);
    UIElements.push_back(welcome);
    UIElements.push_back(offlineHome);
    UIElements.push_back(offlineGameType);

    selectables = { offlineHome,
                    offlineGameType };
}

void OfflineHomeScreen::update()
{
    Screen::update();

    if(offlineHome->isActivated ||
       (InputManager::getInstance()->enter && offlineHome->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(offlineHome->toScreen);
    }

    else if(offlineGameType->isActivated ||
            (InputManager::getInstance()->enter && offlineGameType->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(offlineGameType->toScreen);
    }
}

void OfflineHomeScreen::draw()
{
    Screen::draw();
}