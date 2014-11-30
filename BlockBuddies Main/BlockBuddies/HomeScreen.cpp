#include "HomeScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"

HomeScreen::HomeScreen()
    :section(new Section(0.0f,
                         0.0f,
                         1000.0f,
                         600.0f)),

     welcome(new TextBox("Welcome to Block Buddies!",
                         0.0f,
                         0.0f,
                         300.0f)),

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
    UIElements.push_back(section);
    UIElements.push_back(welcome);
    UIElements.push_back(home);
    UIElements.push_back(profile);
    UIElements.push_back(gameType);

    selectables = { home,
                    profile,
                    gameType };
}

void HomeScreen::update()
{
    // Calls base update()
    Screen::update();

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
            ScreenManager::getInstance()->switchScreen(home->toScreen);
    
    else if (profile->isActivated ||
             (InputManager::getInstance()->enter && profile->isSelected))
                 ScreenManager::getInstance()->switchScreen(profile->toScreen);
        
    else if (gameType->isActivated ||
             (InputManager::getInstance()->enter && gameType->isSelected))
                 ScreenManager::getInstance()->switchScreen(gameType->toScreen);
}

void HomeScreen::draw()
{
    // Calls base draw()
    Screen::draw();
}