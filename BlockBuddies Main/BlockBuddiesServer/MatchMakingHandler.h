#pragma once
#include "Player.h"
#include <queue>
#include "Messenger.h"
#include "Message.h"
#include <map>
#include "Game.h"
#include <list>
class MatchMakingHandler
{
public:
	MatchMakingHandler();
	~MatchMakingHandler();

	std::queue<Player> activePlayers;
	static std::list<Game> activeGames;
	void addMessage(Message message);
	void makeGame(Player p1, Player p2);

};

