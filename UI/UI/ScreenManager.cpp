#include "ScreenManager.hpp"
#include "LoginScreen.hpp"

Screen* ScreenManager::currentScreen;

void ScreenManager::switchScreen(Screen* toScreen)
{
	currentScreen = toScreen;
}