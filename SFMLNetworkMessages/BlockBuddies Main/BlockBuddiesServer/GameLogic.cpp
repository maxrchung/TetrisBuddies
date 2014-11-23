//Implementation of GameLogic.hpp
#include "GameLogic.hpp"


GameLogic::GameLogic(){
	
	srand(time(NULL));
	
	// Tetris Attack has 4 colors on easy, 5 colors on med/hard, and 6 in multi (grey blocks that become garbage)
	numColors = 5; 
}



void GameLogic::InitialBoardPopulation(){

	//also set the difficulty and whatnot here
	//right now this is already set in the sonstructor, but it's here so we can change it if necessary
	numColors = 5;

	//randomly fill most of the board with blocks.

	//boardHeight - 5 so there are at least 5 guaranteed empty rows
	//for (int i = 0; i < boardHeight - 5; i++) {
	//	for (int j = 0; j < boardWidth; j++) {
	for (int rowNum = 0; rowNum < 8; rowNum++) {
		for (int colNum = 0; colNum < 6; colNum++) {

			//gameBoard[i][j] = (rand() % numColors) + 1;
			gso.gameBoard[rowNum][colNum] = (rand() % 5) + 1;
		}
	}

	/*
	//check for anything that got matched and cleared. 
	//replace them with new numbers
	//repeat until they're all full
	*/

	PopulateTempRow();
}


bool GameLogic::PopulateTempRow(){

	//6 = boardWidth
	for (int i = 0; i < 6; i++){
		tempRow[i] = (rand() % numColors) + 1;
	}
	
	return true;
}

bool GameLogic::InsertBottomRow(){


	//if there's something in the top row already, game over (return 1)
	for (int colNum = 0; colNum < 6; colNum++){
		if (gso.gameBoard[11][colNum] != 0) { return 1; }
	}


	//first, shift everything in the board up
	//start top row, left column
	//then move down a row until at row 1 (new row will get inserted at row 0)
	for (int rowNum = 11; rowNum > 0; rowNum--) {
		for (int colNum = 0; colNum < 6; colNum++) {

			//if the space isn't empty, move the block up 1
			if (gso.gameBoard[rowNum][colNum] != 0)
				gso.gameBoard[rowNum + 1][colNum] = gso.gameBoard[rowNum][colNum];
		}
	}


	//insert the last row at the bottom
	for (int j = 0; j < 6; j++){
		gso.gameBoard[0][j] = tempRow[j];
	}


	return false;
}



//need to double-check this functions, make sure it'sctually swapping correctly
//also, as of right now gravity isn't implemented in these
//should gravity be applied here, or should it be done in the main game loop?


bool GameLogic::SwapPieces(int row1Num, int col1Num, int row2Num, int col2Num){
	
	//if trying to swap anywhere out of bounds, fail out
	if ( 
		(row1Num < 0 || row1Num > 11 || row2Num < 0 || row2Num > 11) ||
		(col1Num < 0 || col1Num > 5  || col2Num < 0 || col2Num > 5)
		)
		{return false;}

	int temp = gso.gameBoard[row1Num][col1Num];
	gso.gameBoard[row1Num][col1Num] = gso.gameBoard[row2Num][col2Num];
	gso.gameBoard[row2Num][col2Num] = temp;
	return true;
}

void GameLogic::MainGameLoop(){
	while (true){

		//used to maintain the game loop
		clock.restart();
	
		//loop it at 60 fps. want each cycle to take no more than 16ms. So at the top of the loop get the time, do whatever actions are required, and at the bottom of the loop sleep for the remainder of the 16ms.
		//startTime = now

		//reduce timers (pauses for clear timers, time to insert new row)


		//check for messages
		//look at received messages
		//perform actions based on messages (ether request swap or request new row)


		//check any moved pieces for matches


		//if it's time to insert temp row (either because client requested it or new row timer reached 0)
			//insert temp row
			//check all the blocks in row 0 for matches
			//repopulate temp row
			//reset new row timer

		//send new game state back to client


		//sleep for what's left of 16ms 
		//hopefully, clock.restart() returns in ms
		sf::Time sleepTime = sf::milliseconds(16) - clock.restart();
		sf::sleep(sleepTime);
	}
}

/*
//this function will probably be deleted along with all the other parsedMessage stuff
void Gamelogic::GetMessage(){
	
	//1: request game start
	//2: request swap(piece1row, piece1col, piece2row, piece2col)
	//3 : request new row

	//clear parsedMessage:
	for (int i = 0; i < parsedMessage.size(); i++){
		parsedMessage[i] = "";
	}

	//take the string that's at the head of the queue, parse it, and put the pieces in parsedMessage
	


	//in a loop, find from the beginning of the string to the token
	//place that in parsedMessage[i]
	//the string we're parsing then ebcomes the reaminder of the unparsed string


}














*/