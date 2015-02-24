#include "RegisterScreen.hpp"
#include "Section.hpp"
#include "TextBox.hpp"
#include "TextInput.hpp"
#include "GraphicsManager.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"
#include "ScreenManager.hpp"

RegisterScreen::RegisterScreen()
	:
    backSection(new Section(0.0f,
                            0.0f,
                            420.0f,
                            495.0f,
                            GraphicsManager::getInstance()->buttonColor,
                            true)),

    section(new Section(0.0f,
		                 0.0f,
						 400.0f,
						 475.0f)),

	 title(new TextBox("REGISTER",
                       0.0f,
					   -175.0f + 12.5f,
					   300.0f,
					   Alignments::CENTER,
					   true)),

     status(new TextBox("Enter username once and password twice to register an account. Enter a minimum of 5 characters.",
	                    0.0f,
						-100.0f + 12.5f,
						300.0f,
                        Alignments::CENTER,
                        false,
                        true)),

     usernameTag(new TextBox("Username: ",
	                         -140.0f,
							 -25.0f + 12.5f,
							 300.0f,
							 Alignments::LEFT)),

	 passwordTag(new TextBox("Password: ",
	                         -140.0f,
							 25.0f + 12.5f,
							 250.0f,
							 Alignments::LEFT)),

     password2Tag(new TextBox("Password: ",
	                          -140.0f,
							  75.0f + 12.5f,
							  250.0f,
							  Alignments::LEFT)),

	 username(new TextInput(-60.0f,
	                        -25.0f + 12.5f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							Alignments::LEFT)),

     password(new TextInput(-60.0f,
	                        25.0f + 12.5f,
							200.0f,
							30.0f,
							Alignments::LEFT,
							Alignments::LEFT,
							true)),

	 password2(new TextInput(-60.0f,
		                     75.0f + 12.5f,
							 200.0f,
							 30.0f,
							 Alignments::LEFT,
							 Alignments::LEFT,
							 true)),

	 home(new Button(Screens::HOME,
		             "Enter",
                     -87.5f,
                     150.0f + 12.5f,
                     150.0f,
                     50.0f)),

	 login(new Button(Screens::LOGIN,
		              "Back",
                      87.5f,
                      150.0f + 12.5f,
                      150.0f,
                      50.0f))
{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(title);
    UIElements.push_back(status);
    UIElements.push_back(usernameTag);
    UIElements.push_back(passwordTag);
    UIElements.push_back(password2Tag);
    UIElements.push_back(username);
    UIElements.push_back(password);
    UIElements.push_back(password2);
    UIElements.push_back(login);
    UIElements.push_back(home);

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
        if (!ClientManager::getInstance().isConnected)
        {
			if (!ClientManager::getInstance().initConnection(sf::IpAddress::getLocalAddress(), 5000))
            {
                ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "Failed to connect with server. The server may be down, or you may not be connected to the Internet.");
                return; // Skip the rest if we can't connect
            }
        }

        if (password->input.getString().getSize() < 5 || username->input.getString().getSize() < 5 || password2->input.getString().getSize() < 5)
        {
            ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "Enter a minimum of 5 characters for each input.");
        }
        else if (password->input.getString() == password2->input.getString())
        {
            if (ClientManager::getInstance().registerUser(username->input.getString(),
                password->input.getString()))
            {
                ScreenManager::getInstance()->switchScreen(home->toScreen);
            }
            else
            {
                ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "This username has already been taken.");

                // Need to remember to close connection so the game won't think we're still connected
                // This may potentially cause lag
                ClientManager::getInstance().closeConnection();
            }
        }
        else
        {
            ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "The passwords do not match.");
            ClientManager::getInstance().closeConnection();
        }
    }
    else if (login->isActivated ||
             (InputManager::getInstance()->enter && login->isSelected))
    {
        ScreenManager::getInstance()->switchScreen(login->toScreen);
    }

    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(GraphicsManager::getInstance()->window).x,
                                              sf::Mouse::getPosition(GraphicsManager::getInstance()->window).y);

    if(username->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Enter a username with 5 characters or more.");

    else if (password->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Enter a password with 5 characters or more.");

    else if (password2->boundingRect.getGlobalBounds().contains(mousePosition))
        status->message.setString("Enter password a second time that matches the above password.");

    else
        status->message.setString("Enter username once and password twice to register an account. Enter a minimum of 5 characters.");

    status->textWrap();
}

void RegisterScreen::draw()
{
    Screen::draw();
}