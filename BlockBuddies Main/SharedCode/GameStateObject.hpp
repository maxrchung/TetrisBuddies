#ifndef GAMESTATEOBJECT_HPP
#define GAMESTATEOBJECT_HPP

#include "TimedPiece.h"
#include <SFML/Network.hpp>
#include <iostream>
#include "GameTimedEvent.h"
#include <fstream>
//Network.hpp so it can make itself into a packet
//iostream so we can print out the game state to make sure it looks correct
//utility so we can use pair
//GameTimedEvent so we can keep track of what blocks are doing what
//fstream to output to a file




//TO DO:
/*

add a timestamp
add a frame number
add something to indicate a new line has been inserted? (maybe a bool newLineActive that's always false except when a line is inserted)
add something to track falling blocks
add something to track clearing blocks
add something to track the cursor position (used only for multiplayer animation)
add the pause for the row insertion/scroll
rework the whole game state packet thing so we don't have all the weird encoding and decoding (it works fine before adding stuff to the state, but it makes changing it harder)


*/



class GameStateObject{

public:
	GameStateObject();

	//couts the contents of the board
	void Print();
	
	//Outputs the game state to a file
	void PrintToFile();

	//default Tetris Attack values: 12 rows, 6 cols
	static const int boardHeight = 20;
	static const int boardWidth = 16;

	int gameBoard[boardHeight][boardWidth];

	int tempRow[boardWidth];

	sf::Uint32 score;



///// NEW STUFF:


	//cursor item here
	//first = rowNum
	//second = colNum
	std::pair<int, int> cursorPos;

	//frame number here
	sf::Uint32 frameNum;

	//timestamp here
	int timestamp;
	//no idea if this is right. we might need to use something else for the timestamp 

	//row insertion pause here
	int rowInsertionPause;
	//this won't be used

	//falling blocks here
	std::vector<TimedPiece> fallingBlocks;

	//clearing blocks here
	std::vector<TimedPiece> clearingBlocks;

	bool newRowActive; 
	//how should this work? I don't want to have to reset it every single time 

	GameStateObject& operator=(GameStateObject& gso);
};

sf::Packet& operator <<(sf::Packet& packet, const GameStateObject& gso);
sf::Packet& operator >>(sf::Packet& packet, GameStateObject& gso);


#endif