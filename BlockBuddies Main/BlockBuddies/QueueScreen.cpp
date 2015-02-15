#include "QueueScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "ClientManager.h"
#include "LoginScreen.hpp"
#include "BlockShowerManager.hpp"

QueueScreen::QueueScreen()
	:backSection(new Section(0.0f,
                             0.0f,
                             420.0f,
                             320.0f,
                             GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
	                     0.0f,
						 400.0f,
						 300.0f)),

     title(new TextBox("QUEUE",
	                   0.0f,
					   -75.0f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

	 status(new TextBox("Looking for game",
	                    0.0f,
						0.0f,
						300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     cancel(new Button(Screens::NONE,
                       "Cancel",
                       0.0f,
                       75.0f,
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
    UIElements.push_back(cancel);

    selectables = { cancel };
}

void QueueScreen::update()
{
    Screen::update();

    if(loadingGame)
    {
        if (foundTimer.getElapsedTime().asSeconds() > 3)
        {
            fade.state = FadeStates::FADING_OUT;
            ScreenManager::getInstance()->switchScreen(Screens::MULTIPLAYER);
            BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_OUT;
        }
    }

    else
    {
        if (loadingTimer.getElapsedTime().asSeconds() > 1)
        {
            loadingTimer.restart();
            ellipsesCounter += reverse;
            if (ellipsesCounter > 2 && reverse > 0)
                reverse *= -1;
            else if (ellipsesCounter < 1 && reverse < 0)
                reverse *= -1;
            sf::String ellipses = sf::String("");
            for (int i = 0; i < ellipsesCounter; i++)
                ellipses += ".";
            status->message.setString("Looking for game" + ellipses);
        }

        if (cancel->isActivated ||
            (InputManager::getInstance()->enter && cancel->isSelected) ||
            InputManager::getInstance()->escape)
        {
            fade.state = FadeStates::FADING_OUT;
            InputManager::getInstance()->resetInput();
            ClientManager::getInstance().leaveQueue();
            return;
        }
    }
}

void QueueScreen::draw()
{
    // Used to provide a darkening layer between the last layer
    // and the layers before it
    sf::RectangleShape darken(sf::Vector2f((float)GraphicsManager::getInstance()->window.getSize().x,
                                           (float)GraphicsManager::getInstance()->window.getSize().y));
    darken.setFillColor(sf::Color(0, 0, 0, fade.value/1.25f));
    GraphicsManager::getInstance()->window.draw(darken);

    Screen::draw();
}

void QueueScreen::reload()
{
    loadingTimer.restart();
    ellipsesCounter = 0;
    status->message.setString("Looking for game");
    reverse = 1;

    // Sends the server a message to join queue
    ClientManager::getInstance().joinQueue();
    loadingGame = false;
    cancel->isDisplayed = true;
}

void QueueScreen::foundGame()
{
    status->message.setString("Game found!");
    loadingGame = true;
    foundTimer.restart();
    deselect();
    cancel->isDisplayed = false;
}