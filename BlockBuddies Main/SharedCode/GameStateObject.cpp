#include "GameStateObject.hpp"


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
}

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
}

sf::Packet GameStateObject::GSPacket() const{
	
	//format:
	//uint8: command
	//uint32: score
	//uint8 first row: temp row
	//uint8 the rest: board
	
	
	sf::Packet gameStatePacket;

	sf::Uint8 gameStateCommand = 1;
	gameStatePacket << gameStateCommand;
	gameStatePacket << score;

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

	return gameStatePacket;
}