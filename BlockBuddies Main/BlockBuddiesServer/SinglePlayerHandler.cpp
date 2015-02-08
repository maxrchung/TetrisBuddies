#include "SinglePlayerHandler.h"
#include "DatabaseManager.h"

static std::map<sf::IpAddress, Game*> removeMe;

SinglePlayerHandler::SinglePlayerHandler()
{

}


SinglePlayerHandler::~SinglePlayerHandler()
{

}

void SinglePlayerHandler::removePlayers()
{
	for (auto remove : removeMe)
		singlePlayer.erase(remove);

	removeMe.clear();
}

void SinglePlayerHandler::makeGame(Player p1)
{
	Game* nGame = new Game(1);
	nGame->player1 = &p1;
	singlePlayer.insert(std::pair<sf::IpAddress, Game*>(p1.myAddress, nGame));
}

void SinglePlayerHandler::addMessage(sf::Packet addMe, sf::IpAddress myAddress)
{
	//singlePlayer.at(myAddress)->packetQueue1.push(&addMe);
	singlePlayer.at(myAddress)->playerOneGame.ReceiveMessage(addMe);
}

void SinglePlayerHandler::sendMessages()
{
	for (auto check : singlePlayer)
	{
		while (!check.second->playerOneGame.outgoingMessages.empty())
		{
			sf::Packet toSend = check.second->playerOneGame.outgoingMessages.front();
			check.second->playerOneGame.outgoingMessages.pop();
			check.second->player1->playerSocket->send(toSend);
		}
	}
}

void SinglePlayerHandler::update()
{
	//Run the game tick
	//check to see if game is over. If it is you should remvove them from the list.
	for (auto check : singlePlayer)
	{
		check.second->playerOneGame.GameTick();

		if (check.second->playerOneGame.gameHasStarted && check.second->playerOneGame.IsGameOver())
		{
			sf::Packet lost;
			lost << PacketDecode::PACKET_GAMEOVER;
			if (check.second->player1->playerInfo.highScore < check.second->playerOneGame.GetScore())
			{
				DatabaseManager::getInstance().updateNewHighScore(check.second->player1->playerInfo.username, check.second->playerOneGame.GetScore());
				sf::Packet update;
				update << PacketDecode::PACKET_USERINFOUPDATE;
				update << DatabaseManager::getInstance().getUserInfo(check.second->player1->playerInfo.username);
				check.second->player1->playerSocket->send(update);
			}
			check.second->player1->playerSocket->send(lost);
			removeMe.push_front(check.second->player1->myAddress);
		}
			
	}

	if(removeMe.size() > 0)
		removePlayers();

	//sendMessages();

}