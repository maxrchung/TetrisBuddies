#ifndef GAMESTATEOBJECT_HPP
#define GAMESTATEOBJECT_HPP

#include <SFML/Network.hpp>
#include <iostream>
//#include <array>

//Network.hpp so it can make itself into a packet
//iostream so we can print out the game state to make sure it looks correct

class GameStateObject{

public:
	GameStateObject();
	//couts the contents of the board
	void Print();
	sf::Packet CreatePacket();

	int gameBoard[12][6];
	//these are the default values in Tetris Attack. Rows = 12. Columns = 6.
	//I'd rather have the row/column numbers set in the constructor.  I'll worry about that later.
	//[12] = row num, [6] = col num 


	sf::Uint32 score;

private:
	
	//sf::Uint8 boardWidth;
	//sf::Uint8 boardHeight;


	
	//how long the rows should stop advancing for (after combos get cleared)	
	//will be set by the game logic
	//int pauseCountdown;

	//when this number reaches 0, a new row is inserted
	//will be set by the game logic
	//int insertionCountdown;



	//how fast new rows should spawn in. 1 = slowest
	//sf::Uint8 boardSpeed;




};

#endif