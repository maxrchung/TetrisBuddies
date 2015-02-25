#include "LoginScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"
#include "SoundManager.h"
#include "NotificationScreen.hpp"
#include "BlockShowerManager.hpp"

LoginScreen::LoginScreen()
    :backSection(new Section(0.0f,
                             0.0f,
                             420.0f,
                             595.0f,
                             GraphicsManager::getInstance()->buttonColor,
                             true)),

     section(new Section(0.0f,
	                     0.0f,
						 400.0f,
						 575.0f)),
                         
     title(new TextBox("BLOCK BUDDIES",
	                   0.0f,
					   -200.0f - 12.5f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

	 status(new TextBox("Welcome to the game! Login to access multiplayer.",
	                    0.0f,
						-125.0f - 12.5f,
						300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     usernameTag(new TextBox("Username: ",
		                     -140.0f,
							 -50.0f - 12.5f,
							 250.0f,
							 // We want left alignment so that we can easily line up
							 // Username: tags with the Password: tag below it
							 Alignments::LEFT)),

     passwordTag(new TextBox("Password: ",
	                         -140.0f,
							 0.0f - 12.5f,
							 250.0f,
							 Alignments::LEFT)),

     username(new TextInput(-60.0f,
		                    -50.0f - 12.5f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							Alignments::LEFT)),

     password(new TextInput(-60.0f,
		                    0.0f - 12.5f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							Alignments::LEFT,
							true)),

	 home(new Button(Screens::HOME,
		             "Login",
                     -87.5f,
                     75.0f - 12.5f,
                     150.0f,
                     50.0f)),

     signup(new Button(Screens::REGISTER,
                       "Register",
                       87.5f,
                       75.0f - 12.5f,
                       150.0f,
                       50.0f)),

     instruction(new Button(Screens::INSTRUCTION,
                            "Instructions",
                            87.5,
                            150.0f - 12.5f,
                            150.0f,
                            50.0f)),

     offlineHome(new Button(Screens::GAME,
			                "Offline",
                            -87.5f,
                            150.0f - 12.5f,
                            150.0f,
                            50.0f)),
                            
     exit(new Button(Screens::NONE,
                     "Exit",
                     0.0f,
                     225.0f - 12.5f,
                     150.0f,
                     50.0f))

{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(title);
    UIElements.push_back(status);
    UIElements.push_back(usernameTag);
    UIElements.push_back(passwordTag);
    UIElements.push_back(username);
    UIElements.push_back(password);
    UIElements.push_back(home);
    UIElements.push_back(signup);
    UIElements.push_back(instruction);
    UIElements.push_back(offlineHome);
    UIElements.push_back(exit);

    selectables = { username,
                    password,
                    home,
                    signup,
                    instruction,
                    offlineHome,
                    exit };

	//set the sound with a soundbuffer from the soundmanager
	sound.setBuffer(*SoundManager::getInstance().getSound("scream"));
	SoundManager::getInstance().playMusic("Sounds/Slamstorm.ogg");
}

void LoginScreen::update()
{
    Screen::update();

	// If no buttons are currently selected and the player presses
	// enter, then the enter button is automatically activated
	if(InputManager::getInstance()->enter)
	{
		bool selected = false;
        if (home->isSelected ||
            signup->isSelected ||
            offlineHome->isSelected)
        {
            selected = true;
        }

		if (!selected)
			home->isActivated = true;
	}

	//Bug if you fail to log in and enter a correct log in the second time.
	//Can't log in if it's not in the DB at least
    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
    {
        if(username->input.getString().getSize() < 5 || password->input.getString().getSize() < 5)
        {
            ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "Enter a minimum of 5 characters for each input.");
            return;
        }
        if (!ClientManager::getInstance().isConnected)
        {
			if (!ClientManager::getInstance().initConnection(sf::IpAddress::getLocalAddress(), 5000))
			{
                ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "Failed to connect with server. The server may be down, or you may not be connected to the Internet.");
				if (sound.getStatus() != sound.Playing)
					sound.play();
			}
        }
    
        if(ClientManager::getInstance().isConnected)
        {
            if (ClientManager::getInstance().loginUser(username->input.getString(),
                                                       password->input.getString()))
            {
                //play sound then switch screens
                sound.play();
                ScreenManager::getInstance()->switchScreen(home->toScreen);
            }

            else {
                //play sounds then change strings
				if (sound.getStatus() != sound.Playing)
					sound.play();

                ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "Bad input credentials. The username password combination may be wrong, or the account may already be logged in.");
            }
        }
    }

    else if (signup->isActivated ||
             (InputManager::getInstance()->enter && signup->isSelected))
        ScreenManager::getInstance()->switchScreen(signup->toScreen);

    else if (offlineHome->isActivated ||
             (InputManager::getInstance()->enter && offlineHome->isSelected))
    {
        //play sound then switch screen
		//sound.setBuffer(*SoundManager::getInstance().getSound("repressed"));
		//sound.play();
		//ScreenManager::getInstance()->shake(1);
		SoundManager::getInstance().playMusic("Sounds/Slamtris.ogg");
        ScreenManager::getInstance()->switchScreen(offlineHome->toScreen);
    }

    else if (instruction->isActivated ||
             (InputManager::getInstance()->enter && instruction->isSelected))
    {
        ScreenManager::getInstance()->addScreen(instruction->toScreen);
    }

    else if (exit->isActivated ||
             (InputManager::getInstance()->enter && exit->isSelected))
    {
        ScreenManager::getInstance()->closeGame();
        InputManager::getInstance()->resetInput();
    }

    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(GraphicsManager::getInstance()->window).x,
                                              sf::Mouse::getPosition(GraphicsManager::getInstance()->window).y);

    if(home->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Login with the given username and password.");

    else if(signup->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Register a new account.");

    else if(instruction->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("New to the game? Learn how to play.");

    else if(offlineHome->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Play a singleplayer offline game. Stats are not saved in this mode.");

    else if(exit->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Exit the program. See you next time!");

    else if(username->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Enter account username.");

    else if(password->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Enter account password.");
    else if(close->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Quit the game.");
    else
        status->message.setString("Welcome to the game! Login to access multiplayer.");

    status->textWrap();

    if(InputManager::getInstance()->escape)
    {
        ScreenManager::getInstance()->addScreen(Screens::OFFLINECLOSE);
    }
}

void LoginScreen::draw()
{
    Screen::draw();
}

void LoginScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;
}