#include "HomeScreen.hpp"
#include "LoginScreen.hpp"
#include "ProfileScreen.hpp"
#include "GameTypeScreen.hpp"

HomeScreen::HomeScreen()
{
	new Button(Screens::LOGIN,
	           "Logout",
			   0.0f,
			   0.0f,
			   150.0f,
			   75.0f);

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
}