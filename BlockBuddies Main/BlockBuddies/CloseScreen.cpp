#include "CloseScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "ClientManager.h"
#include "LoginScreen.hpp"

CloseScreen::CloseScreen()
	:backSection(new Section(0.0f,
	                     0.0f,
						 420.0f,
						 420.0f,
                         GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
	                     0.0f,
						 400.0f,
						 400.0f)),

     title(new TextBox("QUIT",
	                   0.0f,
					   -133.33f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

	 status(new TextBox("Are you sure you want to exit?",
	                    0.0f,
						-58.33f,
						300.0f)),

	 login(new Button(Screens::LOGIN,
		              "Logout",
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

void CloseScreen::update()
{
    Screen::update();

    if (login->isActivated ||
        (InputManager::getInstance()->enter && login->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(login->toScreen);
        dynamic_cast<LoginScreen*>(ScreenManager::getInstance()->currentScreens[0])->status->message.setString("Enter username and password");
        ClientManager::getInstance().closeConnection();
    }

    else if (exit->isActivated ||
             (InputManager::getInstance()->enter && exit->isSelected))
    {
        ScreenManager::getInstance()->closeGame();
    }

    else if (cancel->isActivated ||
             (InputManager::getInstance()->enter && cancel->isSelected) ||
             InputManager::getInstance()->escape)
    {
        ScreenManager::getInstance()->popScreen();
        return;
    }
}

void CloseScreen::draw()
{
    Screen::draw();
}