#pragma once
#include "Player.h"
#include <queue>
class MatchMakingHandler
{
public:
	MatchMakingHandler();
	~MatchMakingHandler();

	std::queue<Player> connectedPlayers;
	std::queue<Player> activePlayers;

	void addMessage(Message message);
};

