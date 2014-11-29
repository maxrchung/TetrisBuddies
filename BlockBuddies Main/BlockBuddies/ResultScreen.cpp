#include "ResultScreen.hpp"
#include "InputManager.hpp"

ResultScreen::ResultScreen()
	:section(new Section(0.0f,
                         0.0f,
                         400.0f,
                         600.0f)),
     
     title(new TextBox("RESULTS",
                       0.0f,
                       -200.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

     status(new TextBox("Game over!",
                        0.0f,
                        -125.0f,
                        300.0f)),

     scoreTag(new TextBox("Score",
                          0.0f,
                          -40.0f,
                          Alignments::LEFT)),

     score(new TextBox("5000",
                       0.0f,
                       0.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

	 game(new Button(Screens::GAME,
                     "Play Again",
                     0.0f,
                     137.5f,
                     150.0f,
                     50.0f)),

     home(new Button(Screens::HOME,
	                 "Home",
                     0.0f,
                     212.5f,
                     150.0f,
                     50.0f))
{
    UIElements = { section,
                   title,
                   status,
                   scoreTag,
                   score,
                   game,
                   home };
    
    selectables = { game,
                    home };

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
        ScreenManager::getInstance()->switchScreen(game->toScreen);
	}
}

void ResultScreen::draw()
{
    Screen::draw();
}