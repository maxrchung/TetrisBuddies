#include "BlockHandler.h"

BlockHandler::BlockHandler()
{
	srand(time(NULL)); //random every run
	clearBlocks = false;
	gridPosx = 0;
	gridPosy = 0;
	int color = 0;

	//creates blocks and puts them in 2D array
	for (int i = 0; i < SCREENHEIGHT; i += 25)
	{
		for (int j = 0; j < SCREENWIDTH; j += 25)
		{
			sf::RectangleShape shape(sf::Vector2f(25, 25));
			shape.setPosition(j, i);

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

}



sf::RectangleShape BlockHandler::getBlocks(int posx, int posy)
{
	return blocks[posy][posx]; //returns the block at that position
}

//swaps the left vertical blocks in the cursor
void BlockHandler::swapBlocksVertL(int x, int y)
{
	int blockx = x/25;
	int blocky = y/25;

	sf::RectangleShape temp = blocks[blocky][blockx];
	blocks[blocky][blockx].setFillColor(blocks[blocky+1][blockx].getFillColor());
	blocks[blocky+1][blockx].setFillColor(temp.getFillColor());

	checkBlocks(blockx, blocky);  //checks if any blocks are matching after a swap
}

//swaps the right vertical blocks in the cursor
void BlockHandler::swapBlocksVertR(int x, int y)
{
	int blockx = x / 25;
	int blocky = y / 25;
	blockx++;

	sf::RectangleShape temp = blocks[blocky][blockx];
	blocks[blocky][blockx].setFillColor(blocks[blocky+1][blockx].getFillColor());
	blocks[blocky+1][blockx].setFillColor(temp.getFillColor());

	checkBlocks(blockx-1, blocky); //checks if any blocks are matching after a swap
}

//swaps the horizontal blocks in the top part of the cursor
void BlockHandler::swapBlocksHorizT(int x, int y)
{
	int blockx = x / 25;
	int blocky = y / 25;

	sf::RectangleShape temp = blocks[blocky][blockx];
	blocks[blocky][blockx].setFillColor(blocks[blocky][blockx + 1].getFillColor());
	blocks[blocky][blockx + 1].setFillColor(temp.getFillColor());

	checkBlocks(blockx, blocky);  //checks if any blocks are matching after a swap
}

//swaps the horizontal blocks in the bottom part of the cursor
void BlockHandler::swapBlocksHorizB(int x, int y)
{
	int blockx = x / 25;
	int blocky = y / 25;
	blocky++;

	sf::RectangleShape temp = blocks[blocky][blockx];
	blocks[blocky][blockx].setFillColor(blocks[blocky][blockx + 1].getFillColor());
	blocks[blocky][blockx + 1].setFillColor(temp.getFillColor());

	checkBlocks(blockx, blocky-1); //checks if any blocks are matching after a swap
}

//checks if any of the blocks are matching in at least 3
void BlockHandler::checkBlocks(int x, int y)
{
	checkVertL(x,y);
	checkVertR(x, y);
	checkHorizT(x, y);
	checkHorizB(x, y);	
	if (clearBlocks == true)
	{
		while (!columns.empty() && !rows.empty())
		{
			blocks[columns.back()][rows.back()].setFillColor(sf::Color::Transparent);
			columns.pop_back(); rows.pop_back();
		}
		clearBlocks = false;
	}
}


void BlockHandler::checkVertL(int x, int y)
{
	//checks for the upper left square if it matches with the sqare color above and below it
	if (blocks[y][x].getFillColor() == blocks[y+1][x].getFillColor() && blocks[y][x].getFillColor() == blocks[y-1][x].getFillColor())
	{
		columns.push_back(y); rows.push_back(x);
		columns.push_back(y + 1); rows.push_back(x);
		columns.push_back(y - 1); rows.push_back(x);
		clearBlocks = true;
		
		//checks if the 2nd block above the inital block has the same color
		if (blocks[y][x].getFillColor() == blocks[y+2][x].getFillColor())
			columns.push_back(y + 2); rows.push_back(x);

		//checks if the 2nd block below the inital block has the same color
		if (blocks[y][x].getFillColor() == blocks[y-2][x].getFillColor())
			columns.push_back(y - 2); rows.push_back(x);

	}
	//if the block doesnt match with top and bottom, check to see if it matches the 2 blocks below it
	else if (blocks[y][x].getFillColor() == blocks[y-1][x].getFillColor() && blocks[y][x].getFillColor() == blocks[y-2][x].getFillColor())
	{
		columns.push_back(y - 2); rows.push_back(x);
		columns.push_back(y - 1); rows.push_back(x);
		columns.push_back(y); rows.push_back(x);
		clearBlocks = true;
	}
	//if the block doesnt match with top and bottom, check to see if it matches the 2 blocks above it
	else if (blocks[y][x].getFillColor() == blocks[y+1][x].getFillColor() && blocks[y][x].getFillColor() == blocks[y+2][x].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x);
		columns.push_back(y + 2); rows.push_back(x);
		columns.push_back(y); rows.push_back(x);
		clearBlocks = true;
	}

	//Checks for vertical matching for bottom left square, similar code as above but start square is one lower.
	if (blocks[y+1][x].getFillColor() == blocks[y + 2][x].getFillColor() && blocks[y+1][x].getFillColor() == blocks[y][x].getFillColor())
	{
		columns.push_back(y); rows.push_back(x);
		columns.push_back(y + 1); rows.push_back(x);
		columns.push_back(y + 2); rows.push_back(x);
		clearBlocks = true;

		if (blocks[y+1][x].getFillColor() == blocks[y + 3][x].getFillColor())
			columns.push_back(y + 3); rows.push_back(x);

		if (blocks[y+1][x].getFillColor() == blocks[y - 1][x].getFillColor())
			columns.push_back(y - 1); rows.push_back(x);

	}
	else if (blocks[y+1][x].getFillColor() == blocks[y][x].getFillColor() && blocks[y+1][x].getFillColor() == blocks[y - 1][x].getFillColor())
	{
		columns.push_back(y - 1); rows.push_back(x);
		columns.push_back(y + 1); rows.push_back(x);
		columns.push_back(y); rows.push_back(x);
		clearBlocks = true;
	}
	else if (blocks[y+1][x].getFillColor() == blocks[y + 2][x].getFillColor() && blocks[y+1][x].getFillColor() == blocks[y + 3][x].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x);
		columns.push_back(y + 2); rows.push_back(x);
		columns.push_back(y+3); rows.push_back(x);
		clearBlocks = true;
	}

}

void BlockHandler::checkVertR(int x, int y)
{
	//checks for the upper right square if it matches with the sqare color above and below it
	if (blocks[y][x+1].getFillColor() == blocks[y + 1][x+1].getFillColor() && blocks[y][x+1].getFillColor() == blocks[y - 1][x + 1].getFillColor())
	{
		columns.push_back(y); rows.push_back(x + 1);
		columns.push_back(y + 1); rows.push_back(x + 1);
		columns.push_back(y - 1); rows.push_back(x + 1);
		clearBlocks = true;

		//checks to see if the 2nd block above the inital block matches
		if (blocks[y][x+1].getFillColor() == blocks[y + 2][x+1].getFillColor())
			columns.push_back(y + 2); rows.push_back(x + 1);

		//checks to see if the 2nd block below the inital block matches
		if (blocks[y][x+1].getFillColor() == blocks[y - 2][x+1].getFillColor())
			columns.push_back(y - 2); rows.push_back(x + 1);

	}
	//if the block doesnt match with top and bottom, check to see if it matches the 2 blocks below it
	else if (blocks[y][x+1].getFillColor() == blocks[y - 1][x+1].getFillColor() && blocks[y][x+1].getFillColor() == blocks[y - 2][x+1].getFillColor())
	{
		columns.push_back(y - 2); rows.push_back(x + 1);
		columns.push_back(y - 1); rows.push_back(x + 1);
		columns.push_back(y); rows.push_back(x + 1);
		clearBlocks = true;
	}
	//if the block doesnt match with top and bottom, check to see if it matches the 2 blocks above it
	else if (blocks[y][x+1].getFillColor() == blocks[y + 1][x+1].getFillColor() && blocks[y][x+1].getFillColor() == blocks[y + 2][x+1].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x + 1);
		columns.push_back(y + 2); rows.push_back(x + 1);
		columns.push_back(y); rows.push_back(x + 1);
		clearBlocks = true;
	}

	//Checks the bottom right vertical, similar code but moves down one as start square
	if (blocks[y+1][x + 1].getFillColor() == blocks[y + 2][x + 1].getFillColor() && blocks[y+1][x + 1].getFillColor() == blocks[y][x + 1].getFillColor())
	{
		columns.push_back(y); rows.push_back(x + 1);
		columns.push_back(y + 1); rows.push_back(x + 1);
		columns.push_back(y + 2); rows.push_back(x + 1);
		clearBlocks = true;

		if (blocks[y+1][x + 1].getFillColor() == blocks[y + 3][x + 1].getFillColor())
			columns.push_back(y + 3); rows.push_back(x + 1);

		if (blocks[y+1][x + 1].getFillColor() == blocks[y -1][x + 1].getFillColor())
			columns.push_back(y - 1); rows.push_back(x + 1);

	}
	else if (blocks[y+1][x + 1].getFillColor() == blocks[y][x + 1].getFillColor() && blocks[y+1][x + 1].getFillColor() == blocks[y -1][x + 1].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x + 1);
		columns.push_back(y - 1); rows.push_back(x + 1);
		columns.push_back(y); rows.push_back(x + 1);
		clearBlocks = true;
	}
	else if (blocks[y+1][x + 1].getFillColor() == blocks[y + 2][x + 1].getFillColor() && blocks[y+1][x + 1].getFillColor() == blocks[y + 3][x + 1].getFillColor())
	{
		columns.push_back(y + 3); rows.push_back(x + 1);
		columns.push_back(y + 2); rows.push_back(x + 1);
		columns.push_back(y + 1); rows.push_back(x + 1);
		clearBlocks = true;
	}
}

void BlockHandler::checkHorizT(int x , int y)
{	
	//Checks the upper left square's left and right for matching color
	if (blocks[y][x].getFillColor() == blocks[y][x + 1].getFillColor() && blocks[y][x].getFillColor() == blocks[y][x - 1].getFillColor())
	{
		columns.push_back(y); rows.push_back(x);
		columns.push_back(y); rows.push_back(x + 1);
		columns.push_back(y); rows.push_back(x - 1);
		clearBlocks = true;

		//checks the 2nd square to the right of inital square
		if (blocks[y][x].getFillColor() == blocks[y][x + 2].getFillColor())
			columns.push_back(y); rows.push_back(x + 2);

		//checks the 2nd square to the left of inital square
		if (blocks[y][x].getFillColor() == blocks[y][x - 2].getFillColor())
			columns.push_back(y); rows.push_back(x - 2);
		
	}
	//if no match on both sides of inital square, check the left side for match 3
	else if (blocks[y][x].getFillColor() == blocks[y][x - 1].getFillColor() && blocks[y][x].getFillColor() == blocks[y][x - 2].getFillColor())
	{
		columns.push_back(y); rows.push_back(x - 2);
		columns.push_back(y); rows.push_back(x - 1);
		columns.push_back(y); rows.push_back(x);
		clearBlocks = true;
	}
	//if no match on both sides of inital square, check the right side for match 3
	else if (blocks[y][x].getFillColor() == blocks[y][x + 1].getFillColor() && blocks[y][x].getFillColor() == blocks[y][x + 2].getFillColor())
	{
		columns.push_back(y); rows.push_back(x + 2);
		columns.push_back(y); rows.push_back(x + 1);
		columns.push_back(y); rows.push_back(x);
		clearBlocks = true;
	}

	//Checks top right for horizontal matches, similar code but moved to the right as start square
	if (blocks[y][x+1].getFillColor() == blocks[y][x + 2].getFillColor() && blocks[y][x+1].getFillColor() == blocks[y][x].getFillColor())
	{
		columns.push_back(y); rows.push_back(x);
		columns.push_back(y); rows.push_back(x + 1);
		columns.push_back(y); rows.push_back(x + 2);
		clearBlocks = true;

		if (blocks[y][x+1].getFillColor() == blocks[y][x + 3].getFillColor())
			columns.push_back(y); rows.push_back(x + 3);

		if (blocks[y][x+1].getFillColor() == blocks[y][x - 1].getFillColor())
			columns.push_back(y); rows.push_back(x - 1);

	}
	else if (blocks[y][x+1].getFillColor() == blocks[y][x].getFillColor() && blocks[y][x+1].getFillColor() == blocks[y][x - 1].getFillColor())
	{
		columns.push_back(y); rows.push_back(x - 1);
		columns.push_back(y); rows.push_back(x + 1);
		columns.push_back(y); rows.push_back(x);
		clearBlocks = true;
	}
	else if (blocks[y][x+1].getFillColor() == blocks[y][x + 2].getFillColor() && blocks[y][x+1].getFillColor() == blocks[y][x + 3].getFillColor())
	{
		columns.push_back(y); rows.push_back(x + 3);
		columns.push_back(y); rows.push_back(x + 2);
		columns.push_back(y); rows.push_back(x + 1);
		clearBlocks = true;
	}
}

void BlockHandler::checkHorizB(int x, int y)
{
	//Checks the bottom left square's left and right for matching color
	if (blocks[y + 1][x].getFillColor() == blocks[y + 1][x + 1].getFillColor() && blocks[y + 1][x].getFillColor() == blocks[y + 1][x - 1].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x);
		columns.push_back(y + 1); rows.push_back(x + 1);
		columns.push_back(y + 1); rows.push_back(x -1);
		clearBlocks = true;

		//checks the 2nd square to the right of inital square
		if (blocks[y+1][x].getFillColor() == blocks[y+1][x + 2].getFillColor())
			columns.push_back(y + 1); rows.push_back(x + 2);

		//checks the 2nd square to the left of inital square
		if (blocks[y+1][x].getFillColor() == blocks[y+1][x - 2].getFillColor())
			columns.push_back(y + 1); rows.push_back(x - 2);

	}
	//if no match on both sides of inital square, check the left side for match 3
	else if (blocks[y+1][x].getFillColor() == blocks[y+1][x - 1].getFillColor() && blocks[y+1][x].getFillColor() == blocks[y+1][x - 2].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x - 2);
		columns.push_back(y + 1); rows.push_back(x - 1);
		columns.push_back(y + 1); rows.push_back(x);
		clearBlocks = true;
	}
	//if no match on both sides of inital square, check the right side for match 3
	else if (blocks[y+1][x].getFillColor() == blocks[y+1][x + 1].getFillColor() && blocks[y+1][x].getFillColor() == blocks[y+1][x + 2].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x + 2);
		columns.push_back(y + 1); rows.push_back(x + 1);
		columns.push_back(y + 1); rows.push_back(x);
		clearBlocks = true;
	}

	//Check for bottom right for horizontal matches, similar code as above but moved over to the right as start square
	if (blocks[y + 1][x + 1].getFillColor() == blocks[y + 1][x + 2].getFillColor() && blocks[y + 1][x + 1].getFillColor() == blocks[y + 1][x].getFillColor())
	{

		columns.push_back(y + 1); rows.push_back(x);
		columns.push_back(y + 1); rows.push_back(x + 1);
		columns.push_back(y + 1); rows.push_back(x + 2);

		clearBlocks = true;

		if (blocks[y + 1][x + 1].getFillColor() == blocks[y + 1][x + 3].getFillColor())
			columns.push_back(y + 1); rows.push_back(x + 3);

		if (blocks[y + 1][x + 1].getFillColor() == blocks[y + 1][x - 1].getFillColor())
			columns.push_back(y + 1); rows.push_back(x - 1);

	}
	else if (blocks[y + 1][x + 1].getFillColor() == blocks[y + 1][x].getFillColor() && blocks[y + 1][x + 1].getFillColor() == blocks[y + 1][x - 1].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x + 1);
		columns.push_back(y + 1); rows.push_back(x - 1);
		columns.push_back(y + 1); rows.push_back(x);
		clearBlocks = true;
	}
	else if (blocks[y + 1][x + 1].getFillColor() == blocks[y + 1][x + 2].getFillColor() && blocks[y + 1][x + 1].getFillColor() == blocks[y + 1][x + 3].getFillColor())
	{
		columns.push_back(y + 1); rows.push_back(x + 3);
		columns.push_back(y + 1); rows.push_back(x + 2);
		columns.push_back(y + 1); rows.push_back(x + 1);
		clearBlocks = true;
	}

}