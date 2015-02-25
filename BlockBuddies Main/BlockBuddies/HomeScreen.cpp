#include "HomeScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"
#include "SoundManager.h"
#include "ClientManager.h"
#include "BlockShowerManager.hpp"

HomeScreen::HomeScreen()
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

     title(new TextBox("HOME",
	                   0.0f,
					   -150.0f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

     welcome(new TextBox("The game is now connected with the server. Access the multiplayer features from this menu.",
                         0.0f,
                         -75.0f,
                         300.0f,
                         Alignments::CENTER,
                         false,
                         true)),

     networkedSinglePlayer(new Button(Screens::ONLINESINGLE,
                         "Singleplayer",
                         -87.5f,
                         0.0f,
                         150.0f,
                         50.0f)),

     multiplayer(new Button(Screens::QUEUE,
                         "Multiplayer",
                         87.5f,
                         0.0f,
                         150.0f,
                         50.0f)),

     profile(new Button(Screens::PROFILE,
                        "Profile",
                        -87.5f,
                        75.0f,
                        150.0f,
                        50.0f)),

     instruction(new Button(Screens::INSTRUCTION,
                        "Instructions",
                        87.5f,
                        75.0f,
                        150.0f,
                        50.0f)),

     logout(new Button(Screens::LOGIN,
                        "Logout",
                        0,
                        150.0f,
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
    UIElements.push_back(logout);

    selectables = { networkedSinglePlayer,
                    multiplayer,
                    profile,
                    instruction,
                    logout };
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
                 ScreenManager::getInstance()->addScreen(profile->toScreen);

    else if (instruction->isActivated ||
             (InputManager::getInstance()->enter && instruction->isSelected))
                 ScreenManager::getInstance()->addScreen(instruction->toScreen);

    else if (logout->isActivated ||
             (InputManager::getInstance()->enter && logout->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(logout->toScreen);
        ClientManager::getInstance().closeConnection();
        InputManager::getInstance()->resetInput();
    }

    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(GraphicsManager::getInstance()->window).x,
                                              sf::Mouse::getPosition(GraphicsManager::getInstance()->window).y);

    if(networkedSinglePlayer->boundingRect.getGlobalBounds().contains(mousePosition))
        welcome->message.setString("Play a singleplayer game. Stats will be saved to the profile page.");

    else if (multiplayer->boundingRect.getGlobalBounds().contains(mousePosition))
        welcome->message.setString("Join the multiplayer queue and look for an available game.");

    else if (profile->boundingRect.getGlobalBounds().contains(mousePosition))
        welcome->message.setString("View account stats tracked from singleplayer and multiplayer.");

    else if (instruction->boundingRect.getGlobalBounds().contains(mousePosition))
        welcome->message.setString("New to the game? Learn how to play.");

    else if (logout->boundingRect.getGlobalBounds().contains(mousePosition))
        welcome->message.setString("Logout of this account and return back to the main menu.");
    else if(close->boundingRect.getGlobalBounds().contains(mousePosition))
        welcome->message.setString("Quit the game.");
    else
        welcome->message.setString("The game is now connected with the server. Access the multiplayer features from this menu.");

    welcome->textWrap();

    if(InputManager::getInstance()->escape)
    {
        ScreenManager::getInstance()->addScreen(close->toScreen);
    }
}

void HomeScreen::draw()
{
    // Calls base draw()
    Screen::draw();
}

void HomeScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;
}