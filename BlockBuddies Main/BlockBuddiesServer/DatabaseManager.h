#pragma once

#include "sqlite3.h"
#include "UserInfo.h"
#include <string>
#include <vector>


class DatabaseManager
{
	
	public:
		//call using DatabaseManager::getInstance().functionname() to use.
		static DatabaseManager& getInstance()
		{
			static DatabaseManager instance;
			return instance;
		}
		//if successful return true else return false
		bool registerUser(std::string username, std::string password);
		bool loginUser(std::string username, std::string password);
		std::vector<std::string> getFriendsList(std::string username);
		UserInfo getUserInfo(std::string username);
		bool updateUserGames(std::string username, bool wonned);
		bool addFriend(std::string username, std::string pfriend);
		bool updateNewHighScore(std::string username, int newScore);
	private:
		DatabaseManager() {}                                  // Private constructor
		~DatabaseManager() {}
		DatabaseManager(const DatabaseManager&);                 // Prevent copy-construction
		DatabaseManager& operator=(const DatabaseManager&);
		bool open();
		void close();
		std::string dbname = "game.db";
		sqlite3 *database;
};