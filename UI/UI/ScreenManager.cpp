#include "ScreenManager.hpp"
#include "LoginScreen.hpp"

Screen& ScreenManager::currentScreen = LoginScreen();

void ScreenManager::switchScreen(Screen& toScreen)
{
	currentScreen = toScreen;
}