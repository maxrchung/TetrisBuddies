#ifndef USER_HPP
#define USER_HPP

// Holds user info
class User
{
public:
	User();
	~User();

	char* username;
	int gamesPlayed;
	int gamesWon;
	int gamesLost;
	float winLossRatio;
};

#endif//USER_HPP