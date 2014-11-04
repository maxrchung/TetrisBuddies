#include "ScreenManager.hpp"
#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"
#include "HomeScreen.hpp"
#include "ProfileScreen.hpp"
#include "GameTypeScreen.hpp"
#include "GameScreen.hpp"
#include "UIManager.hpp"
#include "InputManager.hpp"

ScreenManager* ScreenManager::instance;

ScreenManager* ScreenManager::getInstance()
{
	if(!instance)
		instance = new ScreenManager;
	return instance;
}

void ScreenManager::init()
{
	// Set this to something else if you want to start on a specific screen
	currentScreen = new LoginScreen();
}

void ScreenManager::switchScreen(const Screens toScreen)
{	
	// Turn this false so that it doesn't get improperly read for future
	// switchScreen calculations
	InputManager::getInstance()->mouseReleased = false;

	// Making sure to delete for memory leak issues
	delete currentScreen;

	// Clears the UIElements list so that the next Screen's elements
	// can be put on
	// UIManager will deal with memory leaks
	UIManager::getInstance()->clear();

	// Changes the screen based on the given enum
	switch (toScreen)
	{
	case LOGIN:
		currentScreen = new LoginScreen();
		break;
	case REGISTER:
		currentScreen = new RegisterScreen();
		break;
	case HOME:
		currentScreen = new HomeScreen();
		break;
	case PROFILE:
		currentScreen = new ProfileScreen();
		break;
	case GAMETYPE:
		currentScreen = new GameTypeScreen();
		break;
	case GAME:
		currentScreen = new GameScreen();
		break;
	default:
		break;
	}
}