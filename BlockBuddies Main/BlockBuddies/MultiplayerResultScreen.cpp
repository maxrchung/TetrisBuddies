#include "MultiplayerResultScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "ClientManager.h"
#include "SoundManager.h"
#include "BlockShowerManager.hpp"
#include <sstream>

MultiplayerResultScreen::MultiplayerResultScreen()
    :
    backSection(new Section(0.0f,
                            0.0f,
                            420.0f,
                            470.0f,
                            GraphicsManager::getInstance()->buttonColor,
                            true)),

    section(new Section(0.0f,
                        0.0f,
                        400.0f,
                        450.0f)),
     
     title(new TextBox("GAME OVER",
                       0.0f,
                       -150.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

     status(new TextBox("Game over! Hit home to return back to the home screen, or press play again to rejoin the game queue.",
                        0.0f,
                        -75.0f,
                        300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     result(new TextBox("YOU",
                        0.0f,
                        0.0f,
                        300.0f,
                        Alignments::CENTER,
                        true)),

	 game(new Button(Screens::ONLINESINGLE,
                     "Play Again",
                     0.0f,
                     150.0f,
                     150.0f,
                     50.0f)),

     home(new Button(Screens::HOME,
	                 "Home",
                     0.0f,
                     75.0f,
                     150.0f,
                     50.0f))
{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(title);
    UIElements.push_back(status);
    UIElements.push_back(result);
    UIElements.push_back(game);
    UIElements.push_back(home);

    selectables = { game,
                    home };
}

void MultiplayerResultScreen::update()
{
    Screen::update();

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }
    
    else if (game->isActivated ||
             (InputManager::getInstance()->enter && game->isSelected))
    {
        ScreenManager::getInstance()->addScreen(game->toScreen);
	}
}

void MultiplayerResultScreen::draw()
{
    Screen::draw();
}

void MultiplayerResultScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;

    if(ClientManager::getInstance().wonGame)
        result->message.setString("YOU WON!");
    else
        result->message.setString("YOU LOSE!");
}