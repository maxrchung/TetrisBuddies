#include "ScreenManager.hpp"
#include "LoginScreen.hpp"

ScreenManager::ScreenManager()
{
	currentScreen = new LoginScreen;
}

ScreenManager::~ScreenManager() 
{
	delete currentScreen;
}