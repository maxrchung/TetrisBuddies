#include "Game.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "LoginScreen.hpp"
#include "InputManager.hpp"

#include <iostream>

bool Game::isRunning = true;

Game::Game()
{
	// Initialize the singletons
	// Note that UIManager and SelectManager must call init() first or 
	// else making the new screen at ScreenManager will reset all the
	// elements
	GraphicsManager::getInstance()->init();
	ScreenManager::getInstance()->init();
	InputManager::getInstance()->init();
	//NetworkManager::getInstance()->init()
}

void Game::run() 
{
	// I like having everything neatly separated into update() and draw()
	update();
	draw();
}

void Game::update()
{
	// Resets inputs and checks for new ones
	InputManager::getInstance()->update();

	// After inputs and UIElements and updated, we update the screen
	// This will involve bigger picture actions such as sending
	// network messages if we need to
	ScreenManager::getInstance()->update();
}

void Game::draw()
{
	// Clears what's on the window from the last draw with the background color
	GraphicsManager::getInstance()->window.clear(GraphicsManager::getInstance()->backgroundColor);

	// This will usually be empty for Login/Register screen and the like, but GameScreen
	// will need this to draw things
	ScreenManager::getInstance()->draw();

	// Draw everything that we've since prepped onto the window
	GraphicsManager::getInstance()->window.display();
}