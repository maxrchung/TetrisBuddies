#include "OfflineCloseScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "ClientManager.h"
#include "BlockShowerManager.hpp"

OfflineCloseScreen::OfflineCloseScreen()
	:backSection(new Section(0.0f,
	                     0.0f,
						 420.0f,
						 470.0f,
                         GraphicsManager::getInstance()->buttonColor,
                         true)),

     section(new Section(0.0f,
	                     0.0f,
						 400.0f,
						 450.0f)),

     title(new TextBox("QUIT",
	                   0.0f,
					   -150.0f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

	 status(new TextBox("Are you sure you want to exit the game?",
	                    0.0f,
						-75.0f,
						300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

	 login(new Button(Screens::LOGIN,
		              "Login",
                      0.0f,
                      0.0f,
                      150.0f,
                      50.0f)),

     exit(new Button(Screens::NONE,
                     "Exit",
                     0.0f,
                     75.0f,
                     150.0f,
                     50.0f)),

     cancel(new Button(Screens::NONE,
                       "Cancel",
                       0.0f,
                       150.0f,
                       150.0f,
                       50.0f))
{
    // So we don't update/draw the close button when
    // this screen is on top
    close->isDisplayed = false;
    
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(title);
    UIElements.push_back(status);
    UIElements.push_back(login);
    UIElements.push_back(exit);
    UIElements.push_back(cancel);

    selectables = { login,
                    exit,
                    cancel };
}

void OfflineCloseScreen::update()
{
    Screen::update();

    if (login->isActivated ||
        (InputManager::getInstance()->enter && login->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(login->toScreen);
        BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;
        InputManager::getInstance()->resetInput();
    }

    else if (exit->isActivated ||
             (InputManager::getInstance()->enter && exit->isSelected))
    {
        Game::getInstance()->isRunning = false;
        InputManager::getInstance()->resetInput();
    }

    else if (cancel->isActivated ||
             (InputManager::getInstance()->enter && cancel->isSelected) ||
             InputManager::getInstance()->escape)
    {
        deselect();
        deactivate();
        fade.state = FadeStates::FADING_OUT;
        InputManager::getInstance()->resetInput();
        return;
    }
}

void OfflineCloseScreen::draw()
{

    // Used to provide a darkening layer between the last layer
    // and the layers before it
    sf::RectangleShape darken(sf::Vector2f((float)GraphicsManager::getInstance()->window.getSize().x,
                                           (float)GraphicsManager::getInstance()->window.getSize().y));
    darken.setFillColor(sf::Color(0, 0, 0, fade.value/1.25f));
    GraphicsManager::getInstance()->window.draw(darken);

    Screen::draw();
}