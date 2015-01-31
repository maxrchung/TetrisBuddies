#include "GameStateObject.hpp"
#include <iostream>




void SetupGSO(GameStateObject& gs){


	//randomly fill most of the board with blocks.
	for (int rowNum = 0; rowNum < gs.boardHeight; rowNum++) {
		for (int colNum = 0; colNum < gs.boardWidth; colNum++) {
			gs.gameBoard[rowNum][colNum] = 15;
		}
	}

	for (int colNum = 0; colNum < gs.boardWidth; colNum++) {
		gs.tempRow[colNum] = 8;
	}




	gs.score = 9999;
	gs.newRowActive = true;
	gs.cursorPos.first = 0;
	gs.cursorPos.second = gs.boardWidth - 1;
	gs.frameNum = 27;
	gs.timestamp = 2015;
	gs.rowInsertionPause = 500;
	gs.fallingBlocks.push_back(TimedPiece(1, 1, 30));
	gs.fallingBlocks.push_back(TimedPiece(2, 1, 31));
	gs.fallingBlocks.push_back(TimedPiece(3, 1, 32));

	gs.clearingBlocks.push_back(TimedPiece(0, 7, 99));
	gs.clearingBlocks.push_back(TimedPiece(0, 8, 100));
	gs.clearingBlocks.push_back(TimedPiece(0, 9, 101));
	gs.clearingBlocks.push_back(TimedPiece(0, 10, 102));
}


int main(){
	

	GameStateObject gso;


	SetupGSO(gso);
	//gso.Print();


	sf::Packet pack;

	pack << gso;

	GameStateObject newgs;

	pack >> newgs;
	
	newgs.Print();

	std::cin.get();
	

	return 0;
}