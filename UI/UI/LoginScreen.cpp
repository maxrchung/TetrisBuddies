#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"

LoginScreen::LoginScreen()
{
	registerButton = Button(new RegisterScreen);
}

LoginScreen::~LoginScreen()
{

}

void LoginScreen::draw()
{

}