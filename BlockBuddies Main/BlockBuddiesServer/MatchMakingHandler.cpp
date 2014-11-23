#include "MatchMakingHandler.h"

std::list<Game*> MatchMakingHandler::activeGames;

MatchMakingHandler::MatchMakingHandler()
{
}


MatchMakingHandler::~MatchMakingHandler()
{
}


void MatchMakingHandler::checkForMatches()
{
	if (activePlayers.size() >= 2)
	{
		Player p1 = activePlayers.front();
		Player p2 = activePlayers.front();
		activePlayers.pop();
		activePlayers.pop();
		makeGame(p1, p2);

	}
}
void MatchMakingHandler::makeGame(Player p1, Player p2)
{
	Game* nGame = new Game();
	nGame->player1 = &p1;
	nGame->player2 = &p2;
	activeGames.push_back(nGame);
}