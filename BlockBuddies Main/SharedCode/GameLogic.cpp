//Implementation of GameLogic.hpp
#include "GameLogic.hpp"
#include "MessageType.h"

GameLogic::GameLogic(){
	
	srand(time(NULL));
	gameHasStarted = false;

	// Tetris Attack has 4 colors on easy, 5 colors on med/hard, and 6 in multi (grey blocks that become garbage)
	numColors = 5; 

	//this is set to true in InitalBoardPopulation(), which is what's run when the game starts for the first time
	isGameOver = true;

	//I don't know what a good value for this is.  We can play with it and find out what works.  Also, it will have to decrease as the game goes on. Based on score, maybe? Or game time? Or level?
	totalRowInsertionTime = 50;
	rowInsertionTimeLeft = totalRowInsertionTime;

	blocksMarkedForDeletion.clear();
	blocksToCheckForMatches.clear();
	//messagesToDecode doesn't have a clear

}



bool GameLogic::ReceiveMessage(sf::Packet incomingMessage){
	messagesToDecode.push(incomingMessage);
	return true;
}


void GameLogic::InitialBoardPopulation(){

	isGameOver = false;

	//also set the difficulty and whatnot here
	//right now this is already set in the constructor, but it's here so we can change it if necessary
	numColors = 5;


	//want at least 5 empty rows
	int initHeight = gso.boardHeight - 5;

	//randomly fill most of the board with blocks.
	for (int rowNum = 0; rowNum < initHeight; rowNum++) {
		for (int colNum = 0; colNum < gso.boardWidth; colNum++) {
			gso.gameBoard[rowNum][colNum] = (rand() % numColors) + 1;
		}
	}

	/*
	//check for anything that got matched and cleared.
	//replace them with new numbers
	//repeat until the clear list is empty
	*/


	//temporatily printing out the game state here so I can see what got cleared
	//gso.Print();

	/*
	check for any matches
	if there are any, remove them, apply gravity, refill the ones that are now 0, then check again starting at the lowest row that had something cleared in it
	*/



	//right now, they don't get refilled. they're just gone
	do{
		for (int rowNum = 0; rowNum < initHeight; rowNum++) {
			for (int colNum = 0; colNum < gso.boardWidth; colNum++) {
				CheckBlockForMatches(rowNum, colNum);
			}
		}

		//gso.Print();

		//PrintBlocksMarkedForDeletion();

		ClearMatches();
		ApplyGravity();
	} while (!blocksMarkedForDeletion.empty());


	gso.score = 0;

	PopulateTempRow();
}


bool GameLogic::PopulateTempRow(){

	for (int i = 0; i < gso.boardWidth; i++){
		gso.tempRow[i] = (rand() % numColors) + 1;
		
		//std::cout << "Value of temprow[" << i << "]: " << tempRow[i] << std::endl;
	}
	
	return true;
}

//shifts everything up by 1, and inserts the bottom row into the array
//adds the inserted blocks to BTCFM
//repopulates temp row
bool GameLogic::InsertBottomRow(){


	//if there's something in the top row already, game over (return 1)
	for (int colNum = 0; colNum < gso.boardWidth; colNum++){
		if (gso.gameBoard[gso.boardHeight - 1][colNum] != 0) { 
			std::cout << "game over" << std::endl; 
			isGameOver = true; 
			outgoingMessages.push(GameOverPacket());
			return true; }
	}


	//first, shift everything in the board up
	//start 2nd from top row, left column
	//then move down a row until at row 1 (new row will get inserted at row 0)
	for (int rowNum = gso.boardHeight - 2; rowNum > -1; rowNum--) {
		for (int colNum = 0; colNum < gso.boardWidth; colNum++) {
			gso.gameBoard[rowNum + 1][colNum] = gso.gameBoard[rowNum][colNum];
		}
	}


	//insert the last row at the bottom
	for (int j = 0; j < gso.boardWidth; j++){
		gso.gameBoard[0][j] = gso.tempRow[j];
		//std::cout << "gameBoard value[0][" << j << "]: " << gso.gameBoard[0][j] << ", tempRow val: " << tempRow[j] << std::endl;
	}

	//check all the bottom row squares for matches
	for (int j = 0; j < gso.boardWidth; j++){
		blocksToCheckForMatches.insert(std::make_pair(0, j));
	}

	//remake the temp row:
	PopulateTempRow();

	return false;
}


//ApplyGravity moves all blocks down until they rest on either another block or the bottom row
//it also adds every block that moved to BTCFM
bool GameLogic::ApplyGravity(){

	bool blockMoved;

	//for every piece on the board, starting at row 1
	for (int rowNum = 1; rowNum < gso.boardHeight; rowNum++){
		for (int colNum = 0; colNum < gso.boardWidth; colNum++){
			
			blockMoved = false;

			int currentBlockRow = rowNum;
			//std::cout << "Checking: " << currentBlockRow << colNum << std::endl;

			//while the current block exists and has nothing directly below it, and the row below it is in bounds (as in, not trying to insert into row -1)
			while ((gso.gameBoard[currentBlockRow][colNum] > 0) && (gso.gameBoard[currentBlockRow - 1][colNum] == 0) && (currentBlockRow > 0) ){
				blockMoved = true;
				//std::cout << "Moving " << currentBlockRow << colNum << std::endl;
					//the empty space below is set to the current block
					gso.gameBoard[currentBlockRow - 1][colNum] = gso.gameBoard[currentBlockRow][colNum];

					//the current block is set to empty
					gso.gameBoard[currentBlockRow][colNum] = 0;

					//check the block below
					currentBlockRow--;
			}

			//need to save each block's final position so we can add it to the CheckBlockForMatches set
			if (blockMoved){
				blocksToCheckForMatches.insert(std::make_pair(currentBlockRow, colNum));
			}

			//gso.Print();
			//std::cin.get();
		}
	}

	return true;
}


//swapping pieces applies gravity
bool GameLogic::SwapPieces(int row1Num, int col1Num, int row2Num, int col2Num){
	
	//if trying to swap anywhere out of bounds, fail out
	if ( 
		(row1Num < 0 || row1Num > gso.boardHeight - 1 || row2Num < 0 || row2Num > gso.boardHeight - 1) ||
		(col1Num < 0 || col1Num > gso.boardWidth - 1  || col2Num < 0 || col2Num > gso.boardWidth - 1)
		)
	{std::cout << "Swapping out of bounds" << std::endl;  return false;}

	int temp = gso.gameBoard[row1Num][col1Num];
	gso.gameBoard[row1Num][col1Num] = gso.gameBoard[row2Num][col2Num];
	gso.gameBoard[row2Num][col2Num] = temp;

	ApplyGravity();


	//ApplyGravity automatically puts any block that moved into BTCFM
	//Checking both blocks on the assumption neither of them fell. The two extra checks (if they did fall) are fine.

	blocksToCheckForMatches.insert(std::make_pair(row1Num, col1Num));
	blocksToCheckForMatches.insert(std::make_pair(row2Num, col2Num));

	return true;
}


bool GameLogic::ProcessBTCFM(){
	
	int r = -1;
	int c = -1;
	for (auto b : blocksToCheckForMatches){
		r = b.first;
		c = b.second;

		//std::cout << "R: " << r << ", C: " << c << std::endl;

		CheckBlockForMatches(r, c);
	}
	blocksToCheckForMatches.clear();
	
	return true;
}

//CheckBlockForMatches takes in a block and adds any matches it finds to BMFD
//it also updates the player's score
bool GameLogic::CheckBlockForMatches(int rowNum, int colNum){

	//if trying to match to an empty block, fail out
	if (gso.gameBoard[rowNum][colNum] == 0) { return false; }


	//where all the pieces go that are tested for each combo check
	std::set<std::pair<int, int>> potentialMatches;
	potentialMatches.insert(std::make_pair(rowNum, colNum));

	int originalSizeOfBMFD = blocksMarkedForDeletion.size();

	int clearedBlocks = 0;

	//if blocks to the left match, add to potentialMatches and repeat
	int rowToCheck = rowNum;
	int colToCheck = colNum - 1;
	while ((colToCheck > -1) && (gso.gameBoard[rowToCheck][colToCheck] == gso.gameBoard[rowNum][colNum])){
		potentialMatches.insert(std::make_pair(rowToCheck, colToCheck));
		colToCheck--;
	}

	//if blocks to the right match, add to potentialMatches and repeat
	colToCheck = colNum + 1;
	while ((colToCheck < gso.boardWidth) && (gso.gameBoard[rowToCheck][colToCheck] == gso.gameBoard[rowNum][colNum])){
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
	while ((rowToCheck < gso.boardHeight) && (gso.gameBoard[rowToCheck][colToCheck] == gso.gameBoard[rowNum][colNum])){
		potentialMatches.insert(std::make_pair(rowToCheck, colToCheck));
		rowToCheck++;
	}

	//if blocks below match, add to potentialMatches and repeat
	rowToCheck = rowNum - 1;
	while ((rowToCheck > -1) && (gso.gameBoard[rowToCheck][colToCheck] == gso.gameBoard[rowNum][colNum])){
		potentialMatches.insert(std::make_pair(rowToCheck, colToCheck));
		rowToCheck--;
	}

	//if the number in potential matches is > 2, add them to the BlocksToDelete
	if (potentialMatches.size() > 2){
		blocksMarkedForDeletion.insert(potentialMatches.begin(), potentialMatches.end());
	}

	//PrintBlocksMarkedForDeletion();

	//this is where scoring needs to be done. assuming blocksToClear is empty, it would be the number of elements in that set
	//get BMFD.size().  Then subtract it from the final size here.

	clearedBlocks = blocksMarkedForDeletion.size() - originalSizeOfBMFD;

	//now, calculate score.  It's always 10pts/block. If it's 4 blocks, bonus of +20. If it's 5, bonus of + 30. 8 = ??
	//algorithm: (10 * clearedBlocks) +  (if clearedBlocks > 3:) ( (clearedBlocks - 2) * 10)?

	if (clearedBlocks > 0){
		//this isn't complete yet
		int bonusBlocks = clearedBlocks - 3;
		int points = (clearedBlocks * 10) + (bonusBlocks * 10);
		gso.score += points;
	}

	return true;
}

//clearing matches applies gravity
//also empties BMFD
bool GameLogic::ClearMatches(){

	//for each element in the BMFD set:
		//get the row, col numbers, and set that element in the game board array to 0;


	int row;
	int col;

	//for (std::set<std::pair<int, int>>::iterator i = blocksMarkedForDeletion.begin(); i != blocksMarkedForDeletion.end(); ++i){
	for (auto i : blocksMarkedForDeletion) {
		row = i.first;
		col = i.second;
		gso.gameBoard[row][col] = 0;
	}
	
	ApplyGravity();

	//clear the BMFD
	blocksMarkedForDeletion.clear();

	return true;
}




bool GameLogic::ProcessMessage(sf::Packet toProcess){
	
	int command;
	PacketDecode decode;
	toProcess >> command;
	decode = PacketDecode(command);

	


	//swap will be the most common command, so it gets checked first
	if (command == PacketDecode::PACKET_SWAP){
		//std::cout << "Got 'Request Swap' command!" << std::endl;
		sf::Uint8 p1r, p1c, p2r, p2c;
		toProcess >> p1r >> p1c >> p2r >> p2c;
		std::cout << "Swapping piece (" << (int)p1r << ", " << (int)p1c << ") with (" << (int)p2r << ", " << (int)p2c << ")\n" << std::endl;
		
		//haven't tested this yet; the different data types might cause errors (int vs sf::uint8)
		SwapPieces(p1r, p1c, p2r, p2c);
		return true;
	}


	else if (command == PacketDecode::PACKET_NEWROW){
		//std::cout << "Got 'Request New Row' command!" << std::endl;

		//**set the row insertion time left to 0;
		rowInsertionTimeLeft = 0;

		//increases the total insertion time by 1, because it gets reduced by 1 in the Tick()
		totalRowInsertionTime++;

		return true;
	}

	else if (command == PacketDecode::PACKET_START){
		//std::cout << "Got 'Start Game' command!" << std::endl;
		
		//do all the game initalization stuff
		//like what?
		//call InitialBoardPopulation
		//so it should be public?
		//maybe
		//unless threre's a better way to do it
		
		if (isGameOver == true){
			gameHasStarted = true;
			InitialBoardPopulation();
			outgoingMessages.push(StartPacket());
		}
		
		else { std::cout << "Game has already started" << std::endl; }

		return true;
	}

	return false;
}


void GameLogic::GameTick(){

		//reduce timers (pauses for clear timers, time to insert new row)
		rowInsertionTimeLeft--;

		//while messageQueue isn't empty
		while ( !messagesToDecode.empty())
		{
			ProcessMessage(messagesToDecode.front());
			messagesToDecode.pop();
		}


		//while messageQueue isn't empty
			//processMessage (msgQ)
				//row might get inserted at bottom
					//set row insertion timer to 0
				//pieces might get swapped
					//swap pieces

		ProcessBTCFM();
		ClearMatches();


		//if the insert new row timer is 0;
		if (rowInsertionTimeLeft == 0){
			InsertBottomRow();

			//reduces the total row insertion time whenver a new row is inserted
			if (totalRowInsertionTime > 1){
				totalRowInsertionTime--;
			}

			//reset the row insertion timer
			rowInsertionTimeLeft = totalRowInsertionTime;
		}

		//send appropriate packets back to the client, such as game over or new game state
			//only possible packets to send: new GameState, start game, game over
			//startGame and GameOver are sent by ProcessMessage
		outgoingMessages.push(GSPacket());
	
}




//Debug functions:


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

void GameLogic::PrintBTCFM() const{

	std::cout << "contents of BTCFM: ";

	int row;
	int col;

	for (std::set<std::pair<int, int>>::iterator i = blocksToCheckForMatches.begin(); i != blocksToCheckForMatches.end(); ++i){
		row = (*i).first;
		col = (*i).second;

		std::cout << row << "," << col << " ";
	}
}

bool GameLogic::InsertRowAt(int insertOnRowNum, std::array<int, 7> rowToInsert){
	//insert the row at the specified place
	for (int j = 0; j < gso.boardWidth; j++){ gso.gameBoard[insertOnRowNum][j] = rowToInsert[j]; }
	return true;
}

//Decoded here, the packet is correct
sf::Packet GameLogic::GSPacket() const{
	
	sf::Packet gameStatePacket;
	gameStatePacket << PacketDecode::PACKET_GAMESTATE;
	gameStatePacket << gso;
	//return gso.GSPacket(); 
	return gameStatePacket;
}
