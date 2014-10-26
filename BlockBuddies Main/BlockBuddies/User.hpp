#ifndef USER_HPP
#define USER_HPP

// Not fleshed out, but will definitely be needed later
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