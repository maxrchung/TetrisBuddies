#pragma once
#include "UserInfo.h"
#include <SFML/Network.hpp>
class Player
{
public:
	Player(sf::TcpSocket* userSocket, UserInfo userInfo);
	Player();
	~Player();

	UserInfo playerInfo;
	sf::TcpSocket* playerSocket;

	Player& operator=(Player p);
};

