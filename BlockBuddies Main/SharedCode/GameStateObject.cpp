#include "GameStateObject.hpp"
#include "MessageType.h"

GameStateObject::GameStateObject(){
	
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
	cursorPos.first = boardHeight / 2;
	cursorPos.second = boardWidth / 2;
	rowInsertionPause = 0;
	fallingBlocks.clear();
	clearingBlocks.clear();
	newRowActive = false;
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
	std::cout << "Row Insertion Pause: " << rowInsertionPause << std::endl;
	std::cout << "New row active? " << newRowActive << std::endl;
	std::cout << "Size of FallingBlocks: " << fallingBlocks.size() << std::endl;


	if (fallingBlocks.size() > 0){
		std::cout << "Contents of FallingBlocks: \n";
		for (int i = 0; i < fallingBlocks.size(); i++){
			std::cout << "	Row " << fallingBlocks[i].blockNum.first << ", Col " << fallingBlocks[i].blockNum.second << ", duration: " << fallingBlocks[i].duration << std::endl;
		}
	}

	//std::cout << "" << << std::endl;
	std::cout << "Size of ClearingBlocks: " << clearingBlocks.size() << std::endl;
	if (clearingBlocks.size() > 0){
		std::cout << "Contents of ClearingBlocks: \n";
		for (int i = 0; i < clearingBlocks.size(); i++){
			std::cout << "	Row " << clearingBlocks[i].blockNum.first << ", Col " << clearingBlocks[i].blockNum.second << ", duration: " << clearingBlocks[i].duration << std::endl;
		}
	}

}



//change all the COUTs here so it outputs the state to a txt file
void GameStateObject::PrintToFile(){
	
	std::ofstream debugFile;

	debugFile.open("debugOutput.txt", std::ios::app);

	debugFile << "********************START OF NEW STATE*************************************" << std::endl;
	debugFile << "Frame Number: " << frameNum << std::endl;

	//output rows, top to bottom
	for (int rowNum = boardHeight - 1; rowNum > -1; rowNum--){
		debugFile << std::endl;
		//debugFile << "Row " << rowNum << ":| ";

		debugFile << "Row ";
		if (rowNum < 10){ debugFile << "0"; }
		debugFile << rowNum << ":| ";

		//output columns left to right
		for (int colNum = 0; colNum < boardWidth; colNum++){

			if (gameBoard[rowNum][colNum] == 0){debugFile << "  ";}
			else{ debugFile << gameBoard[rowNum][colNum] << " "; }
			
		}
		debugFile << "|";
	}
	debugFile << std::endl;

	debugFile << "Player score: " << score << std::endl;

	debugFile << "Temp :| ";
	for (int colNum = 0; colNum < boardWidth; colNum++){
		debugFile << tempRow[colNum] << " ";
	}
	debugFile << "|" << std::endl;

	//*********
	//print the rest of the elements that will be added to the state 
	debugFile << "Cursor position (row, col): " << cursorPos.first << "," << cursorPos.second << std::endl;
	debugFile << "Timestamp: " << timestamp << std::endl;
	debugFile << "Row Insertion Pause: " << rowInsertionPause << std::endl;
	debugFile << "New row active? " << newRowActive << std::endl;
	debugFile << "Size of FallingBlocks: " << fallingBlocks.size() << std::endl;


	if (fallingBlocks.size() > 0){
		debugFile << "Contents of FallingBlocks: \n";
		for (int i = 0; i < fallingBlocks.size(); i++){
			debugFile << "	Row " << fallingBlocks[i].blockNum.first << ", Col " << fallingBlocks[i].blockNum.second << ", duration: " << fallingBlocks[i].duration << std::endl;
		}
	}

	//debugFile << "" << << std::endl;
	debugFile << "Size of ClearingBlocks: " << clearingBlocks.size() << std::endl;
	if (clearingBlocks.size() > 0){
		debugFile << "Contents of ClearingBlocks: \n";
		for (int i = 0; i < clearingBlocks.size(); i++){
			debugFile << "	Row " << clearingBlocks[i].blockNum.first << ", Col " << clearingBlocks[i].blockNum.second << ", duration: " << clearingBlocks[i].duration << std::endl;
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
sf::Uint32 = frame number
sf::Time timestamp;
int row insertion pause
bool new row active
//uint8 first row: temp row
//uint8 the rest: board



//byte: sizeOf(fallingBlocks)
//until sizeOf is done: entries in the vector
//	
//
//byte: sizeOf(clearingBlocks)
//until sizeOf is done: entries in the vector



*/

sf::Packet& operator <<(sf::Packet& packet, const TimedPiece& tp){ return packet << tp.blockNum.first << tp.blockNum.second << tp.duration; }

sf::Packet& operator >>(sf::Packet& packet, TimedPiece& tp){ return packet >> tp.blockNum.first >> tp.blockNum.second >> tp.duration; }

//change this to work with the new GSO
sf::Packet GameStateObject::GSPacket() const{

	sf::Packet gameStatePacket;

	//just call the << operator here instead of all this stuff

	/*

	//format:
	//uint8: command
	//uint32: score
	//uint8 first row: temp row
	//uint8 the rest: board
	
	
	sf::Packet gameStatePacket;
	gameStatePacket << PacketDecode::PACKET_GAMESTATE;
	gameStatePacket << score;



	//  int, int = cursor row, cursor col
	//	sf::Uint32 = frame number
	//	sf::Time timestamp;
	//  int row insertion pause
	//	bool new row active









	//set to 10 so we can see if the value doesn't get assigned
	sf::Uint8 square = 10;
	
	//insert the temp row
	for (int colNum = 0; colNum < boardWidth; colNum++){
		square = tempRow[colNum];
		gameStatePacket << square;
	}



	//put the contents of the entire board into a single packet
	//bottom to top, left to right
	
	for (int rowNum = 0; rowNum < boardHeight; rowNum++) {
		for (int colNum = 0; colNum < boardWidth; colNum++)
		{
			square = gameBoard[rowNum][colNum];
			//std::cout << "Square value: " << (int)square << std::endl;
			gameStatePacket << square;
		}
	}

	/*

	gameStatePacket >> gameStateCommand;
	sf::Uint8 decoded;
	for (int rowNum = 0; rowNum < boardHeight; rowNum++) {
		for (int colNum = 0; colNum < boardWidth; colNum++)
		{

			gameStatePacket >> decoded;
			std::cout << "(in GSO::GSPacket)Decoded value: " << (int)decoded << std::endl;
			//gameStatePacket << square;
		}
	}
	*/


	//byte: sizeOf(fallingBlocks)
	//until sizeOf is done: entries in the vector
	//	
	//
	//byte: sizeOf(clearingBlocks)
	//until sizeOf is done: entries in the vector




	return gameStatePacket;
}


//change this to work with the new GSO
GameStateObject& GameStateObject::operator=(GameStateObject& rhs)
{
	score = rhs.score;
	cursorPos = rhs.cursorPos;
	frameNum = rhs.frameNum;
	timestamp = rhs.timestamp;
	rowInsertionPause = rhs.rowInsertionPause;
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

	fallingBlocks = rhs.fallingBlocks;
	clearingBlocks = rhs.clearingBlocks;

	return *this;
}




//change this to work with the new GSO
//(insertion operator)
sf::Packet& operator <<(sf::Packet& packet, const GameStateObject& gso)
{
	packet << PacketDecode::PACKET_GAMESTATE;

	packet << gso.score;

	//  int, int = cursor row, cursor col
	packet << gso.cursorPos.first << gso.cursorPos.second;

	//	sf::Uint32 = frame number
	packet << gso.frameNum;

	//	??? timestamp;
	packet << gso.timestamp;

	//  int row insertion pause
	packet << gso.rowInsertionPause;

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


	//sizeOf(fallingBlocks)
	//until sizeOf is done: entries in the vector
	int numFallingBlocks = gso.fallingBlocks.size();
	packet << numFallingBlocks;

	for (int i = 0; i < numFallingBlocks; i++){
		packet << gso.fallingBlocks[i];
	}


	//sizeOf(clearingBlocks)
	//until sizeOf is done: entries in the vector
	int numClearingBlocks = gso.clearingBlocks.size();
	packet << numClearingBlocks;
	for (int i = 0; i < numClearingBlocks; i++){
		packet << gso.clearingBlocks[i];
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


	//	??? timestamp;
	packet >> gso.timestamp;

	//  int row insertion pause
	packet >> gso.rowInsertionPause;

	//	bool new row active
	packet >> gso.newRowActive;



	//insert the temp row
	for (int colNum = 0; colNum < gso.boardWidth; colNum++){
		packet >> gso.tempRow[colNum];
	}

	for (int rowNum = 0; rowNum < gso.boardHeight; rowNum++) {
		for (int colNum = 0; colNum < gso.boardWidth; colNum++)
		{
			packet >> gso.gameBoard[rowNum][colNum];
		}
	}



	//sizeOf(fallingBlocks)
	//until sizeOf is done: entries in the vector
	int numFallingBlocks;
	TimedPiece x;
	packet >> numFallingBlocks;
	for (int i = 0; i < numFallingBlocks; i++){
		//each one is an entry in the vector
		packet >> x;
		gso.fallingBlocks.push_back(x);
	}


	//sizeOf(clearingBlocks)
	//until sizeOf is done: entries in the vector
	int numClearingBlocks;
	packet >> numClearingBlocks;
	for (int i = 0; i < numClearingBlocks; i++){
		//each one is an entry in the vector
		packet >> x;
		gso.clearingBlocks.push_back(x);
	}


	return packet;

}


//sf::Packet GameStateObject::GSPacket() const{
//
//	//format:
//	//uint8: command
//	//uint32: score
//	//uint8 first row: temp row
//	//uint8 the rest: board
//
//
//	sf::Packet gameStatePacket;
//	gameStatePacket << PacketDecode::PACKET_GAMESTATE;
//	gameStatePacket << score;
//
//	//set to 10 so we can see if the value doesn't get assigned
//	sf::Uint8 square = 10;
//
//	//insert the temp row
//	for (int colNum = 0; colNum < boardWidth; colNum++){
//		square = tempRow[colNum];
//		gameStatePacket << square;
//	}
//
//
//
//	//put the contents of the entire board into a single packet
//	//bottom to top, left to right
//
//	for (int rowNum = 0; rowNum < boardHeight; rowNum++) {
//		for (int colNum = 0; colNum < boardWidth; colNum++)
//		{
//			square = gameBoard[rowNum][colNum];
//			//std::cout << "Square value: " << (int)square << std::endl;
//			gameStatePacket << square;
//		}
//	}
//
//	/*
//
//	gameStatePacket >> gameStateCommand;
//	sf::Uint8 decoded;
//	for (int rowNum = 0; rowNum < boardHeight; rowNum++) {
//	for (int colNum = 0; colNum < boardWidth; colNum++)
//	{
//
//	gameStatePacket >> decoded;
//	std::cout << "(in GSO::GSPacket)Decoded value: " << (int)decoded << std::endl;
//	//gameStatePacket << square;
//	}
//	}
//	*/
//
//	return gameStatePacket;
//}

//GameStateObject& GameStateObject::operator=(GameStateObject& rhs)
//{
//	score = rhs.score;
//
//	for (int colNum = 0; colNum < boardWidth; colNum++){
//		tempRow[colNum] = rhs.tempRow[colNum];
//	}
//
//	for (int rowNum = 0; rowNum < rhs.boardHeight; rowNum++) {
//		for (int colNum = 0; colNum < rhs.boardWidth; colNum++)
//		{
//			gameBoard[rowNum][colNum] = rhs.gameBoard[rowNum][colNum];
//		}
//	}
//
//	return *this;
//}
//
//sf::Packet& operator <<(sf::Packet& packet, const GameStateObject& gso)
//{
//	packet << gso.score;
//	int square = 10;
//
//	//insert the temp row
//	for (int colNum = 0; colNum < gso.boardWidth; colNum++){
//		square = gso.tempRow[colNum];
//		packet << square;
//	}
//
//
//	//put the contents of the entire board into a single packet
//	//bottom to top, left to right
//
//	for (int rowNum = 0; rowNum < gso.boardHeight; rowNum++) {
//		for (int colNum = 0; colNum < gso.boardWidth; colNum++)
//		{
//			square = gso.gameBoard[rowNum][colNum];
//			//std::cout << "Square value: " << (int)square << std::endl;
//			packet << square;
//		}
//	}
//	return packet;
//}
//
//sf::Packet& operator >>(sf::Packet& packet, GameStateObject& gso)
//{
//	packet >> gso.score;
//
//	//insert the temp row
//	for (int colNum = 0; colNum < gso.boardWidth; colNum++){
//		packet >> gso.tempRow[colNum];
//	}
//
//	for (int rowNum = 0; rowNum < gso.boardHeight; rowNum++) {
//		for (int colNum = 0; colNum < gso.boardWidth; colNum++)
//		{
//			packet >> gso.gameBoard[rowNum][colNum];
//		}
//	}
//	return packet;
//
//}