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
#include "CloseScreen.hpp"
#include "OfflineCloseScreen.hpp"
#include "MultiplayerScreen.hpp"
#include "NetworkedSinglePlayer.h"
#include "Game.hpp"

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
                                             { Screens::OFFLINERESULT, new OfflineResultScreen() },
                                             { Screens::CLOSE, new CloseScreen() },
                                             { Screens::OFFLINECLOSE, new OfflineCloseScreen() },
                                             { Screens::MULTIPLAYER, new MultiplayerScreen() },
											 { Screens::ONLINESINGLE, new NetworkedSinglePlayer()}
	                                     };

	// Set this to something else if you want to start on a specific screen
    currentScreens = { screens[Screens::LOGIN] };

	//set the initialPosition of the window
	view = GraphicsManager::getInstance()->window.getDefaultView();
}

void ScreenManager::update()
{
    // Only update the most recently added screen
	currentScreens[currentScreens.size() - 1]->update();

	
	//screen shake
	if (shakeTimer.asMilliseconds() > 0)
	{
		view = GraphicsManager::getInstance()->window.getDefaultView();
		view.setCenter(sf::Vector2f(view.getCenter().x + rand() % 5, view.getCenter().y + rand() % 5));
		GraphicsManager::getInstance()->window.setView(view);
		shakeTimer -= clock.getElapsedTime();
	}
	else{
		GraphicsManager::getInstance()->window.setView(GraphicsManager::getInstance()->window.getDefaultView());
	}
	clock.restart();
}

void ScreenManager::draw()
{
    currentScreens[0]->draw();

    if(currentScreens.size() > 1)
    {
        for(int i = 1; i < currentScreens.size() - 1; i++)
        {
            currentScreens[i]->draw();
        }
        // Used to provide a darkening layer between the last layer
        // and the layers before it
        sf::RectangleShape darken(sf::Vector2f((float) GraphicsManager::getInstance()->window.getSize().x,
                                               (float) GraphicsManager::getInstance()->window.getSize().y));
        darken.setFillColor(sf::Color(0, 0, 0, 255/2));
        GraphicsManager::getInstance()->window.draw(darken);

        currentScreens[currentScreens.size() - 1]->draw();
    }
}

void ScreenManager::switchScreen(const Screens toScreen)
{	
    currentScreens = { screens[toScreen] };

    // Deselects any selected elements before going to a new screen
    for(auto& screen : currentScreens)
        screen->deselect();

    for(auto& screen : currentScreens)
        screen->deactivate();
	
}

// For adding a notification screen or a close screen on top of the
// current one
void ScreenManager::addScreen(const Screens toScreen)
{
    currentScreens.push_back(screens[toScreen]);

    for(auto& screen : currentScreens)
        screen->deselect();

    for(auto& screen : currentScreens)
        screen->deactivate();
}

// Removes the last screen
void ScreenManager::popScreen()
{
    currentScreens.pop_back();
}

void ScreenManager::shake(int seconds)
{
	shakeTimer = sf::seconds(seconds);
}

// Does the necessary things for closing the game
void ScreenManager::closeGame()
{
    Game::isRunning = false;
    ClientManager::getInstance().closeConnection();
}