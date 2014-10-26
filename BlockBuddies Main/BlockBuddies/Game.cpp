#include "Game.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "LoginScreen.hpp"

Game::Game()
{
	// Initialize the singletons
	GraphicsManager::getInstance()->init();
	ScreenManager::getInstance()->init();
}

void Game::run() 
{
	update();
	draw();
}

void Game::update()
{
	// Gives control over to the currentScreen to update its tasks
	ScreenManager::getInstance()->currentScreen->update();
}

void Game::draw()
{
	// Clears what's on the window from the last draw
	GraphicsManager::getInstance()->window.clear();

	// Background always the same, so drawn here, followed by allowing the
	// currentScreen to take control and draw as it likes
	GraphicsManager::getInstance()->window.draw(GraphicsManager::getInstance()->background);
	ScreenManager::getInstance()->currentScreen->draw();

	// Draw everything that we've since prepped onto the window
	GraphicsManager::getInstance()->window.display();
}