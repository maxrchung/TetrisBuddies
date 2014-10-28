#include "RegisterScreen.hpp"
#include "HomeScreen.hpp"

RegisterScreen::RegisterScreen()
{
	new Button(Screens::LOGIN,
		       "Cancel",
			   0.0f,
			   200.0f,
			   150.0f,
			   75.0f);

	new Button(Screens::HOME,
		       "Enter",
			   0.0f,
			   100.0f,
			   150.0f,
			   75.0f);
}