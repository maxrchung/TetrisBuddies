#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"
#include "GraphicsManager.hpp"

LoginScreen::LoginScreen()
	// Note that the posX and posY parameters correspond to moving the button
	// a certain distance away relative to the center of the screen
	:registerButton(Button(new RegisterScreen(),
						   0.0f,
						   200.0f,
						   150.0f,
						   75.0f,
						   "Register"))
{
}

void LoginScreen::update()
{
	registerButton.update();
}

void LoginScreen::draw()
{
	// You can sort of ignore these two segments here under draw(). 
	// These are just to temporarily draw the background panes.
	// In the future, it would be nice to have a Section/Pane class that 
	// are initialized above to take care of these rects.
	sf::RectangleShape r(sf::Vector2f(400 * GraphicsManager::getInstance()->scale, 600 * GraphicsManager::getInstance()->scale));
	r.setOrigin(GraphicsManager::getInstance()->getCenter(r));
	r.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize())/2.0f);
	r.setFillColor(GraphicsManager::getInstance()->sectionColor);
	GraphicsManager::getInstance()->window.draw(r);

	sf::RectangleShape r2(sf::Vector2f(150, 75));
	r2.setOrigin(GraphicsManager::getInstance()->getCenter(r2));
	r2.setFillColor(GraphicsManager::getInstance()->sectionColor);
	r2.setPosition(sf::Vector2f(GraphicsManager::getInstance()->window.getSize())/2.0f);
	r2.move(0, 220 * GraphicsManager::getInstance()->scale);
	r2.setScale(GraphicsManager::getInstance()->scale, GraphicsManager::getInstance()->scale);
	GraphicsManager::getInstance()->window.draw(r2);

	registerButton.draw();
}