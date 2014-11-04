//Implementation of GameLogic.hpp
#include "GameLogic.hpp"


GameGrid::GameGrid(){
	srand(time(NULL));
	boardWidth = 6;
	boardHeight = 12;
	//this is where gameBoard[boardHeight][boardWidth] array should be set.
//							   (rowNum)     (colNum)                           
	
	//clearing the array:
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			gameBoard[boardHeight][boardWidth] = 0;
		}
	}	
	
	numColors = 5; // Tetris Attack has 4 colors on easy, 5 colors on med/hard, and 6 in multi
	pauseCountdown = 0;
	pauseGame = false;	
	insertionCountdown = 0;
	score = 0;
}

void GameGrid::MainGameLoop(){
//loop it at 60 fps


	//check for messages
	//reduce timers
	//look at received messages
	//perform actions based on messages
	
	//if temp row doesn't exist
		//create a temp row

	//if it's time to insert temp row
		//insert temp row
		//check all the blocks in row 0 for matches
		//delete temp row

	//send messages back to client



}


std::array<int, 6> GameGrid::CreateTempRow(){

	std::array<int, 6> ret;
	for (int i = 0; i < boardWidth; i++){
		ret[i] = (rand() % boardWidth) + 1;
	}

	//send a message to the client here about the contents of the temp row

	return ret;
}


int GameGrid::InsertRow(std::array<int, 6> tempRow){

	//if there's something in the top row already, game over (return 1)
	for (int j = 0; j < boardWidth; j++){
		if (gameBoard[boardHeight - 1][j] != 0) {return 1;}
	}


	//first, shift everything in the board up
	//start top row, left column
	//then move down a row until at row 1 (new row gets inserted at row 0)
	for (int rowNum = boardHeight - 1; rowNum > 0; rowNum--) {
		for (int colNum = 0; colNum < boardWidth; colNum++) {
			
			//if the space isn't empty, move the block up 1
			if (gameBoard[rowNum][colNum] != 0)
				gameBoard[rowNum + 1][colNum] = gameBoard[rowNum][colNum];
		}
	}


	//insert the last row at the bottom
	for (int j = 0; j < boardWidth; j++){
		gameBoard[0][j] = tempRow[j];
	}

	//have to check for combos again (maybe in main game loop)

	//reset insertion timer here
	return 0;
}

void GameGrid::InitialBoardPopulation(){

	//also set the difficulty and whatnot here


	//randomly fill most of the board with blocks.  make sure they don't match automatically
	//(do the match checking later)
	//or maybe, do the match checking now and don't award any points
	
	
	//boardHeight - 5 so there are at least 5 guaranteed empty rows
	for (int i = 0; i < boardHeight - 5; i++) {
		for (int j = 0; j < boardWidth; j++) {
			gameBoard[boardHeight][boardWidth] = (rand() % numColors) + 1;
		}
	}	

}



//need to double-check all these functions, make sure they're actually swapping correctly
//also, as of right now gravity isn't implemented in these
//should gravity be applied here, or should it be done in the main game loop?

int GameGrid::SwapUp(int rowNum, int colNum){
	//if trying to swap on the top row, fail out
	if (rowNum > boardHeight - 1){
		return 1;
	}

	int temp = gameBoard[rowNum][colNum];
	gameBoard[rowNum][colNum] = gameBoard[rowNum + 1][colNum];
	gameBoard[rowNum + 1][colNum] = temp;
	return 0;

}

int GameGrid::SwapLeft(int rowNum, int colNum){
	//if trying to swap on the left column, fail out
	if (colNum < 1){
		return 1;
	}

	int temp = gameBoard[rowNum][colNum];
	gameBoard[rowNum][colNum] = gameBoard[rowNum][colNum - 1];
	gameBoard[rowNum][colNum - 1] = temp;
	return 0;
}

int GameGrid::SwapRight(int rowNum, int colNum){
	//if trying to swap on the right column, fail out
	if (colNum > boardWidth - 1){
		return 1;
	}

	int temp = gameBoard[rowNum][colNum];
	gameBoard[rowNum][colNum] = gameBoard[rowNum][colNum + 1];
	gameBoard[rowNum][colNum + 1] = temp;
	return 0;
}

int GameGrid::SwapDown(int rowNum, int colNum){
	
	//if trying to swap on the bottom row, fail out
	if (rowNum < 1){
		return 1;
	}

	int temp = gameBoard[rowNum][colNum];
	gameBoard[rowNum][colNum] = gameBoard[rowNum - 1][colNum];
	gameBoard[rowNum - 1][colNum] = temp;
	return 0;
}