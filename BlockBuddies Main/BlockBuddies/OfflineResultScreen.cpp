#include "OfflineResultScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "BlockHandler.hpp"
#include "BlockShowerManager.hpp"

OfflineResultScreen::OfflineResultScreen()
	:backSection(new Section(0.0f,
	                     0.0f,
						 420.0f,
						 620.0f,
                         GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
                         0.0f,
                         400.0f,
                         600.0f)),
     
     title(new TextBox("RESULTS",
                       0.0f,
                       -200.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

     status(new TextBox("Currently playing in offline mode, please login to track your stats",
                        0.0f,
                        -125.0f,
                        300.0f)),

     scoreTag(new TextBox("Score",
                          0.0f,
                          -40.0f,
                          Alignments::LEFT)),

     score(new TextBox("0",
                       0.0f,
                        0.0f,
                        300.0f,
                        Alignments::CENTER,
                        true)), 

	 login(new Button(Screens::LOGIN,
                      "Login",
                      0.0f,
                      100.5f,
                      150.0f,
                      50.0f)),

	 offlineGame(new Button(Screens::GAME,
                            "Play Again",
                            0.0f,
                            175.0f,
                            150.0f,
                            50.0f)),

     offlineHome(new Button(Screens::OFFLINEHOME,
	                        "Home",
                            0.0f,
                            250.0f,
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
    UIElements.push_back(offlineHome);
    UIElements.push_back(offlineGame);

    selectables = { login,
                    offlineHome,
                    offlineGame };
}

void OfflineResultScreen::update()
{
    Screen::update();

	score->message.setString(std::to_string(BlockHandler::displayScore));

    if (offlineHome->isActivated ||
        (InputManager::getInstance()->enter && offlineHome->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(offlineHome->toScreen);
    }
    
    else if (offlineGame->isActivated ||
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