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

	//temporarily making this public so I can populate it and see if it gets made properly
	int gameBoard[12][6];

private:
	
	//right now, board width is 6 and board height is 12
	//sf::Uint8 boardWidth;
	//sf::Uint8 boardHeight;

	//right now, numColors is 5
	//will be set by the game logic
	sf::Uint8 numColors;
	
	//how long the rows should stop advancing for (after combos get cleared)	
	int pauseCountdown;

	//when this number reaches 0, a new row is inserted
	int insertionCountdown;

	sf::Uint32 playerScore;

	//how fast new rows should spawn in. 1 = slowest
	sf::Uint8 boardSpeed;

	//int gameBoard[12][6]; 
	//these are the default values in Tetris Attack. Rows = 12. Columns = 6.
	//I'd rather have it set in the constructor.  I'll worry about that later.
	//[12] = row num, [6] = col num 
	


};

#endif