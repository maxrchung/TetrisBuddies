#include "UserInfo.h"
#include <iostream>

UserInfo::UserInfo() :username("default"), highScore(0), gamesPlayed(0), gamesWon(0)
{
	gamesLost = gamesPlayed - gamesWon;
	if (gamesPlayed != 0)
	{
		winPercentage = ((float)(gamesWon) / (float)gamesPlayed) * 100;
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
		winPercentage = ((float)(gamesWon) / (float)gamesPlayed );
	
	}
	else
	{
		winPercentage = 0;
	
	}
}

UserInfo::~UserInfo()
{
}

float UserInfo::getWinRate()
{
	if (gamesPlayed != 0)
	{
		winPercentage = ((float)(gamesWon) / (float)gamesPlayed);

	}
	else
	{
		winPercentage = 0;

	}
	return winPercentage;
}
void UserInfo::printOut()
{
	std::cout << "Username :" << username << std::endl;
	std::cout << "Highscore :" << highScore << std::endl;
	std::cout << "GamesPlayed :" << gamesPlayed << std::endl;
	std::cout << "GamesWon :" << gamesWon << std::endl;
	std::cout << "gamesLost :" << gamesLost << std::endl;
	std::cout << "WinRate :" << getWinRate() << std::endl;
	
}

// Checks if the usernames are the same. There's no point in checking 
// the other info since the usernames should be unique anyways
bool UserInfo::operator==(UserInfo u)
{
    return username == u.username;
}

UserInfo& UserInfo::operator=(UserInfo temp)
{
	username = temp.username;
	gamesPlayed = temp.gamesPlayed;
	gamesWon = temp.gamesWon;
	highScore = temp.highScore;
	return *this;
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