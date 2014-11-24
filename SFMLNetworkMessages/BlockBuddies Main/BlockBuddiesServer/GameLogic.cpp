//Implementation of GameLogic.hpp
#include "GameLogic.hpp"


GameLogic::GameLogic(){
	
	srand(time(NULL));
	
	// Tetris Attack has 4 colors on easy, 5 colors on med/hard, and 6 in multi (grey blocks that become garbage)
	numColors = 5; 

	PopulateTempRow();
}



void GameLogic::InitialBoardPopulation(){

	isGameOver = false;

	//also set the difficulty and whatnot here
	//right now this is already set in the sonstructor, but it's here so we can change it if necessary
	numColors = 5;

	//randomly fill most of the board with blocks.

	//set at 8 so there are at least 5 empty rows
	for (int rowNum = 0; rowNum < 8; rowNum++) {
		for (int colNum = 0; colNum < 6; colNum++) {

			//gameBoard[i][j] = (rand() % numColors) + 1;
			gso.gameBoard[rowNum][colNum] = (rand() % numColors) + 1;
		}
	}

	/*
	//check for anything that got matched and cleared. 
	//replace them with new numbers
	//repeat until the clear list is empty
	*/

	gso.score = 0;

	PopulateTempRow();
}


bool GameLogic::PopulateTempRow(){

	//6 = boardWidth
	for (int i = 0; i < 6; i++){
		tempRow[i] = (rand() % numColors) + 1;
		
		//std::cout << "Value of temprow[" << i << "]: " << tempRow[i] << std::endl;
	}
	
	return true;
}

bool GameLogic::InsertBottomRow(){


	//if there's something in the top row already, game over (return 1)
	for (int colNum = 0; colNum < 6; colNum++){
		if (gso.gameBoard[11][colNum] != 0) { std::cout << "game over" << std::endl; isGameOver = true; return true; }
	}


	//first, shift everything in the board up
	//start top row, left column
	//then move down a row until at row 1 (new row will get inserted at row 0)
	for (int rowNum = 10; rowNum > -1; rowNum--) {
		for (int colNum = 0; colNum < 6; colNum++) {

			//if the space isn't empty, move the block up 1
			//if (gso.gameBoard[rowNum][colNum] != 0){

			
			gso.gameBoard[rowNum + 1][colNum] = gso.gameBoard[rowNum][colNum];
			//}
		}
	}


	//insert the last row at the bottom
	for (int j = 0; j < 6; j++){
		gso.gameBoard[0][j] = tempRow[j];
		//std::cout << "gameBoard value[0][" << j << "]: " << gso.gameBoard[0][j] << ", tempRow val: " << tempRow[j] << std::endl;
	}



	//remake the temp row:
	PopulateTempRow();


	return false;
}


bool GameLogic::ApplyGravity(){

	//for every piece on the board, starting at row 1
	for (int rowNum = 1; rowNum < 12; rowNum++){
		for (int colNum = 0; colNum < 6; colNum++){
			
			int currentBlockRow = rowNum;
			//std::cout << "Checking: " << currentBlockRow << colNum << std::endl;

			//while the current block exists and has nothing directly below it, or the row below it is still playable
			while ((gso.gameBoard[currentBlockRow][colNum] > 0) && (gso.gameBoard[currentBlockRow - 1][colNum] == 0) && (currentBlockRow > 0) ){
				
				//std::cout << "Moving " << currentBlockRow << colNum << std::endl;
					//the empty space below is set to the current block
					gso.gameBoard[currentBlockRow - 1][colNum] = gso.gameBoard[currentBlockRow][colNum];

					//the current block is set to empty
					gso.gameBoard[currentBlockRow][colNum] = 0;

					//check the block below
					currentBlockRow--;
			}
			//gso.Print();
			//std::cin.get();
		}
	}

	return true;
}


bool GameLogic::InsertRowAt(int insertOnRowNum, std::array<int, 6> rowToInsert){
	//insert the row at the specified place
	for (int j = 0; j < 6; j++){ gso.gameBoard[insertOnRowNum][j] = rowToInsert[j]; }
	return true;
}


//need to double-check this functions, make sure it's actually swapping correctly
//also, as of right now gravity isn't implemented in this
//should gravity be applied here, or should it be done in the main game loop?


bool GameLogic::SwapPieces(int row1Num, int col1Num, int row2Num, int col2Num){
	
	//if trying to swap anywhere out of bounds, fail out
	if ( 
		(row1Num < 0 || row1Num > 11 || row2Num < 0 || row2Num > 11) ||
		(col1Num < 0 || col1Num > 5  || col2Num < 0 || col2Num > 5)
		)
	{std::cout << "Swapping out of bounds" << std::endl;  return false;}

	int temp = gso.gameBoard[row1Num][col1Num];
	gso.gameBoard[row1Num][col1Num] = gso.gameBoard[row2Num][col2Num];
	gso.gameBoard[row2Num][col2Num] = temp;
	return true;
}



bool GameLogic::CheckForMatches(int rowNum, int colNum){
	
	
	//where all the pieces go that are tested for each combo check
	std::set<std::pair<int, int>> potentialMatches;
	potentialMatches.insert(std::make_pair(rowNum, colNum));

	gso.gameBoard[rowNum][colNum];

	int rowToCheck = rowNum;
	int colToCheck = colNum - 1;

	//if blocks to the left match, add to potentialMatches and repeat
	while ( (colToCheck > -1) && (gso.gameBoard[rowToCheck][colToCheck] == gso.gameBoard[rowNum][colNum])){
		potentialMatches.insert(std::make_pair(rowToCheck, colToCheck));
		colToCheck--;
	}

	colToCheck = colNum + 1;

	//if blocks to the right match, add to potentialMatches and repeat
	while ((colToCheck < 6) && (gso.gameBoard[rowToCheck][colToCheck] == gso.gameBoard[rowNum][colNum])){
		potentialMatches.insert(std::make_pair(rowToCheck, colToCheck));
		colToCheck++;
	}

	//if the number in potential matches is > 2, add them to the BlocksToDelete
	if (potentialMatches.size() > 2){
		blocksMarkedForDeletion.insert(potentialMatches.begin(), potentialMatches.end());
	}

	//reset to check for up/down
	rowToCheck = rowNum + 1;
	colToCheck = colNum;
	potentialMatches.clear();
	potentialMatches.insert(std::make_pair(rowNum, colNum));

	//if blocks above match, add to potentialMatches and repeat
	while ((rowToCheck < 12) && (gso.gameBoard[rowToCheck][colToCheck] == gso.gameBoard[rowNum][colNum])){
		potentialMatches.insert(std::make_pair(rowToCheck, colToCheck));
		rowToCheck++;
	}

	//if blocks below match, add to potentialMatches and repeat
	while ((rowToCheck > -1) && (gso.gameBoard[rowToCheck][colToCheck] == gso.gameBoard[rowNum][colNum])){
		potentialMatches.insert(std::make_pair(rowToCheck, colToCheck));
		rowToCheck--;
	}

	//if the number in potential matches is > 2, add them to the BlocksToDelete
	if (potentialMatches.size() > 2){
		blocksMarkedForDeletion.insert(potentialMatches.begin(), potentialMatches.end());
	}

	PrintBlocksMarkedForDeletion();

	return true;
}

void GameLogic::PrintBlocksMarkedForDeletion() const {
	std::cout << "contents of blocksmarkedfordeletion: ";

	int row;
	int col;

	for (std::set<std::pair<int, int>>::iterator i = blocksMarkedForDeletion.begin(); i != blocksMarkedForDeletion.end(); ++i){
		row = (*i).first;
		col = (*i).second;
		
		std::cout << row << "," << col << " ";
	}
}

void GameLogic::MainGameLoop(){
	while (!isGameOver){

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


		//sleep for what's left of 16ms (about 60fps, for now) (note: gso.Print() takes 8ms every time it's called)
		//still don't know how long parsing the messages will take
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