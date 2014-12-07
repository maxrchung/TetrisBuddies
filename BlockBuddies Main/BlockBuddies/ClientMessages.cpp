#include "ClientMessages.hpp"

sf::Packet ClientMessages::StartPacket(){
	sf::Packet ret;
	sf::Uint8 val = 1;
	ret	<< val;
	return ret;
}

sf::Packet ClientMessages::SwapPacket(sf::Uint8 p1row, sf::Uint8 p1col, sf::Uint8 p2row, sf::Uint8 p2col){
	sf::Packet ret;
	sf::Uint8 val = 2;
	ret << val << p1row << p1col << p2row << p2col;
	return ret;
}

sf::Packet ClientMessages::NewRowPacket(){
	sf::Packet ret;
	sf::Uint8 val = 3;
	ret << val;
	return ret;
}


//pass it a packet full of game state data, and decode it into a passed in GameStateObject
void ClientMessages::DecodeGameState(sf::Packet& decodeMe, GameStateObject& gso){

	sf::Uint32 sc;
	decodeMe >> sc;
	gso.score = sc;

	sf::Uint8 square = 9;

	for (int colNum = 0; colNum < gso.boardWidth; colNum++)
	{
		decodeMe >> square;
		//std::cout << "Decoded square: " << (int)square << std::endl;
		gso.tempRow[colNum] = square;
	}

	for (int rowNum = 0; rowNum < gso.boardHeight; rowNum++) {
		for (int colNum = 0; colNum < gso.boardWidth; colNum++)
		{
			decodeMe >> square;
			//std::cout << "Decoded square: " << (int)square << std::endl;
			gso.gameBoard[rowNum][colNum] = square;
		}
	}
}



bool ClientMessages::ProcessMessage(sf::Packet& toProcess, GameStateObject& gso){

	sf::Uint8 command;
	toProcess >> command;

	//Current game state
	if (command == 1){ 
		DecodeGameState(toProcess, gso);
		return true;
	}


	//Game Started
	else if (command == 3){
		//StartGame() function needs to be called
		//std::cout << "Game has started!" << std::endl;
		return true;
	}

	//Game Over
	else if (command == 4){
		//call GameOver()
		//std::cout << "Game Over!" << std::endl;
		return true;
	}

	return false;
}