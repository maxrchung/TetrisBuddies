#include "RegisterScreen.hpp"
#include "Section.hpp"
#include "UIManager.hpp"
#include "TextBox.hpp"
#include "TextInput.hpp"
#include "GraphicsManager.hpp"
#include "InputManager.hpp"
#include "DatabaseManager.h"

RegisterScreen::RegisterScreen()
	:section(new Section(0.0f,
		     0.0f,
			 400.0f,
			 600.0f)),

	 title(new TextBox("REGISTER",
                       0.0f,
					   -200.0f,
					   Alignments::CENTER,
					   true)),

     status(new TextBox("Enter username once and password\ntwice to register an account",
	                    0.0f,
						-135.0f)),

     usernameTag(new TextBox("Username: ",
	                         -140.0f,
							 -50.0f,
							 Alignments::LEFT)),

	 passwordTag(new TextBox("Password: ",
	                         -140.0f,
							 0.0f,
							 Alignments::LEFT)),

     password2Tag(new TextBox("Password: ",
	                          -140.0f,
							  50.0f,
							  Alignments::LEFT)),

	 username(new TextInput(-60.0f,
	                        -50.0f,
							200.0f,
							30.0f,
							Alignments::LEFT)),

     password(new TextInput(-60.0f,
	                        0.0f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							true)),

	 password2(new TextInput(-60.0f,
		                     50.0f,
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

			  new Button(Screens::LOGIN,
		                 "Cancel",
						 0.0f,
						 200.0f,
						 150.0f,
						 50.0f) })
{
}

void RegisterScreen::update()
{
	for(auto i : buttons)
		if (i->isActivated ||
		    (InputManager::getInstance()->enter && i->isSelected))
		{
		if (i->getLabel().getString() == "Enter")
		{
			//This might be optimized
			if (password->getText().getString() == password2->getText().getString())
			{
				if (!username->getText().getString().isEmpty() && password->getText().getString() == password2->getText().getString() && !DatabaseManager::getInstance().loginUser(username->getText().getString(), password->getText().getString()))
				{
					DatabaseManager::getInstance().registerUser(username->getText().getString(), password->getText().getString());
					ScreenManager::getInstance()->switchScreen(i->toScreen);
					break;
				}
			}
			else status->setString("Passwords do not match.");


		}
		else if (i->getLabel().getString() == "Cancel")
		{
			ScreenManager::getInstance()->switchScreen(i->toScreen);
		}
		
			break;
		}
}

void RegisterScreen::draw()
{

}