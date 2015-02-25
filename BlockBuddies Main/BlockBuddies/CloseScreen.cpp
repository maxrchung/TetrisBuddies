#include "CloseScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "ClientManager.h"
#include "LoginScreen.hpp"
#include "BlockShowerManager.hpp"

CloseScreen::CloseScreen()
    :backSection(new Section(0.0f,
	                         0.0f,
						     420.0f,
						     395.0f,
                             GraphicsManager::getInstance()->buttonColor,
                             true)),

     section(new Section(0.0f,
	                     0.0f,
						 400.0f,
						 375.0f)),

     title(new TextBox("QUIT",
	                   0.0f,
					   -150.0f + 37.5f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

	 status(new TextBox("Are you sure you want to quit the game?",
	                    0.0f,
						-75.0f + 37.5f,
						300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

	 login(new Button(Screens::LOGIN,
		              "Logout",
                      -87.5f,
                      0.0f + 37.5f,
                      150.0f,
                      50.0f)),

	 home(new Button(Screens::HOME,
		              "Home",
                      -87.5f,
                      75.0f + 37.5f,
                      150.0f,
                      50.0f)),

     exit(new Button(Screens::NONE,
                     "Exit",
                     87.5f,
                     0.0f + 37.5f,
                     150.0f,
                     50.0f)),

     cancel(new Button(Screens::NONE,
                       "Back",
                       87.5f,
                       75.0f + 37.5f,
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
    UIElements.push_back(home);
    UIElements.push_back(exit);
    UIElements.push_back(cancel);

    selectables = { login,
                    home,
                    exit,
                    cancel };
}

void CloseScreen::update()
{
    Screen::update();

    if (login->isActivated ||
        (InputManager::getInstance()->enter && login->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(login->toScreen);
        ClientManager::getInstance().closeConnection();
        BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;
        InputManager::getInstance()->resetInput();
    }

    else if (home->isActivated ||
             (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }

    else if (exit->isActivated ||
             (InputManager::getInstance()->enter && exit->isSelected))
    {
        ScreenManager::getInstance()->closeGame();
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
    }

    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(GraphicsManager::getInstance()->window).x,
                                              sf::Mouse::getPosition(GraphicsManager::getInstance()->window).y);

    if(login->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Logout of the game.");

    else if (home->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Return back to the home menu.");

    else if (exit->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Exit the game and closes the program.");

    else if (cancel->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Leave the quit screen.");

    else
        status->message.setString("Are you sure you want to quit the game?");

    status->textWrap();

    if(InputManager::getInstance()->escape)
    {
        deselect();
        deactivate();
        fade.state = FadeStates::FADING_OUT;
        InputManager::getInstance()->resetInput();
    }
}

void CloseScreen::draw()
{
    // Used to provide a darkening layer between the last layer
    // and the layers before it
    sf::RectangleShape darken(sf::Vector2f((float)GraphicsManager::getInstance()->window.getSize().x,
                                           (float)GraphicsManager::getInstance()->window.getSize().y));
    darken.setFillColor(sf::Color(0, 0, 0, fade.value/1.25f));
    GraphicsManager::getInstance()->window.draw(darken);

    Screen::draw();
}

void CloseScreen::reload()
{
}