#ifndef GAMESTATEOBJECT_HPP
#define GAMESTATEOBJECT_HPP


#include <SFML/Network.hpp>
#include <iostream>
#include "GameTimedEvent.h"
#include <array>
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
	static const int boardWidth = 8;
	//static const int boardHeight = 12;
	//static const int boardWidth = 6;

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
	sf::Uint32 timestamp;

	//row insertion time
	int rowInsertionCountdown;
	bool rowInsertionPaused;

	//block multiplier
	int blockMultiplier;
	//cleared blocks
	int numClearedBlocks;

	//clearing blocks go here to tell the client what's about to be cleared
	std::vector<std::pair<int, int>> clearingBlocks;

	//swapping blocks go here to tell the client what's about to be swapped
	std::vector<std::pair<int, int>> swappingBlocks;

	//contains the junk blocks sent over by the other player, in row form
	std::vector<std::array<int, boardWidth>> junkRows;

	bool newRowActive; 

	GameStateObject& operator=(GameStateObject& gso);
};

sf::Packet& operator <<(sf::Packet& packet, const GameStateObject& gso);
sf::Packet& operator >>(sf::Packet& packet, GameStateObject& gso);


#endif