#include "HomeScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "SoundManager.h"
#include "ClientManager.h"

HomeScreen::HomeScreen()
    :backSection(new Section(0.0f,
	                         12.5f,
                             420.0f,
                             595.0f,
                             GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
                         12.5f,
                         400.0f,
                         575.0f)),

     title(new TextBox("HOME",
	                   0.0f,
					   -200.0f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

     welcome(new TextBox("Welcome to Block Buddies! Hit play to join the queue of active games. Press profile to view your stats, or help for further instructions.",
                         0.0f,
                         -100.0f,
                         300.0f,
                         Alignments::CENTER,
                         false,
                         true)),

     networkedSinglePlayer(new Button(Screens::ONLINESINGLE,
                         "soloTest",
                         0.0f,
                         0.0f,
                         150.0f,
                         50.0f)),

     multiplayer(new Button(Screens::QUEUE,
                         "Play",
                         0.0f,
                         75.0f,
                         150.0f,
                         50.0f)),

     profile(new Button(Screens::PROFILE,
                        "Profile",
                        0.0f,
                        150.0f,
                        150.0f,
                        50.0f)),

     instruction(new Button(Screens::INSTRUCTION,
                        "Help",
                        0.0f,
                        225.0f,
                        150.0f,
                        50.0f))
{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(title);
    UIElements.push_back(welcome);
    UIElements.push_back(networkedSinglePlayer);
    UIElements.push_back(multiplayer);
    UIElements.push_back(profile);
    UIElements.push_back(instruction);

    selectables = { networkedSinglePlayer,
                    multiplayer,
                    profile,
                    instruction };
}

void HomeScreen::update()
{
    // Calls base update()
    Screen::update();

    if (networkedSinglePlayer->isActivated ||
        (InputManager::getInstance()->enter && networkedSinglePlayer->isSelected))
    {
        SoundManager::getInstance().playMusic("Sounds/Slamtris.ogg");
        ClientManager::getInstance().requestStartGame();
        ScreenManager::getInstance()->switchScreen(networkedSinglePlayer->toScreen);
    }
    
    else if (multiplayer->isActivated ||
             (InputManager::getInstance()->enter && multiplayer->isSelected))
                 ScreenManager::getInstance()->addScreen(multiplayer->toScreen);

    else if (profile->isActivated ||
             (InputManager::getInstance()->enter && profile->isSelected))
                 ScreenManager::getInstance()->switchScreen(profile->toScreen);

    else if (instruction->isActivated ||
             (InputManager::getInstance()->enter && instruction->isSelected))
                 ScreenManager::getInstance()->switchScreen(instruction->toScreen);
}

void HomeScreen::draw()
{
    // Calls base draw()
    Screen::draw();
}