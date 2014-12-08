#include "Player.h"

Player::Player()
{
	playerSocket = nullptr;
	playerInfo = UserInfo();
}

Player::Player(sf::TcpSocket* userSocket)
    :playerSocket(userSocket)
{
}


Player::~Player()
{
}

Player& Player::operator=(Player p)
{
	playerSocket = p.playerSocket;
	playerInfo = p.playerInfo;
	return *this;
}