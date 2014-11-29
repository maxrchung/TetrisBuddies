#include "LoginScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"
#include "SoundManager.h"
LoginScreen::LoginScreen()
	:section(new Section(0.0f,
	                     0.0f,
						 400.0f,
						 600.0f)),

     title(new TextBox("LOGIN",
	                   0.0f,
					   -200.0f,
					   300.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

	 status(new TextBox("Enter username and password ",
	                    0.0f,
						-125.0f,
						300.0f)),

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
		             "Enter",
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

     offlineHome(new Button(Screens::OFFLINEHOME,
			            "Offline Mode",
                        0.0f,
                        250.0f,
                        150.0f,
                        50.0f))
{
    UIElements = { section,
                   title,
                   status,
                   usernameTag,
                   passwordTag,
                   username,
                   password,
                   home,
                   signup,
                   offlineHome };

    selectables = { username,
                    password,
                    home,
                    signup,
                    offlineHome };

	//set the sound with a soundbuffer from the soundmanager
	sound.setBuffer(*SoundManager::getInstance().getSound("scream"));
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
        if (!ClientManager::getInstance().isConnected)
        {
            if (!ClientManager::getInstance().initConnection(sf::IpAddress::getLocalAddress(), 5000))
                status->message.setString("Connection failed");
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
                
                status->message.setString("Wrong username or password");
            }
        }
    }

    else if (signup->isActivated ||
             (InputManager::getInstance()->enter && signup->isSelected))
    {
        if (!ClientManager::getInstance().isConnected)
        {
            if (!ClientManager::getInstance().initConnection(sf::IpAddress::getLocalAddress(), 5000))
                status->message.setString("Connection failed");
        }
				
        else
        {
            //play sound then switch screen
            sound.play();
            ScreenManager::getInstance()->switchScreen(signup->toScreen);
        }
    }

    if (offlineHome->isActivated ||
        (InputManager::getInstance()->enter && offlineHome->isSelected))
    {
        //play sound then switch screen
        sound.play();
        ScreenManager::getInstance()->switchScreen(offlineHome->toScreen);
    }
}

void LoginScreen::draw()
{
    Screen::draw();
}