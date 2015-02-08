#pragma once

#include "Player.h"
#include <queue>
#include "Message.h"
#include "Game.h"
#include <list>


class MatchMakingHandler
{
public:
	MatchMakingHandler();
	~MatchMakingHandler();


	std::deque<Player> activePlayers;
    std::map<sf::IpAddress, Game*> multiPlayerGames;
    std::deque<Game*> gameList;

	void addMessage(sf::Packet addMe, sf::IpAddress myAddress);
	void checkForMatches();
	void makeGame(Player p1, Player p2);

	void update();

};
