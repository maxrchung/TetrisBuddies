#include "Game.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "LoginScreen.hpp"
#include "InputManager.hpp"
#include "ClientManager.h"
#include "BlockShowerManager.hpp"
#include "AnimationManager.hpp"

#include <iostream>

Game* Game::instance;

Game* Game::getInstance()
{
    if(!instance)
        instance = new Game();

    return instance;
}

void Game::init()
{
	// Initialize the singletons
	// Note that UIManager and SelectManager must call init() first or 
	// else making the new screen at ScreenManager will reset all the
	// elements
	GraphicsManager::getInstance()->init();
	ScreenManager::getInstance()->init();
	InputManager::getInstance()->init();
    BlockShowerManager::getInstance()->init();
	AnimationManager::getInstance()->init();

    cursorHideClock.restart();
    prevMousePos = sf::Mouse::getPosition();
}

void Game::run() 
{
	// I like having everything neatly separated into update() and draw()
	update();
	draw();
}

void Game::update()
{
    // Hides/shows the cursor
    cursorUpdate();

    //  Checks received packets and responds to them
    ClientManager::getInstance().update();

	// Resets inputs and checks for new ones
	InputManager::getInstance()->update();

    // Background shower animation update
    BlockShowerManager::getInstance()->update();

	// After inputs and UIElements and updated, we update the screen
	// This will involve bigger picture actions such as sending
	// network messages if we need to
	ScreenManager::getInstance()->update();
}

void Game::cursorUpdate()
{
    // Hides cursor
    cursorHideTimer += cursorHideClock.getElapsedTime().asSeconds();
    cursorHideClock.restart();

    if(prevMousePos != sf::Mouse::getPosition())
    {
        GraphicsManager::getInstance()->window.setMouseCursorVisible(true);
        cursorHideTimer = 0.0f;
    }

    if (cursorHideTimer > 3.0f)
    {
        GraphicsManager::getInstance()->window.setMouseCursorVisible(false);
    }

    prevMousePos = sf::Mouse::getPosition();
}

void Game::draw()
{
	// Clears what's on the window from the last draw with the background color and a border
	GraphicsManager::getInstance()->window.clear(GraphicsManager::getInstance()->backgroundColor);

    // Draws block shower background
    BlockShowerManager::getInstance()->draw();

	// This will usually be empty for Login/Register screen and the like, but GameScreen
	// will need this to draw things
	ScreenManager::getInstance()->draw();

	//AnimationManager draw gets called by update
	AnimationManager::getInstance()->update();

    // Draw everything that we've since prepped onto the window
	GraphicsManager::getInstance()->window.display();
}

// Call this function to start loading before you start blocking
void Game::startLoadingThread()
{
    isLoading = true;
    GraphicsManager::getInstance()->window.setActive(false);
    loadingThread = std::thread(&Game::loadingUpdate, this);
}

// While the game is loading, update the background block shower animation
// and draw everything without updating
void Game::loadingUpdate()
{
    // We need to do this odd setActive(true) and setActive(false)
    // because SFML doesn't like when we have a global sf::RenderWindow
    // that multiple threads are drawing to.
    //
    // Not a great fix, but it seems to not result in any problems, so
    // I'll take it I suppose. I think from what I read on forums, the
    // better design would be to simply avoid static/global variables
    // in general and pass the RenderWindow between classes and functions
    // that need it, but that would involve rewriting a lot of what we have
    GraphicsManager::getInstance()->window.setActive(true);

    while(isLoading)
    {
        if(frameLimiter.getElapsedTime().asMilliseconds() > 16.67f)
        {
            frameLimiter.restart();
            BlockShowerManager::getInstance()->update();
            draw();
        }
    }

    GraphicsManager::getInstance()->window.setActive(false);
}

void Game::stopLoadingThread()
{
    isLoading = false;
    loadingThread.join();
    GraphicsManager::getInstance()->window.setActive(true);
}