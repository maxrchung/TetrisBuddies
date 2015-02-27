#include "MatchMakingHandler.h"
#include "DatabaseManager.h"

//Do this if you have a static object
//std::list<Game*> MatchMakingHandler::activeGames;

MatchMakingHandler::MatchMakingHandler()
{
}


MatchMakingHandler::~MatchMakingHandler()
{

}

bool MatchMakingHandler::isInGame(sf::IpAddress check)
{
	for (auto& checkMe: gameList)
		if (checkMe->player1->myAddress == check || checkMe->player2->myAddress == check)
			return true;

	return false;
}

void MatchMakingHandler::addMessage(sf::Packet addMe , sf::IpAddress myAddress)
{
	if (multiPlayerGames.size() > 0)
	{
		if (multiPlayerGames.at(myAddress)->player1->myAddress == myAddress)
			multiPlayerGames.at(myAddress)->playerOneGame.ReceiveMessage(addMe);
		else if (multiPlayerGames.at(myAddress)->player2->myAddress == myAddress)
			multiPlayerGames.at(myAddress)->playerTwoGame.ReceiveMessage(addMe);
	}
}

void MatchMakingHandler::notifyPartnerOfDisconect(sf::IpAddress disconnectingPlayer)
{
	int counter = 0;

	for (auto& check : gameList)
	{
		if (check->player1->myAddress == disconnectingPlayer)
		{
			sendResults(counter, 2);
			break;
		}
		else if (check->player2->myAddress == disconnectingPlayer)
		{
			sendResults(counter, 1);
			break;
		}
		counter++;
	}
}

bool MatchMakingHandler::isInQueue(sf::IpAddress toRemove)
{
	for (auto& check : activePlayers)
	{
		if (check->myAddress == toRemove)
			return true;
	}
	return false;
}

void MatchMakingHandler::removeFromQueue(sf::IpAddress remove)
{
	int count = 0;
	for (auto& check : activePlayers)
	{
		if (check->myAddress == remove)
			break;
		count++;
	}
	activePlayers.erase(activePlayers.begin() + count);
}

void MatchMakingHandler::checkForMatches()
{
    if (activePlayers.size() >= 2)
    {
		activePlayers[0]->playerInfo;
        makeGame(activePlayers[0], activePlayers[1]);
        activePlayers.pop_front();
        activePlayers.pop_front();
    }
}

void MatchMakingHandler::sendResults(int postition, int winner)
{
		sf::Packet lost;
		sf::Packet win;
		win << PacketDecode::PACKET_WINNER;
		lost << PacketDecode::PACKET_GAMEOVER;
		UserInfo Temp = gameList[postition]->player1->playerInfo;
		//If player one won do this else player two won
		if (winner == 1)
		{
			gameList[postition]->player1->playerSocket->send(win);
			gameList[postition]->player2->playerSocket->send(lost);
			DatabaseManager::getInstance().updateUserGames(gameList[postition]->player1->cachedName, true);
			DatabaseManager::getInstance().updateUserGames(gameList[postition]->player2->cachedName, false);
		}
		else
		{
			gameList[postition]->player2->playerSocket->send(win);
			gameList[postition]->player1->playerSocket->send(lost);
			DatabaseManager::getInstance().updateUserGames(gameList[postition]->player2->cachedName, true);
			DatabaseManager::getInstance().updateUserGames(gameList[postition]->player1->cachedName, false);
		}
		//Send updated profile information;
		sf::Packet updateP1;
		sf::Packet updateP2;
		Temp = gameList[postition]->player1->playerInfo;
		updateP1 << PacketDecode::PACKET_USERINFOUPDATE;
		updateP1 << DatabaseManager::getInstance().getUserInfo(gameList[postition]->player1->cachedName);

		updateP2 << PacketDecode::PACKET_USERINFOUPDATE;
		updateP2 << DatabaseManager::getInstance().getUserInfo(gameList[postition]->player2->cachedName);
		gameList[postition]->player2->playerSocket->send(updateP2);
		gameList[postition]->player1->playerSocket->send(updateP1);
}


void MatchMakingHandler::makeGame(Player* p1, Player* p2)
{
	Game* nGame = new Game(2);
	nGame->player1 = p1;
	nGame->player2 = p2;
	multiPlayerGames.insert(std::pair<sf::IpAddress, Game*>(p1->myAddress, nGame));
	multiPlayerGames.insert(std::pair<sf::IpAddress, Game*>(p2->myAddress, nGame));
    gameList.push_back(nGame);
    sf::Packet foundGame;
    foundGame << PacketDecode::PACKET_FOUNDGAME;
    p1->playerSocket->send(foundGame);
    p2->playerSocket->send(foundGame);
    std::cout << "Sent found game packet" << std::endl;
}

void MatchMakingHandler::removePlayers() 
{
	for (auto remove : removeMe)
		multiPlayerGames.erase(remove);

	for (auto remove : removePostions)
		gameList.erase(gameList.begin() + remove);

	removeMe.clear();
	removePostions.clear();
}

void MatchMakingHandler::removeFromGame(sf::IpAddress toRemove)
{
	int counter = 0;

	for (auto& check : gameList)
	{
		if (check->player1->myAddress == toRemove)
			queueToRemove(check->player1->myAddress, check->player2->myAddress, counter);
		else if (check->player2->myAddress == toRemove)
			queueToRemove(check->player1->myAddress, check->player2->myAddress, counter);
		counter++;
	}
	removePlayers();
}

void MatchMakingHandler::sendPackets(sf::Packet& p1, sf::Packet& p2 , int position)
{
	gameList[position]->player1->playerSocket->send(p1);
	gameList[position]->player1->playerSocket->send(p2);

	gameList[position]->player2->playerSocket->send(p2);
	gameList[position]->player2->playerSocket->send(p1);
}

void MatchMakingHandler::sendMessages()
{
	sf::Packet p1;
	sf::Packet p2;

	int counter = 0;

	for (auto check : gameList)
	{
		//if both have updated game states. 
		if (!check->playerOneGame.outgoingMessages.empty() && !check->playerTwoGame.outgoingMessages.empty())
		{
			p1 = check->playerOneGame.outgoingMessages.front();
			p2 = check->playerTwoGame.outgoingMessages.front();
			check->playerOneGame.outgoingMessages.pop();
			check->playerTwoGame.outgoingMessages.pop();
			//Send player one his gamestate first then send second players board to them first. 
			sendPackets(p1,p2,counter);
		} // if player one has updated their GSO
		else if (!check->playerOneGame.outgoingMessages.empty() && check->playerTwoGame.outgoingMessages.empty())
		{
			p1 = check->playerOneGame.outgoingMessages.front();
			p2 << check->playerTwoGame.gso;
			check->playerOneGame.outgoingMessages.pop();

			sendPackets(p1, p2, counter);

		}// if player two has updated thier GSO
		else if (check->playerOneGame.outgoingMessages.empty() && !check->playerTwoGame.outgoingMessages.empty())
		{
			p1 << check->playerOneGame.gso;
			p2 = check->playerTwoGame.outgoingMessages.front();
			check->playerTwoGame.outgoingMessages.pop();

			sendPackets(p1, p2, counter);
		}
		else
		{
			//Both queues are empty and so you don't need to send anything. 
		}
		counter++;
	}
}

void MatchMakingHandler::queueToRemove(sf::IpAddress p1, sf::IpAddress p2, int postionToRemove)
{
	removePostions.push_back(postionToRemove);
	removeMe.push_back(p1);
	removeMe.push_back(p2);
}

void MatchMakingHandler::update()
{
	//Run the game tick
	int counter = 0;
	for (auto check: gameList)
	{
		if (check->playerOneGame.delayFinished && check->playerTwoGame.delayFinished)
		{
			check->playerOneGame.GameTick();
			check->playerTwoGame.GameTick();

			if (check->playerOneGame.IsGameOver() && check->playerOneGame.gameHasStarted)
			{
				sendResults(counter, 2);
				queueToRemove(check->player1->myAddress, check->player2->myAddress, counter);
			}
			else if (check->playerTwoGame.IsGameOver() && check->playerTwoGame.gameHasStarted)
			{
				sendResults(counter, 1);
				queueToRemove(check->player1->myAddress, check->player2->myAddress, counter);
			}

		}
		else
		{
			check->playerOneGame.delayGame();
			check->playerTwoGame.delayGame();
		}
		counter++;
	}

	if (removeMe.size() > 0)
		removePlayers();
}