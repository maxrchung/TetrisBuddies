#ifndef GAMESTATEOBJECT_HPP
#define GAMESTATEOBJECT_HPP

#include <SFML/Network.hpp>
#include <iostream>
//Network.hpp so it can make itself into a packet
//iostream so we can print out the game state to make sure it looks correct







//TO DO:
/*

add a timestamp
add a frame number
add something to indicate a new line has been inserted? (maybe a bool newLineActive that's always false except when a line is inserted)
add something to track falling blocks
add something to track clearing blocks
add something to track the cursor position (used only for multiplayer animation)
rework the whole game state packet thing so we don't have all the weird encoding and decoding (it works fine now, but it makes changing it harder)

*/



class GameStateObject{

public:
	GameStateObject();
	//couts the contents of the board
	void Print();
	
	//returns the whole packet of the gameState 
	sf::Packet GSPacket() const; 

	//default Tetris Attack values: 12 rows, 6 cols
	static const int boardHeight = 20;
	static const int boardWidth = 16;

	int gameBoard[boardHeight][boardWidth];

	int tempRow[boardWidth];

	sf::Uint32 score;

	GameStateObject& operator=(GameStateObject& gso);
};


sf::Packet& operator <<(sf::Packet& packet, const GameStateObject& gso);

sf::Packet& operator >>(sf::Packet& packet, GameStateObject& gso);

#endif