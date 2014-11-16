#include "LoginScreen.hpp"
#include "ScreenManager.hpp"
#include "InputManager.hpp"
#include "DatabaseManager.h"
#include "ClientManager.h"
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

 	 status(new TextBox((clientManager::getInstance().initConnection(sf::IpAddress::getLocalAddress(),5000)) ? "Enter username and passowrd ": "Could not connect",
	                    0.0f,
						-125.0f,
						300.0f)),

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

	 buttons({ new Button(Screens::HOME,
		                  "Enter",
						  0.0f,
						  125.0f,
						  150.0f,
						  50.0f),

			   new Button(Screens::REGISTER,
			              "Register",
						  0.0f,
						  200.0f,
						  150.0f,
						  50.0f) })
{
}

void LoginScreen::update()
{
	//Bug if you fail to log in and enter a correct log in the second time.
	//Can't log in if it's not in the DB at least
	for (auto i : buttons)
	{
		if (i->label.getString() == "Enter")
		{

			if (i->isActivated ||
				(InputManager::getInstance()->enter && i->isSelected))
			{
				if (clientManager::getInstance().loginUser(username->getText().getString(), password->getText().getString()))
				{
					ScreenManager::getInstance()->switchScreen(i->toScreen);
				}
				else status->setString("Wrong username or password.");

				break;
			}

		}
		else if (i->label.getString() == "Register")
		{

			if (i->isActivated ||
				(InputManager::getInstance()->enter && i->isSelected))
			ScreenManager::getInstance()->switchScreen(i->toScreen);
			break;
		}

		

	}
	
}

void LoginScreen::draw()
{

}