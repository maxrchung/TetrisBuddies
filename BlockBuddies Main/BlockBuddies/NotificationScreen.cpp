#include "NotificationScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "ClientManager.h"
#include "LoginScreen.hpp"
#include "BlockShowerManager.hpp"

NotificationScreen::NotificationScreen()
	:backSection(new Section(0.0f,
                             0.0f,
                             420.0f,
                             320.0f,
                             GraphicsManager::getInstance()->buttonColor,
                             true)),

     section(new Section(0.0f,
	                     0.0f,
						 400.0f,
						 300.0f)),

     title(new TextBox("ERROR",
	                   0.0f,
					   -75.0f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

	 status(new TextBox("",
	                    0.0f,
						0.0f,
						300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     back(new Button(Screens::NONE,
                       "Back",
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
    UIElements.push_back(back);

    selectables = { back };
}

void NotificationScreen::update()
{
    Screen::update();

    if (back->isActivated ||
        (InputManager::getInstance()->enter  && back->isSelected) || InputManager::getInstance()->escape)
    {
        deselect();
        deactivate();
        fade.state = FadeStates::FADING_OUT;
        InputManager::getInstance()->resetInput();
        return;
    }

    if(InputManager::getInstance()->escape)
    {
        deselect();
        deactivate();
        fade.state = FadeStates::FADING_OUT;
        InputManager::getInstance()->resetInput();
    }
}

void NotificationScreen::draw()
{
    // Used to provide a darkening layer between the last layer
    // and the layers before it
    sf::RectangleShape darken(sf::Vector2f((float)GraphicsManager::getInstance()->window.getSize().x,
                                           (float)GraphicsManager::getInstance()->window.getSize().y));
    darken.setFillColor(sf::Color(0, 0, 0, fade.value/1.25f));
    GraphicsManager::getInstance()->window.draw(darken);

    Screen::draw();
}

void NotificationScreen::reload()
{
    status->reload();
}