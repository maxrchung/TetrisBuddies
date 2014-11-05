#include "Game.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "LoginScreen.hpp"
#include "UIManager.hpp"
#include "InputManager.hpp"

bool Game::isRunning = true;

Game::Game()
{
	// Initialize the singletons
	// Note that UIManager must call init() first or it'll reset all the 
	// UIElements to zero
	UIManager::getInstance()->init();
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

	// The UIManager handles all the textboxes, buttons, and text inputs
	// on the screen
	UIManager::getInstance()->update();

	// After inputs and UIElements and updated, we update the screen
	// This will involve bigger picture actions such as sending
	// network messages if we need to
	ScreenManager::getInstance()->currentScreen->update();
}

void Game::draw()
{
	// Clears what's on the window from the last draw
	GraphicsManager::getInstance()->window.clear();

	// Background always the same, so drawn here, followed by allowing the
	// currentScreen to take control and draw as it likes
	GraphicsManager::getInstance()->window.draw(GraphicsManager::getInstance()->background);

	// Display all the UIElements
	UIManager::getInstance()->draw();

	// Draw everything that we've since prepped onto the window
	GraphicsManager::getInstance()->window.display();
}