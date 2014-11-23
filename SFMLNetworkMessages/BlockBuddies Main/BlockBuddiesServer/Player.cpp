#include "Player.h"

Player::Player()
{
	playerSocket = nullptr;
	playerInfo = UserInfo();
}

Player::Player(sf::TcpSocket* userSocket, UserInfo userInfo)
{
	playerSocket = userSocket;
	playerInfo = userInfo;
}


Player::~Player()
{
}
