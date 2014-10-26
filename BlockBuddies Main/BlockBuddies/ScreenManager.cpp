#include "ScreenManager.hpp"
#include "LoginScreen.hpp"

ScreenManager* ScreenManager::instance;

ScreenManager* ScreenManager::getInstance()
{
	if(!instance)
		instance = new ScreenManager;
	return instance;
}

void ScreenManager::init()
{
	currentScreen = new LoginScreen();
}

void ScreenManager::switchScreen(Screen* toScreen)
{
	delete currentScreen;
	currentScreen = toScreen;
}