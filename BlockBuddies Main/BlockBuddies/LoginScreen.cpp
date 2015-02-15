#include "LoginScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"
#include "SoundManager.h"
#include "NotificationScreen.hpp"
#include "BlockShowerManager.hpp"

LoginScreen::LoginScreen()
    :backSection(new Section(0.0f,
                             12.5f,
                             420.0f,
                             645.0f,
                             GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
	                     12.5f,
						 400.0f,
						 625.0f)),
                         
     title(new TextBox("BLOCK BUDDIES",
	                   0.0f,
					   -225.0f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

	 status(new TextBox("Welcome to the game! Enter your username and password to login. Press register to create a new account, or press offline to play a single-player game.",
	                    0.0f,
						-125.0f,
						300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     usernameTag(new TextBox("Username: ",
		                     -140.0f,
							 -25.0f,
							 250.0f,
							 // We want left alignment so that we can easily line up
							 // Username: tags with the Password: tag below it
							 Alignments::LEFT)),

     passwordTag(new TextBox("Password: ",
	                         -140.0f,
							 25.0f,
							 250.0f,
							 Alignments::LEFT)),

     username(new TextInput(-60.0f,
		                    -25.0f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							Alignments::LEFT)),

     password(new TextInput(-60.0f,
		                    25.0f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							Alignments::LEFT,
							true)),

	 home(new Button(Screens::HOME,
		             "Login",
                     0.0f,
                     100.0f,
                     150.0f,
                     50.0f)),

     signup(new Button(Screens::REGISTER,
                       "Register",
                       0.0f,
                       175.0f,
                       150.0f,
                       50.0f)),

     offlineHome(new Button(Screens::GAME,
			                "Offline",
                            0.0f,
                            250.0f,
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
    UIElements.push_back(offlineHome);

    selectables = { username,
                    password,
                    home,
                    signup,
                    offlineHome };

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

                ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "Bad username or password combination.");
            }
        }
    }

    else if (signup->isActivated ||
             (InputManager::getInstance()->enter && signup->isSelected))
    {
        if (!ClientManager::getInstance().isConnected)
        {
			if (!ClientManager::getInstance().initConnection(sf::IpAddress::getLocalAddress(), 5000))
			{
                ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "Failed to connect with server. The server may be down, or you may not be connected to the Internet.");
				if (sound.getStatus() != sound.Playing)
					sound.play();
			}
            else
            {
                //play sound then switch screen
                sound.play();
                ScreenManager::getInstance()->switchScreen(signup->toScreen);
            }
        }
				
        else
        {
            //play sound then switch screen
            sound.play();
            ScreenManager::getInstance()->switchScreen(signup->toScreen);
        }
    }

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
}

void LoginScreen::draw()
{
    Screen::draw();
}

void LoginScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;
}