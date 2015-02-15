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

	std::list<sf::IpAddress> removeMe;
	std::map<sf::IpAddress, Game*> singlePlayerGames;
	
	std::vector<sf::IpAddress> toErase;

	
	bool isInGame(sf::IpAddress);
	bool gameGoing = false;
	void sendMessages();
	void removePlayers();
	void addMessage(sf::Packet message, sf::IpAddress);
	void makeGame(Player &p1);
	void update();

};