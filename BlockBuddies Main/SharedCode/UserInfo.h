#ifndef USERINFO_H
#define USERINFO_H

#include <string>
#include <SFML/Network.hpp>

class UserInfo
{
public:
	UserInfo();
	UserInfo(std::string username, int highscore, int gamesplayed,int gamesWon);
	~UserInfo();
	std::string username;
	int highScore;
	int gamesPlayed;
	int gamesWon;
	int gamesLost;
	float winPercentage;
	void printOut();
	float getWinRate();
    bool operator==(UserInfo u);
	UserInfo& operator=(UserInfo temp);
	std::string getUserName();
};

sf::Packet& operator <<(sf::Packet& packet, const UserInfo& userInfo);

sf::Packet& operator >>(sf::Packet& packet, UserInfo& userInfo);


#endif//USERINFO_H