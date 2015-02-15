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

void MatchMakingHandler::addMessage(sf::Packet addMe , sf::IpAddress myAddress)
{
	if (multiPlayerGames.at(myAddress)->player1->myAddress == myAddress)
		multiPlayerGames.at(myAddress)->packetQueue1.push(&addMe);
	else if (multiPlayerGames.at(myAddress)->player2->myAddress == myAddress)
		multiPlayerGames.at(myAddress)->packetQueue2.push(&addMe);
}

bool MatchMakingHandler::isInQueue(sf::IpAddress check)
{
	return multiPlayerGames.count(check);
}

void MatchMakingHandler::removeFromQueue(sf::IpAddress remove)
{
	int count = 0;
	for (auto& check : activePlayers)
	{
		if (check.myAddress == remove)
			break;
		count++;
	}
	activePlayers.erase(activePlayers.begin() + count);
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

void MatchMakingHandler::sendResults(int postition, int winner)
{
	sf::Packet lost;
	sf::Packet win;
	win << PacketDecode::PACKET_WINNER;
	lost << PacketDecode::PACKET_GAMEOVER;
	//If player one won do this else player two won
	if (winner == 1)
	{
		gameList[postition]->player1->playerSocket->send(win);
		gameList[postition]->player2->playerSocket->send(lost);
		DatabaseManager::getInstance().updateUserGames(gameList[postition]->player1->playerInfo.username, true);
	}
	else
	{
		gameList[postition]->player2->playerSocket->send(win);
		gameList[postition]->player1->playerSocket->send(lost);
		DatabaseManager::getInstance().updateUserGames(gameList[postition]->player2->playerInfo.username, true);
	}
	//Send updated profile information;
	sf::Packet updateP1;
	sf::Packet updateP2;

	updateP1 << PacketDecode::PACKET_USERINFOUPDATE;
	updateP1 << DatabaseManager::getInstance().getUserInfo(gameList[postition]->player1->playerInfo.username);

	updateP2 << PacketDecode::PACKET_USERINFOUPDATE;
	updateP2 << DatabaseManager::getInstance().getUserInfo(gameList[postition]->player2->playerInfo.username);
	gameList[postition]->player2->playerSocket->send(updateP1);
	gameList[postition]->player1->playerSocket->send(updateP2);
	
}


void MatchMakingHandler::makeGame(Player &p1, Player &p2)
{
	Game* nGame = new Game(2);
	nGame->player1 = &p1;
	nGame->player2 = &p2;
	multiPlayerGames.insert(std::pair<sf::IpAddress, Game*>(p1.myAddress, nGame));
	multiPlayerGames.insert(std::pair<sf::IpAddress, Game*>(p2.myAddress, nGame));
    gameList.push_back(nGame);
	nGame->playerOneGame.gameHasStarted = true;
	nGame->playerTwoGame.gameHasStarted = true;
    sf::Packet foundGame;
    foundGame << PacketDecode::PACKET_FOUNDGAME;
    p1.playerSocket->send(foundGame);
    p2.playerSocket->send(foundGame);
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

void MatchMakingHandler::sendMessages()
{
	sf::Packet p1;
	sf::Packet p2;

	for (auto check : gameList)
	{
		if (!check->playerOneGame.outgoingMessages.empty() && !check->playerTwoGame.outgoingMessages.empty())
		{
			p1 = check->playerOneGame.outgoingMessages.front();
			p2 = check->playerTwoGame.outgoingMessages.front();
			check->playerOneGame.outgoingMessages.pop();
			check->playerTwoGame.outgoingMessages.pop();
			//Send player one his gamestate first then send second players board to them first. 
			check->player1->playerSocket->send(p1);
			check->player1->playerSocket->send(p2);

			check->player2->playerSocket->send(p2);
			check->player2->playerSocket->send(p1);	
		}
		else
		{
			//The case that one player doesn't have a packet to send.
			//Send whatever the most recent one is. 
			p1 << check->playerOneGame.gso;
			p2 << check->playerTwoGame.gso;
			
			check->player1->playerSocket->send(p1);
			check->player1->playerSocket->send(p2);

			check->player2->playerSocket->send(p2);
			check->player2->playerSocket->send(p1);
		}
	}
}

void MatchMakingHandler::update()
{
	//Run the game tick
	int counter = 0;
	bool needsRemove = false;;

	for (auto check: gameList)
	{
		if (check->playerOneGame.IsGameOver())
		{ 
			sendResults(counter , 2);
			//Remove players from list
			removeMe.push_front(check->player1->myAddress);
			removePostions.push_back(counter);
			removeMe.push_back(check->player1->myAddress);
			removeMe.push_back(check->player2->myAddress);

		}else if (check->playerTwoGame.IsGameOver())
		{
			sendResults(counter, 1);
			//Remove players from list
			removeMe.push_front(check->player1->myAddress);
			removePostions.push_back(counter);
			removeMe.push_back(check->player1->myAddress);
			removeMe.push_back(check->player2->myAddress);
		}
		else
		{
			check->playerOneGame.GameTick();
			check->playerTwoGame.GameTick();
		}
		counter++;
	}

	if (removeMe.size() > 0)
		removePlayers();

	

}