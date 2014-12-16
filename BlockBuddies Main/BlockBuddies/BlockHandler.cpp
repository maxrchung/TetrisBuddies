#include "BlockHandler.hpp"

int BlockHandler::displayScore = 0;

//takes in window width and window height
BlockHandler::BlockHandler(int ww, int wh)
	:windowHeight(wh), windowWidth(ww), gridPosx(0), gridPosy(0), gameOver(false), clearBlocks(false), coloredBlock(false)
{
	int color = 0;
	//creates blocks and puts them in 2D array
	for (int i = 0; i < SCREENHEIGHT; i += 25)
	{
		for (int j = 0; j < SCREENWIDTH; j += 25)
		{
			sf::RectangleShape shape(sf::Vector2f(25, 25));
			shape.setPosition(j+(ww/2 - SCREENWIDTH/2), i+(wh/2 - SCREENHEIGHT/2)); //puts it in the middle of the screen

			if (i < 250)
			{
				shape.setFillColor(sf::Color::Transparent); //transparent blocks to appear as empty space
			}
			else
			{
				//random the block colors
				color = rand() % 5;
				switch (color)
				{
				case 0:
					shape.setFillColor(sf::Color::Green);
					break;
				case 1:
					shape.setFillColor(sf::Color::Blue);
					break;
				case 2:
					shape.setFillColor(sf::Color::Red);
					break;
				case 3:
					shape.setFillColor(sf::Color::Magenta);
					break;
				case 4:
					shape.setFillColor(sf::Color::Yellow);
					break;
				default:
					break;
				}
			}
			blocks[gridPosx][gridPosy] = shape;
			gridPosy++;
		}
		gridPosy = 0;
		gridPosx++;
	}

	checkEverything();
	score = 0;
}



sf::RectangleShape BlockHandler::getBlocks(int posx, int posy)
{
	return blocks[posy][posx]; //returns the block at that position
}

//swaps the main block with the top block
void BlockHandler::swapBlocksVertT(int x, int y)
{
	int mainblockx = (x - (windowWidth / 2 - SCREENWIDTH / 2)) / 25;
	int mainblocky = (y - (windowHeight / 2 - SCREENHEIGHT / 2)) / 25;
	int topblockx = mainblockx;
	int topblocky = mainblocky--;
	 
	//Dont swap at top or if the block above is transparent.
	if (mainblocky >= 0 && blocks[mainblocky][mainblockx].getFillColor() != sf::Color::Transparent)
	{
		sf::RectangleShape temp = blocks[mainblocky][mainblockx];
		blocks[mainblocky][mainblockx].setFillColor(blocks[topblocky][topblockx].getFillColor());
		blocks[topblocky][topblockx].setFillColor(temp.getFillColor());
		checkBlocks(mainblockx, mainblocky);  //checks if any blocks are matching after a swap
	}

}

//swaps the main block with the botom block
void BlockHandler::swapBlocksVertB(int x, int y)
{
	int mainblockx = (x - (windowWidth / 2 - SCREENWIDTH / 2)) / 25;
	int mainblocky = (y - (windowHeight / 2 - SCREENHEIGHT / 2)) / 25;
	int botblockx = mainblockx;
	int botblocky = mainblocky++;

	//Dont swap at bottom or if the block below is transparent
	if ( mainblocky < SCREENHEIGHT/25 && blocks[botblocky][botblockx].getFillColor() != sf::Color::Transparent)
	{
		sf::RectangleShape temp = blocks[mainblocky][mainblockx];
		blocks[mainblocky][mainblockx].setFillColor(blocks[botblocky][botblockx].getFillColor());
		blocks[botblocky][botblockx].setFillColor(temp.getFillColor());
		checkBlocks(mainblockx, mainblocky);  //checks if any blocks are matching after a swap
	}

}

//swaps the main block with the left block
void BlockHandler::swapBlocksHorizL(int x, int y)
{
	int mainblockx = (x - (windowWidth / 2 - SCREENWIDTH / 2)) / 25;
	int mainblocky = (y - (windowHeight / 2 - SCREENHEIGHT / 2)) / 25;
	int leftblockx = mainblockx--;
	int leftblocky = mainblocky;

	//Dont swap on left edge
	if (mainblockx >= 0)
	{
		sf::RectangleShape temp = blocks[mainblocky][mainblockx];
		blocks[mainblocky][mainblockx].setFillColor(blocks[leftblocky][leftblockx].getFillColor());
		blocks[leftblocky][leftblockx].setFillColor(temp.getFillColor());
		//if you want to drop blocks from a higher column to a lower one.
		if (blocks[mainblocky][mainblockx].getFillColor() == sf::Color::Transparent || blocks[leftblocky][leftblockx].getFillColor() == sf::Color::Transparent)
			dropBlocks();
		checkBlocks(mainblockx, mainblocky);  //checks if any blocks are matching after a swap
	}

}

//swaps the main block with the right block
void BlockHandler::swapBlocksHorizR(int x, int y)
{
	int mainblockx = (x - (windowWidth / 2 - SCREENWIDTH / 2)) / 25;
	int mainblocky = (y - (windowHeight / 2 - SCREENHEIGHT / 2)) / 25;
	int rightblockx = mainblockx++;
	int rightblocky = mainblocky;

	//dont swap on right edge
	if (mainblockx < SCREENWIDTH/25)
	{
		sf::RectangleShape temp = blocks[mainblocky][mainblockx];
		blocks[mainblocky][mainblockx].setFillColor(blocks[rightblocky][rightblockx].getFillColor());
		blocks[rightblocky][rightblockx].setFillColor(temp.getFillColor());
		//if you want to drop blocks from a higher column to a lower one.
		if (blocks[mainblocky][mainblockx].getFillColor() == sf::Color::Transparent || blocks[rightblocky][rightblockx].getFillColor() == sf::Color::Transparent)
			dropBlocks();
		checkBlocks(mainblockx, mainblocky);  //checks if any blocks are matching after a swap
	}

}

//checks if any of the blocks are matching in at least 3
void BlockHandler::checkBlocks(int x, int y)
{

	check(x, y); //checks Middle part of cursor
	check(x - 1, y); //checks left part of cursor
	check(x + 1, y); //checks right part of cursor
	check(x, y - 1); //checks top part of cursor
	check(x, y + 1); //checks bottom part of cursor

	if (clearBlocks == true)
	{
		while (!columns.empty() && !rows.empty())
		{
			//if the game somehow gets a value larger than the gamescreen size, throw it away.
			if (columns.front() >= SCREENHEIGHT / 25 || rows.front() >= SCREENWIDTH /25)
			{
				columns.pop(); rows.pop();
			}
			else
			{
				blocks[columns.front()][rows.front()].setFillColor(sf::Color::Transparent);
				columns.pop(); rows.pop();
			}
		}
		clearBlocks = false;
		dropBlocks();
	}
}

void BlockHandler::check(int x, int y)
{
	//only check blocks that arent empty
	if (blocks[y][x].getFillColor() != sf::Color::Transparent)
	{
		//checks 1 right and 1 left of it, the first line are constraints to prevent line wrap clearing
		if (x > 0 && x < SCREENWIDTH / 25 - 1 &&
			blocks[y][x].getFillColor() == blocks[y][x + 1].getFillColor() && blocks[y][x].getFillColor() == blocks[y][x - 1].getFillColor())
		{
			columns.push(y); columns.push(y); columns.push(y);
			rows.push(x); rows.push(x + 1); rows.push(x - 1);
			clearBlocks = true;
			score += 50;
			//check the 2nd right and 2nd left
			if (x < SCREENWIDTH / 25 - 2 && blocks[y][x].getFillColor() == blocks[y][x + 2].getFillColor())
			{
				columns.push(y);
				rows.push(x + 2);
				score += 20;
			}
			if (x > 1 && blocks[y][x].getFillColor() == blocks[y][x - 2].getFillColor())
			{
				columns.push(y);
				rows.push(x - 2);
				score += 20;
			}
		}
		//check the right side for match 3
		else if (x < SCREENWIDTH / 25 - 2 && blocks[y][x].getFillColor() == blocks[y][x + 1].getFillColor() && blocks[y][x].getFillColor() == blocks[y][x + 2].getFillColor())
		{
			columns.push(y); columns.push(y); columns.push(y);
			rows.push(x); rows.push(x + 1); rows.push(x + 2);
			clearBlocks = true;
			score += 50;
		}
		//check left side for match 3
		else if (x > 1 && blocks[y][x].getFillColor() == blocks[y][x - 1].getFillColor() && blocks[y][x].getFillColor() == blocks[y][x - 2].getFillColor())
		{
			columns.push(y); columns.push(y); columns.push(y);
			rows.push(x); rows.push(x - 1); rows.push(x - 2);
			clearBlocks = true;
			score += 50;
		}
		
		//checks 1 block above and 1 block below
		if (blocks[y][x].getFillColor() == blocks[y + 1][x].getFillColor() && blocks[y][x].getFillColor() == blocks[y - 1][x].getFillColor())
		{
			columns.push(y); columns.push(y + 1); columns.push(y - 1);
			rows.push(x); rows.push(x); rows.push(x);
			clearBlocks = true;
			score += 50;
			//check the 2nd above and 2nd below
			if (blocks[y][x].getFillColor() == blocks[y + 2][x].getFillColor())
			{
				columns.push(y + 2);
				rows.push(x);
				score += 20;
			}
			if (blocks[y][x].getFillColor() == blocks[y - 2][x].getFillColor())
			{
				columns.push(y - 2);
				rows.push(x);
				score += 20;
			}
		}
		//check the top for match 3
		else if (blocks[y][x].getFillColor() == blocks[y + 1][x].getFillColor() && blocks[y][x].getFillColor() == blocks[y + 2][x].getFillColor())
		{
			columns.push(y); columns.push(y + 1); columns.push(y + 2);
			rows.push(x); rows.push(x); rows.push(x);
			clearBlocks = true;
			score += 50;
		}
		//check bottom for match 3
		else if (blocks[y][x].getFillColor() == blocks[y - 1][x].getFillColor() && blocks[y][x].getFillColor() == blocks[y - 2][x].getFillColor())
		{
			columns.push(y); columns.push(y - 1); columns.push(y - 2);
			rows.push(x); rows.push(x); rows.push(x);
			clearBlocks = true;
			score += 50;
		}
	}
}

//block drop only for when blocks are cleared.
void BlockHandler::dropBlocks()
{
	int tempColumn = 0; //variable to move up in the columns to do multiple block drops
	for (int i = (SCREENHEIGHT / 25 - 1); i > 0; i--)
	{
		tempColumn = i;
		for (int j = 0; j < (SCREENWIDTH / 25); j++)
		{
			if (isThereColoredBlock(i, j))
			{
				while (blocks[i][j].getFillColor() == sf::Color::Transparent)
				{
					tempColumn--;
					//set the block to the block above it's color
					blocks[i][j].setFillColor(blocks[tempColumn][j].getFillColor());
					//set the block above to transparent
					blocks[tempColumn][j].setFillColor(sf::Color::Transparent);
				}
				coloredBlock = false; //reset if there is a colored block
			}
			tempColumn = i; // set the temp column back 
		}
	}

	//after the blocks drop, check the whole grid for any matches
	 checkEverything();
}

//checks whole grid for matches
void BlockHandler::checkEverything()
{
	for (int y = 0; y < (SCREENHEIGHT / 25); y++)
	{
		for (int x = 0; x < (SCREENWIDTH / 25); x++)
		{
			check(x,y);
		}
	}

	if (clearBlocks == true)
	{
		while (!columns.empty() && !rows.empty())
		{
			//if the game somehow gets a value larger than the gamescreen size, throw it away.
			if (columns.front() >= SCREENHEIGHT / 25 || rows.front() >= SCREENWIDTH / 25)
			{
				columns.pop(); rows.pop();
			}
			else
			{
				blocks[columns.front()][rows.front()].setFillColor(sf::Color::Transparent);
				columns.pop(); rows.pop();
			}
		}
		clearBlocks = false;
		dropBlocks();
	}
}


//finds the highest block
void BlockHandler::findHighestBlock()
{
	for (int i = 0; i < (SCREENHEIGHT / 25); i++)
	{
		for (int j = 0; j < (SCREENWIDTH / 25); j++)
		{
			if (highestBlock == 0)
			{
				if (blocks[i][j].getFillColor() != sf::Color::Transparent)
				{
					highestBlock = i;
				}
			}
		}
	}
}

//checks if there are colored blocks in the column to see if it needs to do block drop.
bool BlockHandler::isThereColoredBlock(int column, int row)
{
	for (int i = column; i > 0; i--)
	{
		if (blocks[i][row].getFillColor() != sf::Color::Transparent)
		{
			coloredBlock = true;
		}
	}

	return coloredBlock;
}

//creates a new line of blocks at the bottom
void BlockHandler::raiseBlocks()
{
	//moves all the blocks up by one
	for (int i = 0; i < (SCREENHEIGHT / 25 - 1); i++)
	{
		for (int j = 0; j < (SCREENWIDTH / 25); j++)
		{
			blocks[i][j].setFillColor(blocks[i + 1][j].getFillColor());
		}
	}

	for (int k = 0; k < (SCREENWIDTH / 25); k++)
	{
		//random the block colors
		int color = rand() % 5;
		switch (color)
		{
		case 0:
			blocks[SCREENHEIGHT / 25 - 1][k].setFillColor(sf::Color::Green);
			break;
		case 1:
			blocks[SCREENHEIGHT / 25 - 1][k].setFillColor(sf::Color::Blue);
			break;
		case 2:
			blocks[SCREENHEIGHT / 25 - 1][k].setFillColor(sf::Color::Red);
			break;
		case 3:
			blocks[SCREENHEIGHT / 25 - 1][k].setFillColor(sf::Color::Magenta);
			break;
		case 4:
			blocks[SCREENHEIGHT / 25 - 1][k].setFillColor(sf::Color::Yellow);
			break;
		default:
			break;
		}
	}

	//check for matches once a new line comes in
	checkEverything();
}

bool BlockHandler::GameOver()
{
	for (int i = 0; i < SCREENWIDTH / 25; i++)
	{
		if (blocks[0][i].getFillColor() != sf::Color::Transparent)
			gameOver = true;
	}

	return gameOver;
}

