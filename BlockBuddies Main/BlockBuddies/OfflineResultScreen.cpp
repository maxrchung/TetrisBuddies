#include "OfflineResultScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "BlockHandler.hpp"
#include "BlockShowerManager.hpp"

OfflineResultScreen::OfflineResultScreen()
	:backSection(new Section(0.0f,
	                         0.0f,
                             420.0f,
                             410.0f,
                             GraphicsManager::getInstance()->buttonColor,
                             true)),

     section(new Section(0.0f,
                         0.0f,
                         400.0f,
                         390.0f)),
     
     title(new TextBox("GAME OVER",
                       0.0f,
                       -165.0f + 45.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

     status(new TextBox("Game over! Play another offline game?",
                        0.0f,
                        -90.0f + 45.0f,
                        300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     scoreTag(new TextBox("Score:",
                          0.0f,
                          -40.0f + 45.0f,
                          Alignments::CENTER)),

     score(new TextBox("0",
                       0.0f,
                        0.0f + 45.0f,
                        300.0f,
                        Alignments::CENTER,
                        true)), 

	 login(new Button(Screens::LOGIN,
                      "Login",
                      -87.5f,
                      75.0f + 45.0f,
                      150.0f,
                      50.0f)),

	 offlineGame(new Button(Screens::GAME,
                            "Play Again",
                            87.5f,
                            75.0f + 45.0f,
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

    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(GraphicsManager::getInstance()->window).x,
                                              sf::Mouse::getPosition(GraphicsManager::getInstance()->window).y);

    if(login->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Return to the login screen. Results are not saved unless logged into an account.");
    else if(offlineGame->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Play another offline game.");
    else
        status->message.setString("Game over! Play another offline game?");

    status->textWrap();
}

void OfflineResultScreen::draw()
{
    Screen::draw();
}