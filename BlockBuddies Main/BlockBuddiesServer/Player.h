#pragma once
#include "UserInfo.h"
#include <SFML/Network.hpp>
#include <queue>
class Player
{
public:
	Player(sf::TcpSocket* userSocket);
	Player();
	~Player();

	UserInfo playerInfo;
	sf::TcpSocket* playerSocket;
    std::queue<sf::Packet> receivedPackets;

	Player& operator=(Player p);
    bool operator==(Player p);
};

