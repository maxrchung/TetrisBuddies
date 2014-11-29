#ifndef SERVERMESSAGES_HPP
#define  SERVERMESSAGES_HPP

#include <iostream>
#include <SFML/Network.hpp>
#include "GameLogic.hpp"


class ServerMessages{
public:

	//takes a packet sent by the client and decodes it
	//(moved to GameLogic)
	//bool ProcessMessage(sf::Packet toProcess);


	//1: Current game state
	//3: start game
	//4: game over

	//takes a reference to a game logic, calls its game state's "toPacket", then returns that
	sf::Packet GameStatePacket(GameLogic& gl);

	//returns a StartGame packet to send to the client
	sf::Packet StartPacket();

	//returns a GameOver packet to send to the client
	sf::Packet GameOverPacket();

};
#endif
