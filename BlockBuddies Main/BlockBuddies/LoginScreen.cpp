#include "LoginScreen.hpp"
#include "ScreenManager.hpp"

LoginScreen::LoginScreen()
	:section(new Section(0.0f,
	                     0.0f,
						 400.0f,
						 600.0f)),

     title(new TextBox("LOGIN",
	                   0.0f,
					   -200.0f,
					   Alignments::CENTER,

					   // Parameter tells the constructor that it is a title
					   true)),

     usernameTag(new TextBox("Username: ",
		                     -140.0f,
							 -25.0f,

							 // We want left alignment so that we can easily line up
							 // Username: tags with the Password: tag below it
							 Alignments::LEFT)),

     passwordTag(new TextBox("Password: ",
	                         -140.0f,
							 25.0f,
							 Alignments::LEFT)),

 	 status(new TextBox("Enter username and password to login",
	                    0.0f,
						-125.0f)),

     username(new TextInput(-60.0f,
		                    -25.0f,
							200.0f,
							30.0f,
							Alignments::LEFT)),

     password(new TextInput(-60.0f,
		                    25.0f,
							200.0f,
							30.0f,
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
	for(auto i : buttons)
		if (i->isActivated)
		{
			ScreenManager::getInstance()->switchScreen(i->toScreen);
			break;
		}
}