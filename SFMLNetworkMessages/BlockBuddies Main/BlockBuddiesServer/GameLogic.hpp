//this is the code that will eventually be adapted for the server
//it's all game logic

#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include <stdlib.h>
#include <array>
#include <ctime>
#include <string>
#include "GameStateObject.hpp"

class GameLogic{

public:

	GameLogic();
	void MainGameLoop();




//private:

	//holds the array that keeps track of the board, as well as the player's score
	GameStateObject gso;

	//used to keep the game loop running
	bool isGameOver;

	//the number of colors that will be used in the game.
	//TA values: easy = 4, normal/hard = 5, multiplayer = 6 (gray blocks that make garbage)
	int numColors;
	
	

	//used for keeping time for the game loop
	sf::Clock clock;

	//this is an array of strings where the server puts all the client messages in to read them
	//all possible messages:
	//start game request
	//swap pieces request
	//new row request

	//there's a less shitty way to do this.
	//process the message object directly.
	//it's in the ServerMessages file already- decodeMessage
	//std::array<std::string, 5> parsedMessage;
							

	int tempRow[6];









	//functions**********************************************
	

	//if it returns true, game over.
	bool InsertBottomRow();

	//fills the empty board as the game starts
	void InitialBoardPopulation();

	//this is to populate the temp row
	bool PopulateTempRow();


	//looks at the message queue, takes the first message, and puts it in parsedMessage
	//void GetMessage();

	//this is the functions to swap blocks in the gameBoard array
	bool SwapPieces(int row1Num, int col1Num, int row2Num, int col2Num);

	//checks the whole board for any pieces that need to be moved down
	bool ApplyGravity();

	//returns a list of pieces that will be cleared as a result of matching to the square passed in
	//CheckForMatches(int rowNum, int colNum);

	//inserts a row that's passed to it at the row you specify
	//only used for debugging
	bool InsertRowAt(int insertOnRowNum, std::array<int, 6> rowToInsert);

	//need a function to create the message, and put it in a queue
	//also need a function to read the message from the client and act (beginning of loop)
};

#endif