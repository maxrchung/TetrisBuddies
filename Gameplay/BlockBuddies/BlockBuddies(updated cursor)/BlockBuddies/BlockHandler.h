#ifndef BLOCKHANDLER_HPP
#define BLOCKHANDLER_HPP


#include "SFML/Graphics.hpp"
#include <list>
#include <ctime>

class BlockHandler
{
public:
	BlockHandler();
	sf::RectangleShape getBlocks(int,int);
	void swapBlocksVertT(int,int);
	void swapBlocksVertB(int, int);
	void swapBlocksHorizL(int,int);
	void swapBlocksHorizR(int, int);
	void checkBlocks(int, int);
	const int SCREENWIDTH = 400;
	const int SCREENHEIGHT = 500;

private:
	sf::RectangleShape blocks[20][16];
	std::list <int> rows;
	std::list <int> columns;
	int gridPosx;
	int gridPosy;
	bool clearBlocks;
	void checkMiddle(int x, int y);
	void checkLeft(int x, int y);
	void checkRight(int x, int y);
	void checkTop(int x, int y);
	void checkBottom(int x, int y);
};

#endif BLOCKHANDLER_HPP