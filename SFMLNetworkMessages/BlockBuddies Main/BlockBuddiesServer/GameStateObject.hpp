#ifndef GAMESTATEOBJECT_HPP
#define GAMESTATEOBJECT_HPP

#include <SFML/Network.hpp>
#include <iostream>
//Network.hpp so it can make itself into a packet
//iostream so we can print out the game state to make sure it looks correct


class GameStateObject{

public:
	GameStateObject();
	//couts the contents of the board
	void Print();
	
	//returns the whole packet of the gameState 
	sf::Packet GSPacket() const; 

	//default Tetris Attack values: 12 rows, 6 cols
	static const int boardHeight = 13;
	static const int boardWidth = 7;

	int gameBoard[boardHeight][boardWidth];

	int tempRow[boardWidth];

	sf::Uint32 score;

};

#endif