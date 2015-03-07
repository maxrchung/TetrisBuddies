//this is the code that will eventually be adapted for the server
//it's all game logic

#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include <stdlib.h>
#include <array>
#include <vector>
//#include <list>
#include <queue>
#include <ctime>
#include <set>
#include <string>
#include <math.h>
#include "GameStateObject.hpp"
#include "MessageType.h"
#include "TimedPiece.h"
#include "Chronometer.hpp"

class GameLogic{

public:

	GameLogic();
	void GameTick();


	void Print(){ gso.Print(); }
	void PrintBlocksMarkedForDeletion() const;
	bool IsGameOver() const { return isGameOver; }
	void ResetGame();
	//used whenever a message needs to be passed into this game. Puts the message in the message queue 
	bool ReceiveMessage(sf::Packet incomingMessage);

	std::queue<sf::Packet> outgoingMessages;

	bool delayGame();
	sf::Clock clock;
	sf::Time tick;
	bool delayStarted = false;
	bool delayFinished = false;
	int delayTime = 3;

	//Debug functions:

	//inserts a row that's passed to it at the row you specify
	//temporarily here so I can test the game state encoding/decoding
	//it SHOULD be std::array<int, boardWidth>. But that doesn't work here.
	bool InsertRowAt(int insertOnRowNum, std::array<int, 8> rowToInsert);
	
	//it's also commented out in "private"; not sure why it's public
	bool SwapPieces(int row1Num, int col1Num, int row2Num, int col2Num);
	
	bool ClearMatches();
	bool ClearInitialMatches();
	bool BlockIsFalling(int rowNum, int colNum) const;
	bool DestroyedBlockContains(int rowNum, int colNum) const;

	//checks the entire board for matches
	bool CheckAllBlocksForMatches();

	bool CreateJunkBlocks(int numBlocks);
	bool gameHasStarted;
	bool isGameOver;

	//returns the player's score
	int GetScore() const { return gso.score; }

	//this is used for multiplayer; it says how many junk blocks to send to the other player
	//it only gets set to nonzero when there's something to send
	int blocksToSend;

	//holds the array that keeps track of the board, as well as the player's score
	GameStateObject gso;


	//temporary:
	//GameStateObject newGSO;

private:


	//print out the matches that are cleared, along with the GSO info
	//const void PrintClearedBlocks();

	//these are used to set how long a piece takes to fall, and how long blocks stay until they're cleared
	//these values are all temporary; only one set is on the client for 300ms to swap
	const sf::Time blockClearTime = sf::milliseconds(2000);
	const sf::Time blockFallTime = sf::milliseconds(50);
	const sf::Time blockSwapTime = sf::milliseconds(300);
	


	std::vector<TimedPiece> fallingBlocks;
	std::vector<TimedPiece> swappingBlocks;
	std::vector<TimedPiece> destroyedBlocks;



	//the number of colors that will be used in the game.
	//TA values: easy = 4, normal/hard = 5, multiplayer = 6 (gray blocks that make garbage)
	int numColors;
	

	std::set<std::pair<int, int>> blocksMarkedForDeletion;
	std::queue<sf::Packet> messagesToDecode;

	sf::Time totalRowInsertionTime;
	sf::Time remainingRowInsertionTime;
	sftools::Chronometer newRowClock;

	sf::Clock totalTimeElapsedClock;
	sf::Time totalTimeElapsed;

	//functions**********************************************
	
	
	//if it returns true, game over.
	bool InsertBottomRow();

	//fills the empty board as the game starts
	void InitialBoardPopulation();

	//this is to populate the temp row
	bool PopulateTempRow();

	//decodes a message packet from the client
	bool ProcessMessage(sf::Packet toProcess);

	//swap blocks in the gameBoard array
	//bool SwapPieces(int row1Num, int col1Num, int row2Num, int col2Num);

	//checks the whole board for any pieces that need to be moved down
	bool ApplyGravity();

	//takes a block's row and column, and adds blocks that will be cleared to blocksMarkedForDeletion
	bool CheckBlockForMatches(int rowNum, int colNum);


	//Apples gravity and clears BMFD
	//bool ClearMatches();

	//if all 3 values are equal, return true
	//else return false
	bool AllMatch(int a, int b, int c);


	bool CheckSwappingTimers();
	bool CheckClearingTimers();
	bool CheckFallingTimers();


	sf::Packet StartPacket(){
		sf::Packet ret;
		ret << PacketDecode::PACKET_START;
		return ret;
	}

	sf::Packet GameOverPacket(){
		sf::Packet ret;
		ret << PacketDecode::PACKET_GAMEOVER;
		return ret;
	}

};

#endif