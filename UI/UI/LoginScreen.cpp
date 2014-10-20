#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"
#include "GraphicsManager.hpp"

LoginScreen::LoginScreen()
	:registerButton(Button(new RegisterScreen(),
						   sf::RectangleShape(sf::Vector2f(200.0f, 100.0f)),
						   sf::Text(sf::String("Register"),
								    GraphicsManager::labelFont,
								    GraphicsManager::labelSize)))
{
	GraphicsManager::setCenter(registerButton.boundingRect, sf::Vector2f(GraphicsManager::window.getSize())/2.0f);
	GraphicsManager::setCenter(registerButton.label, GraphicsManager::getCenter(registerButton.boundingRect));
}

void LoginScreen::update()
{
	registerButton.update();
}

void LoginScreen::draw()
{
	sf::RectangleShape r(sf::Vector2f(800, 600));
	GraphicsManager::setCenter(r, sf::Vector2f(GraphicsManager::window.getSize())/2.0f);
	r.setFillColor(GraphicsManager::sectionColor);
	GraphicsManager::window.draw(r);
	registerButton.draw();
}