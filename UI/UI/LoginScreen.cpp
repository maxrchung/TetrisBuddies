#include "LoginScreen.hpp"
#include "RegisterScreen.hpp"
#include "GraphicsManager.hpp"

LoginScreen::LoginScreen()
	:registerButton(Button(new RegisterScreen(),
						   sf::RectangleShape(sf::Vector2f(150.0f, 75.0f)),
						   sf::Text(sf::String("Register"),
								    GraphicsManager::labelFont,
								    GraphicsManager::labelSize)))
{
	registerButton.boundingRect.move(0, 200 * GraphicsManager::scale);
	registerButton.label.setPosition(registerButton.boundingRect.getPosition());
}

void LoginScreen::update()
{
	registerButton.update();
}

void LoginScreen::draw()
{
	sf::RectangleShape r(sf::Vector2f(400 * GraphicsManager::scale, 600 * GraphicsManager::scale));
	r.setOrigin(GraphicsManager::getCenter(r));
	r.setPosition(sf::Vector2f(GraphicsManager::window.getSize())/2.0f);
	r.setFillColor(GraphicsManager::sectionColor);
	GraphicsManager::window.draw(r);

	sf::RectangleShape r2(sf::Vector2f(150, 75));
	r2.setOrigin(GraphicsManager::getCenter(r2));
	r2.setFillColor(GraphicsManager::sectionColor);
	r2.setPosition(sf::Vector2f(GraphicsManager::window.getSize())/2.0f);
	r2.move(0, 220 * GraphicsManager::scale);
	r2.setScale(GraphicsManager::scale, GraphicsManager::scale);
	GraphicsManager::window.draw(r2);

	registerButton.draw();
}