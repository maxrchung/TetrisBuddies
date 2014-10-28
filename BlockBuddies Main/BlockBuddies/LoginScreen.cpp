#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"
#include "GraphicsManager.hpp"
#include "HomeScreen.hpp"
#include "UIManager.hpp"

LoginScreen::LoginScreen()
{
	// Kind of obvious, but I'll say it anyways, we must use new here otherwise 
	// the Elements will fall out of scope

	// And also, we don't need to save these UIElements to any variables because 
	// the screen's job is to just declare the elements. The UIElement constructor
	// will automatically put 'em all into the UIManager
	new Button(Screens::HOME,
               "Enter",
			   0.0f,
			   100.0f,
			   150.0f,
			   75.0f);

    new Button(Screens::REGISTER,
               "Register",
			   0.0f,
			   200.0f,
			   150.0f,
			   75.0f);
}