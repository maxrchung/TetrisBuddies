#ifndef CLIENTMESSAGES_HPP
#define CLIENTMESSAGES_HPP

#include <SFML/Network.hpp>
#include <iostream>
#include "GameStateObject.hpp"

class ClientMessages{

public:
	sf::Packet StartPacket();
	sf::Packet SwapPacket(sf::Uint8, sf::Uint8, sf::Uint8, sf::Uint8);
	sf::Packet NewRowPacket();

	//pass it the packet you want to process, and the GameStateObject you want it to operate on
	bool ProcessMessage(sf::Packet& toProcess, GameStateObject& gso);


private:
	//Takes a packet full of game state data, and decode it into a passed in GameStateObject
	void DecodeGameState(sf::Packet& decodeMe, GameStateObject& gso);
};

#endif