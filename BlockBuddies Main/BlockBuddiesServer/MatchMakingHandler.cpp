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

void MatchMakingHandler::update()
{
	for (std::list<Game*>::iterator it = activeGames.begin(); it != activeGames.end(); ++it)
	{

		(*it)->runGame();
		if ((*it)->playerOneGame.IsGameOver() )
		{
			//send game over then remove from list
			sf::Packet lost;
			lost << PacketDecode::PACKET_GAMEOVER;
			(*it)->player1->playerSocket->send(lost);
			activeGames.erase(it++);

		}
		else if ((*it)->playerTwoGame.IsGameOver())
		{
			sf::Packet lost;
			lost << PacketDecode::PACKET_GAMEOVER;
			(*it)->player1->playerSocket->send(lost);
			activeGames.erase(it++);
		}



	}

}