#pragma once

#include "Player.h"
#include <queue>
#include "Message.h"
#include "Game.h"
#include <list>



class SinglePlayerHandler
{
public:
	SinglePlayerHandler();
	~SinglePlayerHandler();

	std::list<Player*> activePlayers;
	std::map<sf::IpAddress, Game*> singlePlayer;
	
	std::vector<sf::IpAddress> toErase;
	bool gameGoing = false;
	void addMessage(sf::Packet message, sf::IpAddress);
	void makeGame(Player p1);
	void update();

};