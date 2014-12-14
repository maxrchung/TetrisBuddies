#ifndef CURSORHANDLER_HPP
#define CURSORHANDLER_HPP

#include "SFML/Graphics.hpp"

class CursorHandler
{
public:
	CursorHandler(int, int, int, int, int, int);
	void Left(sf::Keyboard::Key L);
	void Right(sf::Keyboard::Key R);
	void Up(sf::Keyboard::Key U);
	void Down(sf::Keyboard::Key D);
	int getCursorX();
	int getCursorY();
	sf::RectangleShape getMainCursor();
	sf::RectangleShape getLeftCursor();
	sf::RectangleShape getRightCursor();
	sf::RectangleShape getTopCursor();
	sf::RectangleShape getBottomCursor();
	int blockSize;
private:
	int xBoundary,yBoundary,screenWidth, screenHeight, originX, originY;
	sf::RectangleShape mainSquare;
	sf::RectangleShape leftSquare;
	sf::RectangleShape rightSquare;
	sf::RectangleShape topSquare;
	sf::RectangleShape bottomSquare;
	
};
#endif CURSORHANDLER_HPP
