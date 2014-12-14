#include "Player.h"

int Player::receiveAliveLimit = 10;

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

// Checks if the player usernames match
// No need to check further since playerinfos should be unique
bool Player::operator==(Player p)
{
    return playerInfo == p.playerInfo; 
}