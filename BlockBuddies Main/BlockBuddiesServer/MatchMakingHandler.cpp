#include "MatchMakingHandler.h"

//Do this if you have a static object
//std::list<Game*> MatchMakingHandler::activeGames;

MatchMakingHandler::MatchMakingHandler()
{
}


MatchMakingHandler::~MatchMakingHandler()
{

}

void MatchMakingHandler::addMessage(sf::Packet addMe , sf::IpAddress myAddress)
{
	if (multiPlayerGames.at(myAddress)->player1->myAddress == myAddress)
		multiPlayerGames.at(myAddress)->packetQueue1.push(&addMe);
	else if (multiPlayerGames.at(myAddress)->player2->myAddress == myAddress)
		multiPlayerGames.at(myAddress)->packetQueue2.push(&addMe);
}


void MatchMakingHandler::checkForMatches()
{
	if (!gameGoing)
	{
		if (activePlayers.size() >= 2)
		{
			Player p1 = activePlayers.front();
			Player p2 = activePlayers.front();
			activePlayers.pop();
			activePlayers.pop();
			makeGame(p1, p2);
			gameGoing = true;

		}
	}
}

void MatchMakingHandler::makeGame(Player p1, Player p2)
{
	Game* nGame = new Game(2);
	nGame->player1 = &p1;
	nGame->player2 = &p2;
	multiPlayerGames.insert(std::pair<sf::IpAddress, Game*>(p1.myAddress, nGame));
	multiPlayerGames.insert(std::pair<sf::IpAddress, Game*>(p2.myAddress, nGame));
}

void MatchMakingHandler::update()
{
	//Run the game tick
	for (auto check: multiPlayerGames)
	{
		check.second->playerOneGame.GameTick();
		check.second->playerTwoGame.GameTick();
	}
}