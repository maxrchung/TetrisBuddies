#pragma once
#include "Player.h"
#include <queue>
#include "Messenger.h"
#include "Message.h"
#include <map>
#include "Game.h"
class MatchMakingHandler
{
public:
	MatchMakingHandler();
	~MatchMakingHandler();

	std::queue<Player> connectedPlayers;
	std::queue<Player> activePlayers;
	static std::vector<Game> activeGames;
	void addMessage(Message message);
	void makeGame(Player p1, Player p2);

};

