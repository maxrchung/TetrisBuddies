#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include "GameStateObject.hpp"


class ServerMessages{
public:
	bool ProcessMessage(sf::Packet toProcess);


	//1: Current game state
	//2: contents of temp row
	//3: start game
	//4: game over

	//takes a reference to a game state, calls its "toPacket", then returns that
	sf::Packet GameStatePacket(GameStateObject& gs);

	//generates a temp row, sends it as a packet
	sf::Packet ContentsOfTempRowPacket();

	//sends the StartGame command to client
	sf::Packet StartPacket();

	//sends the GameOver command to the client
	sf::Packet GameOverPacket();


private:

};