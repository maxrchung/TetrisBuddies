#include "GameStateObject.hpp"
#include "MessageType.h"

GameStateObject::GameStateObject(){
	
	remove("debugOutput.txt");

	score = 0;

	//clear the gameBoard
	for (int rowNum = 0; rowNum < boardHeight; rowNum++){
		for (int colNum = 0; colNum < boardWidth; colNum++){
			gameBoard[rowNum][colNum] = 0;
		}
	}

	//clear the tempRow 
	for (int i = 0; i < boardWidth; i++){ tempRow[i] = 0; }


	//*****
	//set all the rest of the values to 0 here
	frameNum = 0;
	cursorPos.first = (boardWidth / 2) - 1;
	cursorPos.second = (boardHeight / 2) - 1;
	rowInsertionCountdown = 0;
	clearingBlocks.clear();
	junkRows.clear();
	newRowActive = false;
	rowInsertionPaused = false;
	numChains = 0;
	numClearedBlocks = 0;
}



//Should work with the new GSO at this point
void GameStateObject::Print(){


	//output rows, top to bottom
	for (int rowNum = boardHeight - 1; rowNum > -1; rowNum--){
		std::cout << std::endl;
		std::cout << "Row " << rowNum << ":| ";
		//output columns left to right
		for (int colNum = 0; colNum < boardWidth; colNum++){
			std::cout << gameBoard[rowNum][colNum] << " ";
		}
		std::cout << "|";
	}
	std::cout << std::endl;
	
	std::cout << "Player score: " << score << std::endl;

	std::cout << "Temp :| ";
	for (int colNum = 0; colNum < boardWidth; colNum++){
		std::cout << tempRow[colNum] << " ";
	}
	std::cout << "|" << std::endl;

	//*********
	//print the rest of the elements that will be added to the state 
	std::cout << "Cursor position (row, col): " << cursorPos.first << "," << cursorPos.second << std::endl;
	std::cout << "Frame Number: " << frameNum << std::endl;
	std::cout << "Timestamp: " << timestamp << std::endl;
	std::cout << "Number of cleared blocks: " << numClearedBlocks << std::endl;
	std::cout << "Number of chains: " << numChains << std::endl;
	std::cout << "Row Insertion Timer paused? " << rowInsertionPaused << std::endl;
	std::cout << "Row Insertion In: " << rowInsertionCountdown << "ms" << std::endl;
	std::cout << "New row active? " << newRowActive << std::endl;


	std::cout << "Number of rows in junkRows: " << junkRows.size() << std::endl;
	if (!junkRows.empty()){
		std::cout << "Contents of junkRows:" << std::endl;
		for (int i = 0; i < junkRows.size(); i++){
			std::cout << "Row " << i << ": ";
			for (int j = 0; j < boardWidth; j++){
				std::cout << junkRows.at(i).at(j) << " ";
			}
			std::cout << std::endl;
		}
	}


	//std::cout << "" << << std::endl;
	std::cout << "Size of ClearingBlocks: " << clearingBlocks.size() << std::endl;
	if (clearingBlocks.size() > 0){
		std::cout << "Contents of ClearingBlocks: \n";
		for (int i = 0; i < clearingBlocks.size(); i++){
			std::cout << "	Row " << clearingBlocks[i].first << ", Col " << clearingBlocks[i].second <<  std::endl;
		}
	}

}



//outputs the state to a txt file
void GameStateObject::PrintToFile(){
	
	std::ofstream debugFile;

	debugFile.open("debugOutput.txt", std::ios::app);

	debugFile << "********************START OF NEW STATE*************************************" << std::endl;
	debugFile << "Player score: " << score << std::endl;
	debugFile << "Cursor position (row, col): " << cursorPos.first << "," << cursorPos.second << std::endl;
	debugFile << "Frame Number: " << frameNum << std::endl;
	debugFile << "Timestamp: " << timestamp << std::endl;
	debugFile << "Number of cleared blocks: " << numClearedBlocks << std::endl;
	debugFile << "Number of chains: " << numChains << std::endl;
	debugFile << "Row Insertion Timer paused? " << rowInsertionPaused << std::endl;
	debugFile << "Row Insertion In: " << rowInsertionCountdown << "ms" << std::endl;
	debugFile << "New row active? " << newRowActive << std::endl;

	debugFile << "Temp  :| ";
	for (int colNum = 0; colNum < boardWidth; colNum++){
		debugFile << tempRow[colNum] << " ";
	}
	debugFile << "|" << std::endl;

	//output rows, top to bottom
	for (int rowNum = boardHeight - 1; rowNum > -1; rowNum--){

		debugFile << "Row ";
		if (rowNum < 10){ debugFile << "0"; }
		debugFile << rowNum << ":| ";

		//output columns left to right
		for (int colNum = 0; colNum < boardWidth; colNum++){

			if (gameBoard[rowNum][colNum] == 0){debugFile << "  ";}
			else{ debugFile << gameBoard[rowNum][colNum] << " "; }
			
		}
		debugFile << "|" << std::endl;
	}
	debugFile << std::endl;





	//*********
	//print the rest of the elements that will be added to the state 

	debugFile << "Number of rows in junkRows: " << junkRows.size() << std::endl;
	if (!junkRows.empty()){
		debugFile << "Contents of junkRows:" << std::endl;
		for (int i = 0; i < junkRows.size(); i++){
			debugFile << "Row " << i << ": ";
			for (int j = 0; j < boardWidth; j++){
				debugFile << junkRows.at(i).at(j) << " ";
			}
			debugFile << std::endl;
		}
	}



	//debugFile << "" << << std::endl;
	debugFile << "Size of ClearingBlocks: " << clearingBlocks.size() << std::endl;
	if (!clearingBlocks.empty()){
		debugFile << "Contents of ClearingBlocks: \n";
		for (int i = 0; i < clearingBlocks.size(); i++){
			debugFile << "	Row " << clearingBlocks[i].first << ", Col " << clearingBlocks[i].second << std::endl;
		}
	}

	debugFile << "***********************************************************************\n" << std::endl;
	
	debugFile.close();
}


/*
PACKET STRUCTURE:

//format:
//uint8: command
//uint32: score
int, int = cursor row, cursor col
sf::Uint32 frame number
sf::Uint32 timestamp;
int numClearedBlocks
int numChains
bool row insertion paused
int row insertion countdown
bool new row active
//uint8 first row: temp row
//uint8 the rest: board

//byte: sizeOf(junkRows)
//until sizeOf is done: each row of junk blocks

//byte: sizeOf(fallingBlocks)
//until sizeOf is done: entries in the vector
//	
//
//byte: sizeOf(clearingBlocks)
//until sizeOf is done: entries in the vector



*/


sf::Packet& operator <<(sf::Packet& packet, const std::pair<int, int>& tp){ return packet << tp.first << tp.second; }
sf::Packet& operator >>(sf::Packet& packet, std::pair<int, int>& tp){ return packet >> tp.first >> tp.second; }



GameStateObject& GameStateObject::operator=(GameStateObject& rhs)
{
	score = rhs.score;
	cursorPos = rhs.cursorPos;
	frameNum = rhs.frameNum;
	timestamp = rhs.timestamp;
	numClearedBlocks = rhs.numClearedBlocks;
	numChains = rhs.numChains;
	rowInsertionPaused = rhs.rowInsertionPaused;
	rowInsertionCountdown = rhs.rowInsertionCountdown;
	newRowActive = rhs.newRowActive;

	for (int colNum = 0; colNum < boardWidth; colNum++){
		tempRow[colNum] = rhs.tempRow[colNum];
	}

	for (int rowNum = 0; rowNum < rhs.boardHeight; rowNum++) {
		for (int colNum = 0; colNum < rhs.boardWidth; colNum++)
		{
			gameBoard[rowNum][colNum] = rhs.gameBoard[rowNum][colNum];
		}
	}

	junkRows = rhs.junkRows;

	clearingBlocks = rhs.clearingBlocks;

	return *this;
}



//(insertion operator)
sf::Packet& operator <<(sf::Packet& packet, const GameStateObject& gso)
{
	packet << PacketDecode::PACKET_GAMESTATE;

	packet << gso.score;

	//  int, int = cursor row, cursor col
	packet << gso.cursorPos.first << gso.cursorPos.second;

	//	sf::Uint32 = frame number
	packet << gso.frameNum;

	//	sf::Uint32 timestamp;
	packet << gso.timestamp;

	//int numclearedBlocks
	packet << gso.numClearedBlocks;

	//int numChains
	packet << gso.numChains;

	//bool row insertion paused
	packet << gso.rowInsertionPaused;

	//  int row insertion pause
	packet << gso.rowInsertionCountdown;

	//	bool new row active
	packet << gso.newRowActive;


	int square = 10;

	//insert the temp row
	for (int colNum = 0; colNum < gso.boardWidth; colNum++){
		square = gso.tempRow[colNum];
		packet << square;
	}


	//put the contents of the entire board into a single packet
	//bottom to top, left to right

	for (int rowNum = 0; rowNum < gso.boardHeight; rowNum++) {
		for (int colNum = 0; colNum < gso.boardWidth; colNum++)
		{
			square = gso.gameBoard[rowNum][colNum];
			//std::cout << "Square value: " << (int)square << std::endl;
			packet << square;
		}
	}


	////byte: sizeOf(junkRows)
	////until sizeOf is done: each row of junk blocks
	int numJunkRows = gso.junkRows.size();
	packet << numJunkRows;
	for (int i = 0; i < numJunkRows; i++){
		for (int j = 0; j < gso.boardWidth; j++){
			packet << gso.junkRows.at(i).at(j);
		}
	}


	//sizeOf(clearingBlocks)
	//until sizeOf is done: entries in the vector
	int numClearingBlocks = gso.clearingBlocks.size();
	packet << numClearingBlocks;
	for (int i = 0; i < numClearingBlocks; i++){
		packet << gso.clearingBlocks[i];
	}

	//sizeOf(swappingBlocks)
	// (it SHOULD only ever be 2)
	//until sizeOf is done: entries in the vector
	int numSwappingBlocks = gso.swappingBlocks.size();
	packet << numSwappingBlocks;
	for (int i = 0; i < numSwappingBlocks; i++){
		packet << gso.swappingBlocks[i];
	}



	return packet;
}

//change this to work with the new GSO
//(extraction operator)
sf::Packet& operator >>(sf::Packet& packet, GameStateObject& gso)
{
	packet >> gso.score;

	//  int, int = cursor row, cursor col
	packet >> gso.cursorPos.first >> gso.cursorPos.second;


	//	sf::Uint32 = frame number
	packet >> gso.frameNum;


	//	sf::uint32 timestamp;
	packet >> gso.timestamp;

	//int numclearedBlocks
	packet >> gso.numClearedBlocks;

	//int numChains
	packet >> gso.numChains;

	//bool row insertion paused
	packet >> gso.rowInsertionPaused;

	//  int row insertion pause
	packet >> gso.rowInsertionCountdown;

	//	bool new row active
	packet >> gso.newRowActive;



	//insert the temp row
	for (int colNum = 0; colNum < gso.boardWidth; colNum++){
		packet >> gso.tempRow[colNum];
	}

	//insert the game board
	for (int rowNum = 0; rowNum < gso.boardHeight; rowNum++) {
		for (int colNum = 0; colNum < gso.boardWidth; colNum++)
		{
			packet >> gso.gameBoard[rowNum][colNum];
		}
	}



	//INSERTING THE JUNK ROWS INTO THE GSO
	gso.junkRows.clear();
	//byte: sizeOf(junkRows)
	//until sizeOf is done: each row of junk blocks
	int numjunkrows;
	packet >> numjunkrows;
	for (int i = 0; i < numjunkrows; i++){
		
		//if the array is smaller than the current row #, add a new row
		if (gso.junkRows.size() < (i + 1) ){
			const int bw = gso.boardWidth;
			std::array<int, bw> newjunkrow;

			//this for loop will be unnecessary if array defaults everything to 0
			for (int j = 0; j < bw; j++){
				newjunkrow.at(j) = 0;
			}

			gso.junkRows.push_back(newjunkrow);
		}

		//insert the values from the packet into each row
		//they SHOULD be inserted one row at a time, so the trailing zeroes will be there.
		for (int j = 0; j < gso.boardWidth; j++){
			packet >> gso.junkRows.at(i).at(j);
		}
	}


	std::pair<int, int> x;

	gso.clearingBlocks.clear();
	//sizeOf(clearingBlocks)
	//until sizeOf is done: entries in the vector
	int numClearingBlocks;
	packet >> numClearingBlocks;
	for (int i = 0; i < numClearingBlocks; i++){
		//each one is an entry in the vector
		packet >> x;
		gso.clearingBlocks.push_back(x);
	}

	gso.swappingBlocks.clear();
	int numSwappingBlocks;
	packet >> numSwappingBlocks;
	for (int i = 0; i < numSwappingBlocks; i++){
		//each one is an entry in the vector
		packet >> x;
		gso.swappingBlocks.push_back(x);
	}

	return packet;
}
