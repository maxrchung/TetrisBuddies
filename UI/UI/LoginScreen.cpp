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
	registerButton.boundingRect.setFillColor(GraphicsManager::buttonColor);
	GraphicsManager::setCenter(registerButton.label, GraphicsManager::getCenter(registerButton.boundingRect));
	registerButton.label.setColor(GraphicsManager::labelColor);
}

LoginScreen::~LoginScreen()
{
}

void LoginScreen::update()
{
	registerButton.update();
}

void LoginScreen::draw()
{
	registerButton.draw();
}