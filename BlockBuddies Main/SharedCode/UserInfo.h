#pragma once
#include <string>

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
};

