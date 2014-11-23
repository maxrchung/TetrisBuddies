#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include "GameStateObject.hpp"

class ClientMessages{

public:
	sf::Packet StartPacket();
	sf::Packet SwapPacket(sf::Uint8, sf::Uint8, sf::Uint8, sf::Uint8);
	sf::Packet NewRowPacket();
	
	//pass it a packet full of game state data, and decode it into a passed in GameStateObject
	void DecodeGameState(sf::Packet& decodeMe, GameStateObject& gso);

	bool ProcessMessage(sf::Packet toProcess);

	//going to need a function for each command to process
	//extract the command from the packet in ProcessMessage, then pass the rest of the packet to the new function


private:
};