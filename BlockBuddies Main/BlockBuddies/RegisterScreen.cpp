#include "RegisterScreen.hpp"
#include "Section.hpp"
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
						-125.0f,
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

	 home(new Button(Screens::HOME,
		             "Enter",
                     0.0f,
                     137.5f,
                     150.0f,
                     50.0f)),

	 login(new Button(Screens::LOGIN,
		              "Cancel",
                      0.0f,
                      212.5f,
                      150.0f,
                      50.0f))
{
    UIElements = { section,
                   title,
                   status,
                   usernameTag,
                   passwordTag,
                   password2Tag,
                   username,
                   password,
                   password2,
                   login,
                   home };

    selectables = { username,
                    password,
                    password2,
                    home,
                    login };
}

void RegisterScreen::update()
{
    Screen::update();

	// If no buttons are currently selected and the player presses
	// enter, then the enter button is automatically activated
	if(InputManager::getInstance()->enter)
	{
		bool selected = false;
        if (login->isSelected ||
            home->isSelected)
				selected = true;

        if (!selected)
			home->isActivated = true;
	}

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
    {
        if (password->input.getString() == password2->input.getString())
        {
            if (ClientManager::getInstance().registerUser(username->input.getString(),
                password->input.getString()))
            {
                ScreenManager::getInstance()->switchScreen(home->toScreen);
            }
            else
                status->message.setString("Username taken");
        }
        else
            status->message.setString("Passwords do not match");
    }
    else if (login->isActivated ||
             (InputManager::getInstance()->enter && login->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(login->toScreen);
    }
}

void RegisterScreen::draw()
{
    Screen::draw();
}