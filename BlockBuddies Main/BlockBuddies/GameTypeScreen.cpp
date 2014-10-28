#include "HomeScreen.hpp"
#include "ProfileScreen.hpp"
#include "GameTypeScreen.hpp"
#include "GameScreen.hpp"

GameTypeScreen::GameTypeScreen()
{
	new Button(Screens::HOME,
		       "Home",
			   -175.0f,
			   -200.0f,
			   150.0f,
			   75.0f);

	new Button(Screens::PROFILE,
		       "Profile",
			   0.0f,
			   -200.0f,
			   150.0f,
			   75.0f);

	 new Button(Screens::GAMETYPE,
	            "Play",
				175.0f,
				-200.0f,
				150.0f,
				75.0f);

	 new Button(Screens::GAME,
                "Start Game",	 
				0.0f,
				0.0f,
				150.0f,
				75.0f);
}