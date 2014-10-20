#include "ScreenManager.hpp"
#include "LoginScreen.hpp"

Screen* ScreenManager::currentScreen;

void ScreenManager::init()
{
	currentScreen = new LoginScreen();
}

void ScreenManager::switchScreen(Screen* toScreen)
{
	delete currentScreen;
	currentScreen = toScreen;
}