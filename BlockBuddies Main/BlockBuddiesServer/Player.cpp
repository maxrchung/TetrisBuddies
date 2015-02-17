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
	playerInfo = UserInfo();
	myAddress = (*userSocket).getRemoteAddress();
}

Player::~Player()
{
}

Player& Player::operator=(Player p)
{
	playerSocket = p.playerSocket;
	playerInfo.username = p.playerInfo.username;
	playerInfo.gamesPlayed = p.playerInfo.gamesPlayed;
	playerInfo.gamesWon = p.playerInfo.gamesWon;
	playerInfo.gamesLost = playerInfo.gamesLost;
	return *this;
}

// Checks if the player usernames match
// No need to check further since playerinfos should be unique
bool Player::operator==(Player p)
{
    return playerInfo == p.playerInfo; 
}