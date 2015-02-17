//Implementation of GameLogic.hpp
#include "GameLogic.hpp"
#include "MessageType.h"

GameLogic::GameLogic(){

	srand(time(NULL));
	// Tetris Attack has 4 colors on easy, 5 colors on med/hard, and 6 in multi (grey blocks that become garbage)
	numColors = 5;

	//this is set to true in InitalBoardPopulation(), which is what's run when the game starts for the first time
	isGameOver = true;
	gameHasStarted = false;

	//I don't know what a good value for this is.  We can play with it and find out what works.  Also, it will have to decrease as the game goes on. Based on score, maybe? Or game time? Or level?
	totalRowInsertionTime = sf::milliseconds(16000);
	gso.rowInsertionCountdown = totalRowInsertionTime.asMilliseconds();

	blocksMarkedForDeletion.clear();
	blocksToCheckForMatches.clear();
	//messagesToDecode doesn't have a clear

	rowInsertionTimerRunning = true;

}

bool GameLogic::delayGame()
{
	if (!delayStarted)
	{
		clock.restart();
		tick = sf::Time::Zero;
		delayStarted = true;
		return false;
	}
	else
	{
		if (tick.asSeconds() < delayTime)
		{
			tick += clock.getElapsedTime();
			return false;
		}
		else
		{
			delayFinished = true;
			InitialBoardPopulation();
			gameHasStarted = true;
			sf::Packet toSend;
			toSend << gso;
			outgoingMessages.push(toSend);
			return true;
		}
	}

	return true;
}

void GameLogic::ResetGame()
{
	gso = GameStateObject();
	GameLogic::InitialBoardPopulation();
	totalRowInsertionTime = sf::milliseconds(16000);
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

	//clear board first
	//clear the gameBoard
	for (int rowNum = 0; rowNum < gso.boardHeight; rowNum++){
		for (int colNum = 0; colNum < gso.boardWidth; colNum++){
			gso.gameBoard[rowNum][colNum] = 0;
		}
	}

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




	//I think this works correctly now
	bool allBlocksFilled = false;
	do{
		for (int rowNum = 0; rowNum < initHeight; rowNum++) {
			for (int colNum = 0; colNum < gso.boardWidth; colNum++) {
				CheckBlockForMatches(rowNum, colNum);
			}
		}

		if (blocksMarkedForDeletion.size() == 0){
			allBlocksFilled = true;
		}

		ClearInitialMatches();


		for (int rowNum = 0; rowNum < initHeight; rowNum++) {
			for (int colNum = 0; colNum < gso.boardWidth; colNum++) {
				if (gso.gameBoard[rowNum][colNum] == 0){
					gso.gameBoard[rowNum][colNum] = (rand() % numColors) + 1;
				}
			}
		}


	} while (!allBlocksFilled);


	gso.score = 0;
	gso.newRowActive = false;
	destroyedBlocks.clear();

	PopulateTempRow();
	newRowClock.restart();
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

	if (!isGameOver){
		//if there's something in the top row already, game over (return 1)
		for (int colNum = 0; colNum < gso.boardWidth; colNum++){
			if (gso.gameBoard[gso.boardHeight - 1][colNum] != 0) {
				isGameOver = true;
				outgoingMessages.push(GameOverPacket());
				return true;
			}
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
	}

	return false;
}



//ApplyGravity moves all blocks down until they rest on either another block or the bottom row
//it also adds every block that moved to BTCFM

//change it so:
//every block only moves once per call
//only blocks that stopped moving are checked for matches
bool GameLogic::ApplyGravity(){


	bool blockMoved = false;

	//for every piece on the board, starting at row 1
	for (int rowNum = 1; rowNum < gso.boardHeight; rowNum++){
		for (int colNum = 0; colNum < gso.boardWidth; colNum++){



			int currentBlockRow = rowNum;

			//this is to check if a block moved on this row.
			//if it did
			bool currentRowMoved = false;


			//if the current block exists and has nothing directly below it, and the row below it is in bounds (as in, not trying to insert into row -1)
			if ((gso.gameBoard[currentBlockRow][colNum] > 0) && (gso.gameBoard[currentBlockRow - 1][colNum] == 0) && (currentBlockRow > 0)){

				blockMoved = true;
				currentRowMoved = true;

				//the empty space below is set to the current block
				gso.gameBoard[currentBlockRow - 1][colNum] = gso.gameBoard[currentBlockRow][colNum];

				//the current block is set to empty
				gso.gameBoard[currentBlockRow][colNum] = 0;


				//if it's on the bottom row, or the block below isn't empty, that means this block just hit bottom
				//so add it to BTCFM
				//(currentBlockRow is the one it's CHECKING. It starts at 1, and the row below that is 0.  So it SHOULD be if (currentblockrow - 1 == 0) )
				if ((currentBlockRow == 1) || ((currentBlockRow > 0) && (gso.gameBoard[currentBlockRow - 2][colNum] != 0))){
					blocksToCheckForMatches.insert(std::make_pair(currentBlockRow, colNum));
				}

				//check the block below
				//currentBlockRow--;
			}



			//gso.Print();
			//std::cin.get();
		}
	}

	return blockMoved;
}

/*
new gravity algorithm:

start on row 1, go by column:
	
	if column is not already falling:
		if the space below is empty, treat the column as "falling" with THIS piece as the head/timer



*/




//******************RECHECK THIS BECAUSE OF NEW GRAVITY AND STUFF
//swapping pieces applies gravity
bool GameLogic::SwapPieces(int row1Num, int col1Num, int row2Num, int col2Num){

	//if trying to swap anywhere out of bounds, fail out
	if (
		(row1Num < 0 || row1Num > gso.boardHeight - 1 || row2Num < 0 || row2Num > gso.boardHeight - 1) ||
		(col1Num < 0 || col1Num > gso.boardWidth - 1 || col2Num < 0 || col2Num > gso.boardWidth - 1)
		)
	{
		std::cout << "Swapping out of bounds" << std::endl;  return false;
	}

	int temp = gso.gameBoard[row1Num][col1Num];
	gso.gameBoard[row1Num][col1Num] = gso.gameBoard[row2Num][col2Num];
	gso.gameBoard[row2Num][col2Num] = temp;

	//ApplyGravity();


	//V------- Might need to re-examine this logic now that gravity has changed

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


//checks the entire board for matches
bool GameLogic::CheckAllBlocksForMatches(){

	for (int row = 0; row < gso.boardHeight; row++){
		for (int col = 0; col < gso.boardWidth; col++){
			CheckBlockForMatches(row, col);
		}
	}

	//if (blocksToCheckForMatches.size() == 0){return false;}
	//else { return true; }

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


	//instead of clearing them here, add them to destroyedBlocks

	if (blocksMarkedForDeletion.empty()){
		return false;
	}


	//for each element in the BMFD set:
	//get the row, col numbers, and set that element in the game board array to 0;

	int row;
	int col;


	for (auto i : blocksMarkedForDeletion) {
		row = i.first;
		col = i.second;
		//gso.gameBoard[row][col] = 0;

		//add to destroyedBlocks here:
		//(make sure that the new row timer is paused while clearing)
		destroyedBlocks.push_back(TimedPiece{i.first, i.second});

	}

	ApplyGravity();

	//clear the BMFD
	blocksMarkedForDeletion.clear();

	return true;
}

bool GameLogic::ClearInitialMatches(){


	//instead of clearing them here, add them to destroyedBlocks

	if (blocksMarkedForDeletion.empty()){
		return false;
	}


	//for each element in the BMFD set:
	//get the row, col numbers, and set that element in the game board array to 0;

	int row;
	int col;


	for (auto i : blocksMarkedForDeletion) {
		row = i.first;
		col = i.second;
		gso.gameBoard[row][col] = 0;

		//add to destroyedBlocks here:
		//(make sure that the new row timer is paused while clearing)
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


		//this line will be commented out:
		//SwapPieces(p1r, p1c, p2r, p2c);
		
		//instead:
		//put the pieces into a "swap" queue
		//pause the row timer
		//in the Tick(), it will be swapped when countdown = 0

		//rowInsertionTimerRunning = false;
		swappingBlocks.push_back(TimedPiece{p1r, p1c});
		swappingBlocks.push_back(TimedPiece{p2r, p2c});
		gso.swappingBlocks.push_back(std::make_pair(p1r, p1c));
		gso.swappingBlocks.push_back(std::make_pair(p2r, p2c));


		return true;
	}


	else if (command == PacketDecode::PACKET_NEWROW){
		//std::cout << "Got 'Request New Row' command!" << std::endl;

		InsertBottomRow();
		newRowClock.restart();

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
		GameLogic::ResetGame();
		if (isGameOver == true){
			gameHasStarted = true;
			InitialBoardPopulation();
			outgoingMessages.push(StartPacket());
		}

		//else { std::cout << "Game has already started" << std::endl; }

		return true;
	}

	return false;
}


void GameLogic::GameTick(){


	//reset all the temp variables:
	gso.newRowActive = false;
	//clear the clearing and swapping vectors here:
	gso.swappingBlocks.clear();
	gso.clearingBlocks.clear();
	//if this is true, put the game state as a message to the client
	bool gameStateChanged = false;

	//end temp variables

	gso.frameNum++;



	//reduce timers (rowInsertionTimerRunning pauses for swapping or clearing pieces)
	//DecrementCounters();

	//Decrement the row insertion counter
	if (rowInsertionTimerRunning) {gso.rowInsertionCountdown--;}
	//(since we're not using counters any more, this won't be used)

	

	//while messageQueue isn't empty
	while (!messagesToDecode.empty())
	{
		ProcessMessage(messagesToDecode.front());
		messagesToDecode.pop();
		gameStateChanged = true;
	}

	if (CheckSwappingTimers()){ gameStateChanged = true; }

	if (ApplyGravity()){gameStateChanged = true;}


	//while messageQueue isn't empty
	//processMessage (msgQ)
	//row might get inserted at bottom
	//set row insertion timer to 0
	//pieces might get swapped
	//swap pieces

	//ProcessBTCFM();
	//this isn't a good idea; this way blocks might still be matched while they're falling
	CheckAllBlocksForMatches();


	//it's set to "initial" right now because the code for teh clear animation isn't in place yet.
	if (ClearInitialMatches()){ gameStateChanged = true; }
	//if (ClearMatches()){gameStateChanged = true;}


	//if it's time to insert a new row:
	//if the insert new row timer is 0;
	//if (gso.rowInsertionCountdown == 0){
	if (newRowClock.getElapsedTime() > totalRowInsertionTime){

		InsertBottomRow();

		//reduces the total row insertion time whenever a new row is inserted
		if (totalRowInsertionTime.asMilliseconds() > 500){
			totalRowInsertionTime = totalRowInsertionTime - sf::milliseconds(500);
		}

		//reset the row insertion timer

		gso.newRowActive = true;
		newRowClock.restart();
		gso.rowInsertionCountdown = totalRowInsertionTime.asMilliseconds();
		std::cout << "Row insertion time: " << totalRowInsertionTime.asMilliseconds() << " ms" << std::endl;
		gameStateChanged = true;
	}

	//send appropriate packets back to the client, such as game over or new game state
	//possible packets to send: new GameState, start game, game over
	//startGame and GameOver are sent by ProcessMessage
	//so add: blocks to clear, 

	//queue = FIFO, so make sure you're adding the packets in the correct order

	/*if (outgoingMessages.size() >= 1)
	{
		std::queue<sf::Packet> swap;
		std::swap(outgoingMessages, swap);
		sf::Packet p;
		p << gso;
		outgoingMessages.push(p);
	}
	else
	{
		sf::Packet p;
		p << gso;
		outgoingMessages.push(p);
	}*/


	//this might cause a problem:
	//the clearingBlocks and swappingBlocks only get added to the GSO once
	//if the packet they're in gets overwritten, they will never be sent to the client
	if (gameStateChanged){
		//gso.PrintToFile();
		sf::Packet p;
		if (outgoingMessages.size() > 1)
		{
			std::queue<sf::Packet> swap;
			std::swap(outgoingMessages, swap);
		}
		p << gso;
		outgoingMessages.push(p);
	}
}

void GameLogic::NewTick(){

	//**********clear the temporary GSO stuff

		//reset all the temp variables:
		gso.newRowActive = false;

		//clear the clearing and swapping vectors here:
		gso.swappingBlocks.clear();
		gso.clearingBlocks.clear();

		//if this is true, put the game state as a message to the client
		bool gameStateChanged = false;

	//**********************end temp variables

	gso.frameNum++;


	//process input
		//check for messages

	//while messageQueue isn't empty
	while (!messagesToDecode.empty())
	{
		ProcessMessage(messagesToDecode.front());
		messagesToDecode.pop();
		gameStateChanged = true;
	}


	//check timers:
	
	//swap
	//if time is up, swap the two pieces
	if (CheckSwappingTimers()){gameStateChanged = true;}
	
	//clear
	//if time is up, remove the blocks from the board and apply gravity
	if (CheckClearingTimers()){gameStateChanged = true;}
	
	//fall
	//if time is up, move the blocks down by one square, check if they landed, then update the timers for the new pieces
	if (CheckFallingTimers()){gameStateChanged = true;}


	//check for matches
		//if match found:
		//add to "clearing" vectors along with times
		//add clearing blocks to GSO

	//
}


bool GameLogic::CheckSwappingTimers(){

	//(make sure that the new row timer is paused while swapping)
	//maybe add to totalRowInsertionTime?

	if (swappingBlocks.empty()){ return false; }

	//note: right now it only checks the first 2 elements
	//this might cause a bug on the off-chance that there are 4 pieces being swapped at the same time

	//if the two pieces' (at the head of the queue) timers = 0
	if ((swappingBlocks.at(0).duration.getElapsedTime() > blockSwapTime) && (swappingBlocks.at(1).duration.getElapsedTime() > blockSwapTime)){
		
		//swap the pieces
		//(SwapPieces adds them to BTCFM)
		SwapPieces(swappingBlocks.at(0).blockNum.first, swappingBlocks.at(0).blockNum.second, swappingBlocks.at(1).blockNum.first, swappingBlocks.at(1).blockNum.second);



		//remove the pieces
		//swappingBlocks.erase(swappingBlocks.begin(), swappingBlocks.begin()+1);
		swappingBlocks.clear();

		//apply gravity(?) (gravity will be reworked)

		return true;
	}

	return false;
}


bool GameLogic::CheckClearingTimers(){

	//maybe add to totalRowInsertionTime?

	if (destroyedBlocks.empty()){ return false; }

	//if the pieces's clearing times are up
		//remove them
		//apply gravity(?)

	for (auto i = destroyedBlocks.begin(); i != destroyedBlocks.end(); ++i){
	//for (int i = 0; i < destroyedBlocks.size(); ++i){
		if (i->duration.getElapsedTime() > blockClearTime){
			gso.gameBoard[i->blockNum.first][i->blockNum.second] = 0;
			
			//remove from the vector here:
			destroyedBlocks.erase(i);
		}

	}

	return false;
}


bool GameLogic::CheckFallingTimers(){

	//(this should be checked on a per-column basis, starting at row 1)

	//if a piece's falling timer is up
		//move it down one block, reset the falling time
		//if the piece landed, remove it from the Falling queue and add it to BTCFM


	return false;
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