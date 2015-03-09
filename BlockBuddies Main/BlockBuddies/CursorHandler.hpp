#ifndef CURSORHANDLER_HPP
#define CURSORHANDLER_HPP

#include "SFML/Graphics.hpp"

class CursorHandler
{
public:
	CursorHandler(int sw, int sh, int ww, int wh, int blockS, int offset);
	CursorHandler(sf::Vector2f orginPos, sf::Vector2f gameScreenPos, int gameScreenHeight, int gameScreenWidth, int blockS);
	CursorHandler(int sw, int sh, int ww, int wh, int xStart, int yStart, int blockS, int offset);
	void Left(sf::Keyboard::Key L);
	void Right(sf::Keyboard::Key R);
	void Up(sf::Keyboard::Key U);
	void Down(sf::Keyboard::Key D);
	void setCursorAt(int x, int y);
	void setCursorAt_v2(int x, int y);
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
	sf::Vector2f screenPos;
	sf::RectangleShape mainSquare;
	sf::RectangleShape leftSquare;
	sf::RectangleShape rightSquare;
	sf::RectangleShape topSquare;
	sf::RectangleShape bottomSquare;
	
};
#endif CURSORHANDLER_HPP
