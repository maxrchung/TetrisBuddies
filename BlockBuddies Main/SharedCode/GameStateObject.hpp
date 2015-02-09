#ifndef GAMESTATEOBJECT_HPP
#define GAMESTATEOBJECT_HPP


#include <SFML/Network.hpp>
#include <iostream>
#include "GameTimedEvent.h"
#include <fstream>
#include <stdio.h>
//Network.hpp so it can make itself into a packet
//iostream so we can print out the game state to make sure it looks correct
//utility so we can use pair
//GameTimedEvent so we can keep track of what blocks are doing what
//fstream to output to a file
//stdio to clear the output file before writing to it

//TO DO:
/*
add a timestamp
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
	//static const int boardHeight = 10;
	//static const int boardWidth = 8;

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
	//no idea if this is right. we might need to use some other data type for the timestamp 

	//row insertion time
	int rowInsertionCountdown;


	//clearing blocks here
	std::vector<std::pair<int, int>> clearingBlocks;


	bool newRowActive; 

	GameStateObject& operator=(GameStateObject& gso);
};

sf::Packet& operator <<(sf::Packet& packet, const GameStateObject& gso);
sf::Packet& operator >>(sf::Packet& packet, GameStateObject& gso);


#endif