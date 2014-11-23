#include "GameStateObject.hpp"


GameStateObject::GameStateObject(){
	
	playerScore = 500;
	boardSpeed = 200;
	pauseCountdown = 0;
	insertionCountdown = 0; //this will be set by the game logic later
	
	//clear the gameBoard
	for (int rowNum = 0; rowNum < 12; rowNum++){
		for (int colNum = 0; colNum < 6; colNum++){
			gameBoard[rowNum][colNum] = 0;
		}
	}
}

//uint 8 - score
//uint 8 - speed
//uint 8[][] - board squares

void GameStateObject::Print(){
	//output rows, top to bottom
	for (int rowNum = 11; rowNum > -1; rowNum--){
		std::cout << std::endl;
		std::cout << "Row " << rowNum << ":| ";
		//output columns left to right
		for (int colNum = 0; colNum < 6; colNum++){
			std::cout <<gameBoard[rowNum][colNum] << " ";
		}
		std::cout << "|";
	}
}

//CreatePacket hasn't been successfully verified yet
sf::Packet GameStateObject::CreatePacket(){
	sf::Packet gameStatePacket;

	gameStatePacket << playerScore << boardSpeed;

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