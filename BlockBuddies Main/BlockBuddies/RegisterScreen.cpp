#include "RegisterScreen.hpp"
#include "Section.hpp"
#include "UIManager.hpp"
#include "TextBox.hpp"
#include "TextInput.hpp"
#include "GraphicsManager.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"

RegisterScreen::RegisterScreen()
	:section(new Section(0.0f,
		                 0.0f,
						 400.0f,
						 600.0f)),

	 title(new TextBox("REGISTER",
                       0.0f,
					   -200.0f,
					   300.0f,
					   Alignments::CENTER,
					   true)),

     status(new TextBox("Enter username once and password twice to register an account",
	                    0.0f,
						-135.0f,
						300.0f)),

     usernameTag(new TextBox("Username: ",
	                         -140.0f,
							 -50.0f,
							 300.0f,
							 Alignments::LEFT)),

	 passwordTag(new TextBox("Password: ",
	                         -140.0f,
							 0.0f,
							 250.0f,
							 Alignments::LEFT)),

     password2Tag(new TextBox("Password: ",
	                          -140.0f,
							  50.0f,
							  250.0f,
							  Alignments::LEFT)),

	 username(new TextInput(-60.0f,
	                        -50.0f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							Alignments::LEFT)),

     password(new TextInput(-60.0f,
	                        0.0f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							Alignments::LEFT,
							true)),

	 password2(new TextInput(-60.0f,
		                     50.0f,
							 200.0f,
							 30.0f,
							 Alignments::LEFT,
							 Alignments::LEFT,
							 true)),

	buttons({ new Button(Screens::HOME,
		                 "Enter",
						 0.0f,
						 137.5f,
						 150.0f,
						 50.0f),

			  new Button(Screens::LOGIN,
		                 "Cancel",
						 0.0f,
						 212.5f,
						 150.0f,
						 50.0f) })
{
}

void RegisterScreen::update()
{
	// If no buttons are currently selected and the player presses
	// enter, then the enter button is automatically activated
	if(InputManager::getInstance()->enter)
	{
		bool selected = false;
		for(auto i : buttons)
			if (i->isSelected)
			{
				selected = true;
				break;
			}

		if (!selected)
			buttons[0]->isActivated = true;
	}

	for(auto i : buttons)
		if (i->isActivated ||
		    (InputManager::getInstance()->enter && i->isSelected))
		{
			if (i->label.getString() == "Enter")
			{
				//This might be optimized
				if (password->input.getString() == password2->input.getString())
				{
					if (ClientManager::getInstance().registerUser(username->input.getString(),
					             	                              password->input.getString()))
						ScreenManager::getInstance()->switchScreen(i->toScreen);
					else
						status->message.setString("Username taken");
				}
				else 
					status->message.setString("Passwords do not match");
			}
			else if (i->label.getString() == "Cancel")
			{
				ScreenManager::getInstance()->switchScreen(i->toScreen);
			}

			break;
		}
}

void RegisterScreen::draw()
{

}