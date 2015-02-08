#include "SinglePlayerHandler.h"

static std::map<sf::IpAddress, Game*> singlePlayer;

SinglePlayerHandler::SinglePlayerHandler()
{

}


SinglePlayerHandler::~SinglePlayerHandler()
{

}

void SinglePlayerHandler::makeGame(Player p1)
{
	Game* nGame = new Game(1);
	nGame->player1 = &p1;
	singlePlayer.insert(std::pair<sf::IpAddress, Game*>(p1.myAddress, nGame));
}

void SinglePlayerHandler::addMessage(sf::Packet addMe, sf::IpAddress myAddress)
{
	singlePlayer.at(myAddress)->packetQueue1.push(&addMe);
	singlePlayer.at(myAddress)->playerOneGame.ReceiveMessage(addMe);
}

void SinglePlayerHandler::update()
{
	//Run the game tick
	//check to see if game is over. If it is you should remvove them from the list.
	for (auto check : singlePlayer)
	{
			check.second->playerOneGame.GameTick();
	}

	//for (int i = 0; i < toErase.size(); ++i)
	//{
		//singlePlayer.erase(toErase[i]);
	//}


}