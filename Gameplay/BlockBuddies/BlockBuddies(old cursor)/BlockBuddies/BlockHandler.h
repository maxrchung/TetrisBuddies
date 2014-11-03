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
	void swapBlocksVertL(int,int);
	void swapBlocksVertR(int, int);
	void swapBlocksHorizT(int,int);
	void swapBlocksHorizB(int, int);
	void checkBlocks(int, int);
	const int SCREENWIDTH = 400;
	const int SCREENHEIGHT = 500;

private:
	sf::RectangleShape blocks[20][20];
	std::list <int> rows;
	std::list <int> columns;
	int gridPosx;
	int gridPosy;
	bool clearBlocks;
	void checkVertL(int x, int y);
	void checkVertR(int x, int y);
	void checkHorizT(int x, int y);
	void checkHorizB(int x, int y);
};

#endif BLOCKHANDLER_HPP