#include "CursorHandler.hpp"

//for single player
CursorHandler::CursorHandler(int sw, int sh, int ww, int wh)
{
	blockSize = 25;
	xBoundary = (ww / 2 - sw / 2);
	yBoundary =	(wh / 2 - sh / 2);
	screenWidth = sw - blockSize;
	screenHeight = sh - blockSize;

	//inital set up for main square
	mainSquare.setSize(sf::Vector2f(blockSize, blockSize));
	mainSquare.setFillColor(sf::Color::Transparent);
	mainSquare.setPosition(ww/2, wh/2);
	mainSquare.setOutlineThickness(-3);
	mainSquare.setOutlineColor(sf::Color::Black);
	//initial set up for right square
	rightSquare.setSize(sf::Vector2f(blockSize, blockSize));
	rightSquare.setFillColor(sf::Color::Transparent);
	rightSquare.setPosition(ww / 2 + blockSize, wh / 2);
	rightSquare.setOutlineThickness(-3);
	rightSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//inital set up for left square
	leftSquare.setSize(sf::Vector2f(blockSize, blockSize));
	leftSquare.setFillColor(sf::Color::Transparent);
	leftSquare.setPosition(ww / 2 - blockSize, wh / 2);
	leftSquare.setOutlineThickness(-3);
	leftSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//initial set up for top square
	topSquare.setSize(sf::Vector2f(blockSize, blockSize));
	topSquare.setFillColor(sf::Color::Transparent);
	topSquare.setPosition(ww / 2, wh / 2 + blockSize);
	topSquare.setOutlineThickness(-3);
	topSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//initial set up for bottom square
	bottomSquare.setSize(sf::Vector2f(blockSize, blockSize));
	bottomSquare.setFillColor(sf::Color::Transparent);
	bottomSquare.setPosition(ww / 2, wh / 2 - blockSize);
	bottomSquare.setOutlineThickness(-3);
	bottomSquare.setOutlineColor(sf::Color(0, 0, 0, 200));

}

//for multiplayer
CursorHandler::CursorHandler(int sw, int sh, int ww, int wh, int xStart, int yStart)
{
	ww = ww / 2 - sw; 
	wh = wh / 2;
	xBoundary = xStart;
	yBoundary = yStart;
	screenWidth = sw - blockSize;
	screenHeight = sh - blockSize;

	//inital set up for main square
	mainSquare.setSize(sf::Vector2f(blockSize, blockSize));
	mainSquare.setFillColor(sf::Color::Transparent);
	mainSquare.setPosition(ww , wh);
	mainSquare.setOutlineThickness(-3);
	mainSquare.setOutlineColor(sf::Color::Black);
	//initial set up for right square
	rightSquare.setSize(sf::Vector2f(blockSize, blockSize));
	rightSquare.setFillColor(sf::Color::Transparent);
	rightSquare.setPosition(ww + blockSize, wh);
	rightSquare.setOutlineThickness(-3);
	rightSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//inital set up for left square
	leftSquare.setSize(sf::Vector2f(blockSize, blockSize));
	leftSquare.setFillColor(sf::Color::Transparent);
	leftSquare.setPosition(ww - blockSize, wh);
	leftSquare.setOutlineThickness(-3);
	leftSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//initial set up for top square
	topSquare.setSize(sf::Vector2f(blockSize, blockSize));
	topSquare.setFillColor(sf::Color::Transparent);
	topSquare.setPosition(ww, wh + blockSize);
	topSquare.setOutlineThickness(-3);
	topSquare.setOutlineColor(sf::Color(0, 0, 0, 200));
	//initial set up for bottom square
	bottomSquare.setSize(sf::Vector2f(blockSize, blockSize));
	bottomSquare.setFillColor(sf::Color::Transparent);
	bottomSquare.setPosition(ww, wh - blockSize);
	bottomSquare.setOutlineThickness(-3);
	bottomSquare.setOutlineColor(sf::Color(0, 0, 0, 200));

}

void CursorHandler::Left(sf::Keyboard::Key L)
{
	if (mainSquare.getPosition().x > xBoundary)
	{
		mainSquare.setPosition(mainSquare.getPosition().x - blockSize, mainSquare.getPosition().y);
		leftSquare.setPosition(leftSquare.getPosition().x - blockSize, leftSquare.getPosition().y);
		rightSquare.setPosition(rightSquare.getPosition().x - blockSize, rightSquare.getPosition().y);
		topSquare.setPosition(topSquare.getPosition().x - blockSize, topSquare.getPosition().y);
		bottomSquare.setPosition(bottomSquare.getPosition().x - blockSize, bottomSquare.getPosition().y);
	}
}

void CursorHandler::Right(sf::Keyboard::Key R)
{
	if (mainSquare.getPosition().x < xBoundary+screenWidth)
	{
		mainSquare.setPosition(mainSquare.getPosition().x + blockSize, mainSquare.getPosition().y);
		leftSquare.setPosition(leftSquare.getPosition().x + blockSize, leftSquare.getPosition().y);
		rightSquare.setPosition(rightSquare.getPosition().x + blockSize, rightSquare.getPosition().y);
		topSquare.setPosition(topSquare.getPosition().x + blockSize, topSquare.getPosition().y);
		bottomSquare.setPosition(bottomSquare.getPosition().x + blockSize, bottomSquare.getPosition().y);
	}
}

void CursorHandler::Up(sf::Keyboard::Key U)
{
	if (mainSquare.getPosition().y > yBoundary)
	{
		mainSquare.setPosition(mainSquare.getPosition().x, mainSquare.getPosition().y - blockSize);
		leftSquare.setPosition(leftSquare.getPosition().x, leftSquare.getPosition().y - blockSize);
		rightSquare.setPosition(rightSquare.getPosition().x, rightSquare.getPosition().y - blockSize);
		topSquare.setPosition(topSquare.getPosition().x, topSquare.getPosition().y - blockSize);
		bottomSquare.setPosition(bottomSquare.getPosition().x, bottomSquare.getPosition().y - blockSize);
	}
}

void CursorHandler::Down(sf::Keyboard::Key D)
{
	if (mainSquare.getPosition().y < yBoundary+screenHeight)
	{
		mainSquare.setPosition(mainSquare.getPosition().x, mainSquare.getPosition().y + blockSize);
		leftSquare.setPosition(leftSquare.getPosition().x, leftSquare.getPosition().y + blockSize);
		rightSquare.setPosition(rightSquare.getPosition().x, rightSquare.getPosition().y + blockSize);
		topSquare.setPosition(topSquare.getPosition().x, topSquare.getPosition().y + blockSize);
		bottomSquare.setPosition(bottomSquare.getPosition().x, bottomSquare.getPosition().y + blockSize);
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