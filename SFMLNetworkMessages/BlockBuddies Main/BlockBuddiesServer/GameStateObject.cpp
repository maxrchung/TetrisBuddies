#include "GameStateObject.hpp"


GameStateObject::GameStateObject(){
	
	score = 0;
	
	//clear the gameBoard
	for (int rowNum = 0; rowNum < 12; rowNum++){
		for (int colNum = 0; colNum < 6; colNum++){
			gameBoard[rowNum][colNum] = 0;
		}
	}
}

void GameStateObject::Print(){
	//output rows, top to bottom
	for (int rowNum = 11; rowNum > -1; rowNum--){
		std::cout << std::endl;
		std::cout << "Row " << rowNum << ":| ";
		//output columns left to right
		for (int colNum = 0; colNum < 6; colNum++){
			std::cout << gameBoard[rowNum][colNum] << " ";
		}
		std::cout << "|";
	}
	std::cout << std::endl;
}

//CreatePacket hasn't been successfully verified yet
sf::Packet GameStateObject::CreatePacket(){
	sf::Packet gameStatePacket;

	gameStatePacket << score;

	//it's supposed to put the contents of the entire board into a single packet
	//bottom to top, left to right

	//row numbers
	for (int rowNum = 0; rowNum < 12; rowNum++) {

		//column numbers
		for (int colNum = 0; colNum < 6; colNum++)
		{
			sf::Uint8 square = gameBoard[rowNum][colNum];
			gameStatePacket << square;
		}
	}

	return gameStatePacket;
}