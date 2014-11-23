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

}

bool ClientMessages::ProcessMessage(sf::Packet toProcess){

	sf::Uint8 command;
	toProcess >> command;

	//Current game state
	if (command == 1){ 
		//put the game state in the proper location here
		
		sf::Uint8 ps;
		sf::Uint8 bs;
		sf::Uint8 squareVal;

		toProcess >> ps >> bs;

		std::cout << "Game state: " << std::endl;
		std::cout << "Player score: " << (int)ps << std::endl;
		std::cout << "Board Speed: " << (int)bs << std::endl;

		int localBoard[12][6];


		//output rows, top to bottom
		for (int rowNum = 11; rowNum > -1; rowNum--){
			std::cout << std::endl;
			std::cout << "Row " << rowNum << ":| ";
			//output columns left to right
			for (int colNum = 0; colNum < 6; colNum++){
				
				toProcess >> squareVal;
				localBoard[rowNum][colNum] = squareVal;
				std::cout << " " << localBoard[rowNum][colNum];
			}
			std::cout << " |";
		}
	}

	//Temp Row contents
	else if (command == 2){
		//put the rest of the packet data in the temp row here
		std::cout << "This is the contents of the temp row " << std::endl;
	}

	//Game Started
	else if (command == 3){
		//call StartGame()
		std::cout << "Game has started!" << std::endl;
	}

	//Move a piece
	else if (command == 4){
		//call GameOver()
		std::cout << "Game Over!" << std::endl;
	}



	return false;
}