#include "OfflineResultScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "BlockHandler.hpp"
#include "BlockShowerManager.hpp"

OfflineResultScreen::OfflineResultScreen()
	:backSection(new Section(0.0f,
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

     status(new TextBox("The game is currently running in offline mode. Login to track your stats, or press play again to play another round.",
                        0.0f,
                        -115.0f,
                        300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     scoreTag(new TextBox("Score:",
                          0.0f,
                          -40.0f,
                          Alignments::CENTER)),

     score(new TextBox("0",
                       0.0f,
                        0.0f,
                        300.0f,
                        Alignments::CENTER,
                        true)), 

	 login(new Button(Screens::LOGIN,
                      "Login",
                      0.0f,
                      75.5f,
                      150.0f,
                      50.0f)),

	 offlineGame(new Button(Screens::GAME,
                            "Play Again",
                            0.0f,
                            150.0f,
                            150.0f,
                            50.0f))
{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(title);
    UIElements.push_back(status);
    UIElements.push_back(scoreTag);
    UIElements.push_back(score);
    UIElements.push_back(login);
    UIElements.push_back(offlineGame);

    selectables = { login,
                    offlineGame };
}

void OfflineResultScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;
}

void OfflineResultScreen::update()
{
    Screen::update();

	score->message.setString(std::to_string(BlockHandler::displayScore));

    if (offlineGame->isActivated ||
             (InputManager::getInstance()->enter && offlineGame->isSelected))
    {
        BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_OUT;
        ScreenManager::getInstance()->switchScreen(offlineGame->toScreen);
	}

    else if (login->isActivated ||
        (InputManager::getInstance()->enter && login->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(login->toScreen);
    }
}

void OfflineResultScreen::draw()
{
    Screen::draw();
}