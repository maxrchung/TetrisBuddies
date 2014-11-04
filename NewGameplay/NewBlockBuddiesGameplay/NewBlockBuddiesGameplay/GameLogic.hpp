//this is the code that will eventually be adapted for the server
//it's all game logic

#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include <stdlib.h>
#include <array>
#include <ctime>

class GameGrid{

public:



	GameGrid();
	void MainGameLoop();

private:

	//specifies the number of columns in the game grid
	int boardWidth;

	//specifies the number of rows in the game grid
	int boardHeight;
	
	//this array keeps track of all the blocks in the grid
	int gameBoard[12][6]; //these are the default values in Tetris Attack. Rows = 12. Columns = 6.
							//I'd rather have it set in the constructor.  I'll worry about that later.
							//set as [1] = row num, [2] = col num 
					
							
							
	//the number of colors the board will have.  Tetris Attack's values are 5 in single player, 6 for multi
	int numColors;
	
	//how long the rows should stop advancing for (after combos get cleared)
	int pauseCountdown; 

	//when this number reaches 0, a new row is inserted
	int insertionCountdown;

	//the player's score
	unsigned int score;
	
	//if the game is paused or not
	bool pauseGame;
	



	//fills the empty board as the game starts
	void InitialBoardPopulation();


	//this is to create a temp row. 6 = boardWidth
	std::array<int, 6> CreateTempRow();

	//takes the temp row that has been created and inserts it into the bottom row of the game grid, shifting everything else up. 6 = boardWidth
	int InsertRow(std::array<int, 6> tempRow);

	//these are the functions to swap blocks in the gameBoard array
	//pass in the center block
	int SwapUp(int rowNum, int colNum);
	int SwapLeft(int rowNum, int colNum);
	int SwapRight(int rowNum, int colNum);
	int SwapDown(int rowNum, int colNum);
};

#endif