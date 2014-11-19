#ifndef BLOCKHANDLER_HPP
#define BLOCKHANDLER_HPP


#include "SFML/Graphics.hpp"
#include <queue>
#include <ctime>

class BlockHandler
{
public:
	BlockHandler(int, int);
	sf::RectangleShape getBlocks(int, int);
	void swapBlocksVertT(int, int);
	void swapBlocksVertB(int, int);
	void swapBlocksHorizL(int, int);
	void swapBlocksHorizR(int, int);
	void checkBlocks(int, int);
	void raiseBlocks();
	void dropBlocks();
	void findHighestBlock();
	bool isThereColoredBlock(int, int);
	bool GameOver();
	const int SCREENWIDTH = 400;
	const int SCREENHEIGHT = 500;

private:
	sf::RectangleShape blocks[20][16];
	std::queue <int> rows;
	std::queue <int> columns;
	int windowWidth, windowHeight;
	int highestBlock;
	int gridPosx;
	int gridPosy;
	bool clearBlocks;
	bool coloredBlock;
	bool gameOver;
	void check(int x, int y);
};

#endif BLOCKHANDLER_HPP