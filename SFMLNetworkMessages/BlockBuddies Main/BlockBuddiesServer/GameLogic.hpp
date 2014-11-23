//this is the code that will eventually be adapted for the server
//it's all game logic

#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include <stdlib.h>
#include <array>
#include <ctime>
#include <string>

class GameLogic{

public:

	GameLogic();
	void MainGameLoop();

private:


	
	//this is an array of strings where the server puts all the client messages in to read them
	std::array<std::string, 5> parsedMessage;
							

	

	//fills the empty board as the game starts
	void InitialBoardPopulation();


	//this is to create a temp row. 6 = boardWidth
	std::array<int, 6> CreateTempRow();

	//takes the temp row that has been created and inserts it into the bottom row of the game grid, shifting everything else up. 6 = boardWidth
	int InsertRow(std::array<int, 6> tempRow);

	//looks at the message queue, takes the first message, and puts it in parsedMessage
	void GetMessage();

	//this is the functions to swap blocks in the gameBoard array
	int SwapPieces(int row1Num, int col1Num, int row2num, int row2col);

	//check for matches
	//



	//need a function to create the message, and put it in a queue
	//also need a function to read the message from the client and act (beginning of loop)
};

#endif