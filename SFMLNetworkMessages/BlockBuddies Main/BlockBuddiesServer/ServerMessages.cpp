#include "ServerMessages.hpp"

bool ServerMessages::ProcessMessage(sf::Packet toProcess){
	sf::Uint8 command;
	
	toProcess >> command;

	if (command == 1){
		std::cout << "Got 'Start Game' command!" << std::endl;
		//call StartGame()
		return true;
	}

	else if (command == 2){
		std::cout << "Got 'Request Swap' command!" << std::endl;
		sf::Uint8 p1r, p1c, p2r, p2c;
		toProcess >> p1r >> p1c >> p2r >> p2c;
		std::cout << "Swapping piece (" << (int)p1r << ", " << (int)p1c << ") with (" << (int)p2r <<", " << (int)p2c << ")\n" << std::endl;
		//call "Swap Pieces()"
		return true;
	}


	else if (command == 3){
		std::cout << "Got 'Request New Row' command!" << std::endl;
		//call "CreateTempRow()"
		return true;
	}

	return false;
}


sf::Packet ServerMessages::StartPacket(){
	sf::Packet ret;
	sf::Uint8 startCommand = 3;
	ret << startCommand;
	return ret;
}

sf::Packet ServerMessages::GameOverPacket(){
	sf::Packet ret;
	sf::Uint8 gameOverCommand = 4;
	ret << gameOverCommand;
	return ret;
}

sf::Packet ServerMessages::GameStatePacket(GameStateObject& gs){
	sf::Packet ret;
	sf::Uint8 gameStateCommand = 1;
	ret << gameStateCommand;
	//append the game state to ret
	ret << gs.CreatePacket();
	return ret;
}