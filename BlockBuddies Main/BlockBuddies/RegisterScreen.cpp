#include "RegisterScreen.hpp"
#include "HomeScreen.hpp"
#include "Section.hpp"
#include "UIManager.hpp"
#include "TextBox.hpp"
#include "TextInput.hpp"
#include "GraphicsManager.hpp"

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

     status(new TextBox("Enter username once and password",
	                    0.0f,
						-135.0f)),

     status2(new TextBox("twice to register an account",

	                     // This is just some kind of dumb/obnoxious code I wanted to
						 // test out. What it does is basically aligns the status2 message
						 // with the status above with left alignment.
						 // As you can see, it is rather painful. I'll be looking into
						 // text wrapping options in the near future as that'll be definitely
						 // needed for display/chat later on
                         (GraphicsManager::getInstance()->getLeftCenter(status->message).x - 
						     (GraphicsManager::getInstance()->window.getSize().x / 2.0f)) /
							 GraphicsManager::getInstance()->scale,
						 -115.0f,
						 Alignments::LEFT)),

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
		if (i->isActivated)
		{
			ScreenManager::getInstance()->switchScreen(i->toScreen);
			break;
		}
}