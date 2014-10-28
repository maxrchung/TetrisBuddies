#include "ScreenManager.hpp"
#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"
#include "HomeScreen.hpp"
#include "ProfileScreen.hpp"
#include "GameTypeScreen.hpp"
#include "GameScreen.hpp"
#include "UIManager.hpp"
#include <iostream>

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
	// Making sure to delete for memory leak issues
	delete currentScreen;

	// Clears the UIElements list so that the next Screen's elements
	// can be put on
	UIManager::getInstance()->clear();

	switch (toScreen)
	{
	case LOGIN:
		currentScreen = new LoginScreen();

		// Inserting these std::cout statements here so you can see how fast it shifts
		// between the LoginScreen and RegisterScreen
		std::cout << "switched to LoginScreen" << std::endl;
		break;
	case REGISTER:
		currentScreen = new RegisterScreen();
		std::cout << "switched to RegisterScreen" << std::endl;
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