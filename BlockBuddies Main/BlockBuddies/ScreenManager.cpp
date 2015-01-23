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
    switchScreen(Screens::LOGIN);

	//set the initialPosition of the window
	view = GraphicsManager::getInstance()->window.getDefaultView();
}

void ScreenManager::update()
{
    int removeIndex = -1;
    // Loops backwards so we can check updates for the top screens first
    for(int i = currentScreens.size() - 1; i >= 0; i--)
    {
        if(currentScreens[i]->fade.state == FadeStates::FADED_IN)
            currentScreens[i]->update();
        // Sets index of fade out
        else if(currentScreens[i]->fade.state == FadeStates::FADED_OUT)
            removeIndex = i;
    }

    // Removes faded out elements, doesn't matter if this only removes
    // one at a time per loop
    //
    // Also, we must remove after the loop so we don't mess up indexing
    if(removeIndex != -1)
        currentScreens.erase(currentScreens.begin() + removeIndex);

	//screen shake
	if (shakeTimer.asMilliseconds() > 0)
	{
		view = GraphicsManager::getInstance()->window.getDefaultView();
		view.setCenter(sf::Vector2f(view.getCenter().x + rand() % 5 - 2.5f, view.getCenter().y + rand() % 5 - 2.5f));
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
    for (int i = 0; i < currentScreens.size(); i++)
        currentScreens[i]->draw();
}

void ScreenManager::switchScreen(const Screens toScreen)
{	
    screens[toScreen]->fade.state = FadeStates::FADING_IN;

    // Add to the front, as the back will disappear
    currentScreens.push_front(screens[toScreen]);

    // Deselects and deactivate any selected elements before going to a new screen
    for(auto& screen : currentScreens)
    {
        screen->deselect();
        screen->deactivate();

        // Start fading out
        if(screen->fade.state == FadeStates::FADED_IN)
            screen->fade.state = FadeStates::FADING_OUT;
    }
}

// For adding a notification screen or a close screen on top of the
// current one
void ScreenManager::addScreen(const Screens toScreen)
{
    screens[toScreen]->fade.state = FadeStates::FADING_IN;

    currentScreens.push_back(screens[toScreen]);

    for(auto& screen : currentScreens)
    {
        screen->deselect();
        screen->deactivate();
    }
}

void ScreenManager::shake(float seconds)
{
	shakeTimer = sf::seconds(seconds);
}

// Does the necessary things for closing the game
void ScreenManager::closeGame()
{
    Game::getInstance()->isRunning = false;
    if(ClientManager::getInstance().isConnected)
        ClientManager::getInstance().closeConnection();
}