#include "ScreenManager.hpp"
#include "LoginScreen.hpp"

Screen* ScreenManager::currentScreen = new LoginScreen;

ScreenManager::ScreenManager()
{
}

ScreenManager::~ScreenManager() 
{
	delete currentScreen;
}

void ScreenManager::switchScreen(Screen* toScreen)
{
	currentScreen = toScreen;
}