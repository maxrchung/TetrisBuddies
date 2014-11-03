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
					   Alignment::CENTER,
					   true)), // Parameter tells the constructor that it is a title
     usernameTag(new TextBox("Username: ",
		                     -140.0f,
							 -25.0f,
							 Alignment::LEFT)),
     passwordTag(new TextBox("Password: ",
	                         -140.0f,
							 25.0f,
							 Alignment::LEFT)),
 	 status(new TextBox("Enter username and password to login",
	                    0.0f,
						-125.0f)),
     username(new TextInput(-60.0f,
		                    -25.0f,
							200.0f,
							30.0f,
							Alignment::LEFT)),
     password(new TextInput(-60.0f,
		                    25.0f,
							200.0f,
							30.0f,
							Alignment::LEFT,
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