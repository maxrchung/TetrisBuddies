#include "ProfileScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "ClientManager.h"
/*
TextBox* nameTag;
TextBox* hsTag;
TextBox* gpTag;
TextBox* gwTag;
*/

ProfileScreen::ProfileScreen()
	:
	section(new Section(0.0f,
	                     0.0f,
						 1000.0f,
						 600.0f)),
						 
	usernameTag(new TextBox("UserName: ",
						 -250.0f,
						 -125.0f,
						 150.0f,
						 Alignments::LEFT)),

	nameTag(new TextBox(ClientManager::getInstance().getName(),
						 -70.0f,
						 -125.0f,
						 250.0f,
						 Alignments::LEFT)),

	highscoreTag(new TextBox("High Score: ",
						 -250.0f,
						 -50.0f,
						 250.0f,
						 Alignments::LEFT)),

	hsTag(new TextBox("0",
						 -70.0f,
						 -50.0f,
						 250.0f,
						 Alignments::LEFT)),

	gamesplayedTag(new TextBox("Games Played: ",
						 -250.0f,
						 25.0f,
						 250.0f,
						 Alignments::LEFT)),
	gpTag(new TextBox("0",
						 -70.0f,
						 25.0f,
						 250.0f,
						 Alignments::LEFT)),

	gameswonTag(new TextBox("Games Won: ",
						 -250.0f,
						 100.0f,
						 250.0f,
						 Alignments::LEFT)),

	gwTag(new TextBox("0",
						 -70.0f,
						 100.0f,
						 250.0f,
						 Alignments::LEFT)),


	 home(new Button(Screens::HOME,
                     "Home",
                     -175.0f,
                     -225.0f,
                     150.0f,
                     50.0f)),

     profile(new Button(Screens::PROFILE,
                        "Profile",
                        0.0f,
                        -225.0f,
                        150.0f,
                        50.0f)),

     gameType(new Button(Screens::GAMETYPE,
    		             "Play",
                         175.0f,
                         -225.0f,
                         150.0f,
                         50.0f))
{
    UIElements.push_back(section);
	UIElements.push_back(usernameTag);
	UIElements.push_back(highscoreTag);
	UIElements.push_back(gameswonTag);
	UIElements.push_back(gamesplayedTag);
	UIElements.push_back(nameTag);
	UIElements.push_back(hsTag);
	UIElements.push_back(gwTag);
	UIElements.push_back(gpTag);
    UIElements.push_back(home);
    UIElements.push_back(profile);
    UIElements.push_back(gameType);

    selectables = { home,
                    profile,
                    gameType };
}

void ProfileScreen::update()
{
    Screen::update();

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }

    else if (profile->isActivated ||
             (InputManager::getInstance()->enter && home->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(home->toScreen);
    }

    else if (gameType->isActivated ||
             (InputManager::getInstance()->enter && gameType->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(gameType->toScreen);
    }
}

void ProfileScreen::draw()
{
    Screen::draw();
}