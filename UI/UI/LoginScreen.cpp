#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"
#include "GraphicsManager.hpp"
#include <iostream>

LoginScreen::LoginScreen()
	:registerButton(Button(RegisterScreen(),
						   sf::RectangleShape(sf::Vector2f(200.0f, 200.0f)),
						   sf::Text(sf::String("Register"), 
								    GraphicsManager::labelFont,
								    GraphicsManager::labelSize)))
{
	GraphicsManager::setCenter(registerButton.boundingRect, sf::Vector2f(GraphicsManager::window.getSize())/2.0f);
	registerButton.boundingRect.setFillColor(GraphicsManager::buttonColor);
	GraphicsManager::setCenter(registerButton.label, GraphicsManager::getCenter(registerButton.boundingRect));
	registerButton.label.setColor(GraphicsManager::labelColor);

	std::cout << registerButton.label.getPosition().x << " " << registerButton.label.getPosition().y << std::endl;
	std::cout << registerButton.label.getCharacterSize() << std::endl;

	sf::Color temp = registerButton.boundingRect.getFillColor();
	std::cout << (float) temp.r << " " << (float) temp.g << " " << (float) temp.b << std::endl;
	temp = registerButton.label.getColor();
	std::cout << (float) temp.r << " " << (float) temp.g << " " << (float) temp.b << std::endl;
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