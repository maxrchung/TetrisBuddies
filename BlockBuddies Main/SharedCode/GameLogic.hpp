//this is the code that will eventually be adapted for the server
//it's all game logic

#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP


#include <stdlib.h>
#include <array>
#include <vector>
#include <queue>
#include <ctime>
#include <set>
#include <string>
#include "GameStateObject.hpp"
#include "MessageType.h"

class GameLogic{

public:

	GameLogic();
	void GameTick();

	void Print(){ gso.Print(); }
	void PrintBlocksMarkedForDeletion() const;
	void PrintBTCFM() const;
	bool IsGameOver() const { return isGameOver; }
	void ResetGame();
	//used whenever a message needs to be passed into this game. Puts the message in the message queue 
	bool ReceiveMessage(sf::Packet incomingMessage);

	std::queue<sf::Packet> outgoingMessages;

	

	//Debug functions:

	//inserts a row that's passed to it at the row you specify
	//temporarily here so I can test the game state encoding/decoding
	bool InsertRowAt(int insertOnRowNum, std::array<int, 7> rowToInsert);
	bool SwapPieces(int row1Num, int col1Num, int row2Num, int col2Num);
	bool ProcessBTCFM();
	bool ClearMatches();
	//bool PopulateTempRow();
	bool gameHasStarted;
	bool sendNewRow;

	//returns the player's score
	int GetScore() { return gso.score; }


private:


	//holds the array that keeps track of the board, as well as the player's score
	GameStateObject gso;
	bool isGameOver;

	//the number of colors that will be used in the game.
	//TA values: easy = 4, normal/hard = 5, multiplayer = 6 (gray blocks that make garbage)
	int numColors;
	

	std::set<std::pair<int, int>> blocksMarkedForDeletion;
	std::set<std::pair<int, int>> blocksToCheckForMatches;
	std::queue<sf::Packet> messagesToDecode;

	int totalRowInsertionTime;
	int rowInsertionTimeLeft;

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
	//called by InitalBoardPopulation(), ClearMatches(), and SwapPieces()

	//takes a block's row and column, and adds blocks that will be cleared to blocksMarkedForDeletion
	bool CheckBlockForMatches(int rowNum, int colNum);

	//Runs all the blocks in blocksToCheckForMatches through CheckBlocksForMatches()
	//bool ProcessBTCFM();

	//Apples gravity and clears BMFD
	//bool ClearMatches();



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