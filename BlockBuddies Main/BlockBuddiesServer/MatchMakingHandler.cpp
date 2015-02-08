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
    if (activePlayers.size() >= 2)
    {
        makeGame(activePlayers[0], activePlayers[1]);
        activePlayers.pop_front();
        activePlayers.pop_front();
    }
}

void MatchMakingHandler::makeGame(Player p1, Player p2)
{
	Game* nGame = new Game(2);
	nGame->player1 = &p1;
	nGame->player2 = &p2;
	multiPlayerGames.insert(std::pair<sf::IpAddress, Game*>(p1.myAddress, nGame));
	multiPlayerGames.insert(std::pair<sf::IpAddress, Game*>(p2.myAddress, nGame));
    gameList.push_back(nGame);
    sf::Packet foundGame;
    foundGame << PacketDecode::PACKET_FOUNDGAME;
    p1.playerSocket->send(foundGame);
    p2.playerSocket->send(foundGame);
    std::cout << "Sent found game packet" << std::endl;
}

void MatchMakingHandler::update()
{
	//Run the game tick
	for (auto game: gameList)
	{
		game->playerOneGame.GameTick();
		game->playerTwoGame.GameTick();
	}
}