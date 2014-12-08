#include "UserInfo.h"
#include <iostream>

UserInfo::UserInfo() :username("default"), highScore(0), gamesPlayed(0), gamesWon(0)
{
	gamesLost = gamesPlayed - gamesWon;
	if (gamesPlayed != 0)
	{
		winPercentage = (float)gamesWon / gamesPlayed;
	}
	else
	{
		winPercentage = 0;
	}
}
UserInfo::UserInfo(std::string username, int highscore, int gamesplayed, int gameswon) :username(username),highScore(highscore),
gamesPlayed(gamesplayed), gamesWon(gameswon)
{
	gamesLost = gamesPlayed - gamesWon;
	if (gamesPlayed != 0)
	{
		winPercentage = (float)gamesWon/gamesPlayed;
	
	}
	else
	{
		winPercentage = 0;
	
	}
}

UserInfo::~UserInfo()
{
}

void UserInfo::printOut()
{
	std::cout << "Username :" << username << std::endl;
	std::cout << "Highscore :" << highScore << std::endl;
	std::cout << "GamesPlayed :" << gamesPlayed << std::endl;
	std::cout << "GamesWon :" << gamesWon << std::endl;
	std::cout << "gamesLost :" << gamesLost << std::endl;
	std::cout << "WinRate :" << winPercentage << std::endl;
	
}

sf::Packet& operator <<(sf::Packet& packet, const UserInfo& userInfo)
{
    return packet << userInfo.username 
                  << userInfo.gamesPlayed
                  << userInfo.gamesWon 
                  << userInfo.gamesLost 
                  << userInfo.highScore;
}

sf::Packet& operator >>(sf::Packet& packet, UserInfo& userInfo)
{
    return packet >> userInfo.username 
                  >> userInfo.gamesPlayed
                  >> userInfo.gamesWon 
                  >> userInfo.gamesLost 
                  >> userInfo.highScore;
}