#include "CursorHandler.hpp"

CursorHandler::CursorHandler(int sw, int sh, int ww, int wh)
{
	xBoundary = (ww / 2 - sw / 2);
	yBoundary =	(wh / 2 - sh / 2);
	screenWidth = sw-25;
	screenHeight = sh-25;
	//inital set up for main square
	mainSquare.setSize(sf::Vector2f(25, 25));
	mainSquare.setFillColor(sf::Color::Transparent);
	mainSquare.setPosition(ww/2, wh/2);
	mainSquare.setOutlineThickness(-3);
	mainSquare.setOutlineColor(sf::Color::Black);
	//initial set up for right square
	rightSquare.setSize(sf::Vector2f(25, 25));
	rightSquare.setFillColor(sf::Color::Transparent);
	rightSquare.setPosition(ww / 2+25, wh / 2);
	rightSquare.setOutlineThickness(-3);
	rightSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//inital set up for left square
	leftSquare.setSize(sf::Vector2f(25, 25));
	leftSquare.setFillColor(sf::Color::Transparent);
	leftSquare.setPosition(ww / 2 - 25, wh / 2);
	leftSquare.setOutlineThickness(-3);
	leftSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//initial set up for top square
	topSquare.setSize(sf::Vector2f(25, 25));
	topSquare.setFillColor(sf::Color::Transparent);
	topSquare.setPosition(ww / 2, wh / 2 + 25);
	topSquare.setOutlineThickness(-3);
	topSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//initial set up for bottom square
	bottomSquare.setSize(sf::Vector2f(25, 25));
	bottomSquare.setFillColor(sf::Color::Transparent);
	bottomSquare.setPosition(ww / 2, wh / 2 - 25);
	bottomSquare.setOutlineThickness(-3);
	bottomSquare.setOutlineColor(sf::Color(0, 0, 0, 200));

}


void CursorHandler::Left(sf::Keyboard::Key L)
{
	if (mainSquare.getPosition().x > xBoundary)
	{
		mainSquare.setPosition(mainSquare.getPosition().x - 25, mainSquare.getPosition().y);
		leftSquare.setPosition(leftSquare.getPosition().x - 25, leftSquare.getPosition().y);
		rightSquare.setPosition(rightSquare.getPosition().x - 25, rightSquare.getPosition().y);
		topSquare.setPosition(topSquare.getPosition().x - 25, topSquare.getPosition().y);
		bottomSquare.setPosition(bottomSquare.getPosition().x - 25, bottomSquare.getPosition().y);
	}
}

void CursorHandler::Right(sf::Keyboard::Key R)
{
	if (mainSquare.getPosition().x < xBoundary+screenWidth)
	{
		mainSquare.setPosition(mainSquare.getPosition().x + 25, mainSquare.getPosition().y);
		leftSquare.setPosition(leftSquare.getPosition().x + 25, leftSquare.getPosition().y);
		rightSquare.setPosition(rightSquare.getPosition().x + 25, rightSquare.getPosition().y);
		topSquare.setPosition(topSquare.getPosition().x + 25, topSquare.getPosition().y);
		bottomSquare.setPosition(bottomSquare.getPosition().x + 25, bottomSquare.getPosition().y);
	}
}

void CursorHandler::Up(sf::Keyboard::Key U)
{
	if (mainSquare.getPosition().y > yBoundary)
	{
		mainSquare.setPosition(mainSquare.getPosition().x, mainSquare.getPosition().y - 25);
		leftSquare.setPosition(leftSquare.getPosition().x, leftSquare.getPosition().y - 25);
		rightSquare.setPosition(rightSquare.getPosition().x, rightSquare.getPosition().y - 25);
		topSquare.setPosition(topSquare.getPosition().x, topSquare.getPosition().y - 25);
		bottomSquare.setPosition(bottomSquare.getPosition().x, bottomSquare.getPosition().y - 25);
	}
}

void CursorHandler::Down(sf::Keyboard::Key D)
{
	if (mainSquare.getPosition().y < yBoundary+screenHeight)
	{
		mainSquare.setPosition(mainSquare.getPosition().x, mainSquare.getPosition().y + 25);
		leftSquare.setPosition(leftSquare.getPosition().x, leftSquare.getPosition().y + 25);
		rightSquare.setPosition(rightSquare.getPosition().x, rightSquare.getPosition().y + 25);
		topSquare.setPosition(topSquare.getPosition().x, topSquare.getPosition().y + 25);
		bottomSquare.setPosition(bottomSquare.getPosition().x, bottomSquare.getPosition().y + 25);
	}
}

sf::RectangleShape CursorHandler::getMainCursor()
{
	return mainSquare;
}

sf::RectangleShape CursorHandler::getRightCursor()
{
	return rightSquare;
}

sf::RectangleShape CursorHandler::getLeftCursor()
{
	return leftSquare;
}

sf::RectangleShape CursorHandler::getTopCursor()
{
	return topSquare;
}
sf::RectangleShape CursorHandler::getBottomCursor()
{
	return bottomSquare;
}