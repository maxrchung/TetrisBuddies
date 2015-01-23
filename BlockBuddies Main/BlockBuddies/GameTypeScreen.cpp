#include "GameTypeScreen.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"
#include "ScreenManager.hpp"
#include "SoundManager.h"
#include "BlockShowerManager.hpp"

GameTypeScreen::GameTypeScreen()
    :backSection(new Section(0.0f,
	                     0.0f,
						 1020.0f,
						 620.0f,
                         GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
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
                         50.0f)),

     game(new Button(Screens::ONLINESINGLE,
                     "Solo Game",
                     0.0f,
                     -37.5f,
                     150.0f,
                     50.0f)),
     
     multiplayer(new Button(Screens::MULTIPLAYER,
                            "Multiplayer",
                            0.0f,
                            37.5f,
                            150.0f,
                            50.0f))
{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(home);
    UIElements.push_back(profile);
    UIElements.push_back(gameType);
    UIElements.push_back(game);
    UIElements.push_back(multiplayer);

    selectables = { home,
                    profile,
                    gameType,
                    game,
                    multiplayer};
}

void GameTypeScreen::update()
{
    Screen::update();

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }
    
    else if (profile->isActivated ||
             (InputManager::getInstance()->enter && profile->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(profile->toScreen);
    }
        
    else if (gameType->isActivated ||
             (InputManager::getInstance()->enter && gameType->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(gameType->toScreen);
    }

    else if (game->isActivated ||
             (InputManager::getInstance()->enter && game->isSelected))
	{
        BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_OUT;

		SoundManager::getInstance().playMusic("Sounds/Slamtris.ogg");
		ClientManager::getInstance().requestStartGame();
        ScreenManager::getInstance()->switchScreen(game->toScreen);
    }

    else if (multiplayer->isActivated ||
             (InputManager::getInstance()->enter && multiplayer->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(game->toScreen);
    }
}

void GameTypeScreen::draw()
{
    Screen::draw();
}