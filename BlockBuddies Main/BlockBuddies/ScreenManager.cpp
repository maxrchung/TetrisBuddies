#include "ScreenManager.hpp"
#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"
#include "HomeScreen.hpp"
#include "ProfileScreen.hpp"
#include "GameTypeScreen.hpp"
#include "GameScreen.hpp"
#include "ResultScreen.hpp"
#include "InputManager.hpp"
#include "OfflineHomeScreen.hpp"
#include "OfflineGameTypeScreen.hpp"
#include "OfflineResultScreen.hpp"

ScreenManager* ScreenManager::instance;

ScreenManager* ScreenManager::getInstance()
{
	if(!instance)
		instance = new ScreenManager;
	return instance;
}

void ScreenManager::init()
{
	// Initialize all the screens to a map
	screens = std::map<Screens, Screen*> { 
		                                     { Screens::LOGIN, new LoginScreen() },
											 { Screens::REGISTER, new RegisterScreen() },
											 { Screens::HOME, new HomeScreen() },
											 { Screens::PROFILE, new ProfileScreen() },
											 { Screens::GAMETYPE, new GameTypeScreen() },
											 { Screens::GAME, new GameScreen() },
											 { Screens::RESULT, new ResultScreen() },
                                             { Screens::OFFLINEHOME, new OfflineHomeScreen() },
                                             { Screens::OFFLINEGAMETYPE, new OfflineGameTypeScreen() },
                                             { Screens::OFFLINERESULT, new OfflineResultScreen() }
	                                     };

	// Set this to something else if you want to start on a specific screen
	currentScreen = screens[Screens::OFFLINERESULT];
}

void ScreenManager::update()
{
	currentScreen->update();
}

void ScreenManager::draw()
{
	currentScreen->draw();
}

void ScreenManager::switchScreen(const Screens toScreen)
{	
	// Turn this false so that it doesn't get improperly read for future
	// switchScreen calculations
	InputManager::getInstance()->mouseReleased = false;

    // Deselects any selected elements before going to a new screen
    currentScreen->deselect();
	
	currentScreen = screens[toScreen];
}