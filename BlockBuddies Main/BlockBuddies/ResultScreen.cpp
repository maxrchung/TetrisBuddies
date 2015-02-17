#include "ResultScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "ClientManager.h"
#include "SoundManager.h"
#include "BlockShowerManager.hpp"
#include <sstream>
ResultScreen::ResultScreen()
	:scoreString("5000"),
	 
    backSection(new Section(0.0f,
	                     -20.0f,
						 420.0f,
						 510.0f,
                         GraphicsManager::getInstance()->buttonColor,
                         true)),

    section(new Section(0.0f,
                         -20.0f,
                         400.0f,
                         490.0f)),
     
     title(new TextBox("GAME OVER",
                       0.0f,
                       -190.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

     status(new TextBox("Game over! Hit home to return back to the home screen, or press play again to play another round.",
                        0.0f,
                        -115.0f,
                        300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     scoreTag(new TextBox("Score:",
                          0.0f,
                          -40.0f,
                          Alignments::LEFT)),

     score(new TextBox("0",
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
    UIElements.push_back(scoreTag);
    UIElements.push_back(score);
    UIElements.push_back(game);
    UIElements.push_back(home);
	scoreString = "5000";
    selectables = { game,
                    home };
	updated = false;
}

void ResultScreen::update()
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
		ClientManager::getInstance().requestStartGame();
		SoundManager::getInstance().playMusic("Sounds/Slamtris.ogg");
        ScreenManager::getInstance()->switchScreen(game->toScreen);
	}
	
    int Number = ClientManager::getInstance().lastScore;
    scoreString = static_cast<std::ostringstream*>(&(std::ostringstream() << Number))->str();
    score->message.setString(scoreString);
    updated = true;
	
}

void ResultScreen::draw()
{
    Screen::draw();
}

void ResultScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;
}