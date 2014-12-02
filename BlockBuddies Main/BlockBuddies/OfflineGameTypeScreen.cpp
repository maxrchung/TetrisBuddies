#include "OfflineGameTypeScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "SoundManager.h"

OfflineGameTypeScreen::OfflineGameTypeScreen()
    :section(new Section(0.0f,
                         0.0f,
                         1000.0f,
                         600.0f)),

     home(new Button(Screens::OFFLINEHOME,
                     "Home",
                     -87.5f,
                     -225.0f,
                     150.0f,
                     50.0f)),

     gameType(new Button(Screens::OFFLINEGAMETYPE,
                         "Play",
                         87.5f,
                         -225.0f,
                         150.0f,
                         50.0f)),

     game(new Button(Screens::GAME,
                     "Start Game",	 
                     0.0f,
                     0.0f,
                     150.0f,
                     50.0f))
{
    UIElements.push_back(section);
    UIElements.push_back(home);
    UIElements.push_back(gameType);
    UIElements.push_back(game);

    selectables = { home,
                    gameType,
                    game };
}

void OfflineGameTypeScreen::update()
{
    Screen::update();

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }

    
    else if (gameType->isActivated ||
             (InputManager::getInstance()->enter && gameType->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(gameType->toScreen);
    }

    else if (game->isActivated ||
             (InputManager::getInstance()->enter && game->isSelected))
    {

		SoundManager::getInstance().playMusic("Sounds/Slamtris.ogg");
        ScreenManager::getInstance()->switchScreen(game->toScreen);
    }
}

void OfflineGameTypeScreen::draw()
{
    Screen::draw();
}