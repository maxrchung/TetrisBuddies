#pragma once
#include "Player.h"
#include <queue>
#include "Message.h"
#include "Game.h"
#include <list>


class MatchMakingHandler
{
public:
	MatchMakingHandler();
	~MatchMakingHandler();

	bool isInQueue(sf::IpAddress check);
	bool isInGame(sf::IpAddress check);

	void removeFromQueue(sf::IpAddress remove);
	void removePlayers();
	void removeFromGame(sf::IpAddress remove);
	
	void sendMessages();
	void addMessage(sf::Packet addMe, sf::IpAddress myAddress);

	void checkForMatches();
	void makeGame(Player *p1, Player *p2);
	void notifyPartnerOfDisconect(sf::IpAddress disconnectingPlayer);

	void update();

	std::deque<Player*> activePlayers;
	std::map<sf::IpAddress, Game*> multiPlayerGames;
	

private:



	std::deque<Game*> gameList;
	std::list<sf::IpAddress> removeMe;
	std::list<int> removePostions;

	void queueToRemove(sf::IpAddress p1, sf::IpAddress p2, int postionToRemove);
	void sendPackets(sf::Packet&, sf::Packet&, int position);
	void sendResults(int postion, int winner);

};
