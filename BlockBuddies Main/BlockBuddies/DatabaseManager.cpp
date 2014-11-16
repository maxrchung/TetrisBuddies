#include "DatabaseManager.h"
#include <iostream>
//opens the database
bool DatabaseManager::open()
{
	if (sqlite3_open(dbname.c_str(), &database) == SQLITE_OK)
		return true;

	return false;
}
//closes database
void DatabaseManager::close()
{
	sqlite3_close(database);
}

//checks to see if username already exist before inserting a new user with provided
//password and username. Returns true on success, and false otherwise.
bool DatabaseManager::registerUser(std::string username, std::string password)
{
	//check if username exists
	//if it doesn't exist create an account
	//else return false "account already exist"
	const char *name = username.c_str();
	const char *pass = password.c_str();
	if (open())
	{
		char *zErrMsg = 0; // error message
		sqlite3_stmt *stmt; //statement
		sqlite3_stmt *stmt2;
		const char *pzTest;
		char *szSQL; // actual raw sql

		//check if that username is already taken
		szSQL = "SELECT COUNT(username) FROM user WHERE username = ?;";

		// perparing sql stmt
		int rc = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt, &pzTest);

		//if sucessfully prepared bind values and proceed
		if (rc == SQLITE_OK)
		{
			sqlite3_bind_text(stmt, 1, name, strlen(name), 0);

			//execute statement;
			int result = sqlite3_step(stmt);
			int check = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);

			//if a result is generated
			if (result == SQLITE_ROW)
			{
				//if result is zero that means that username is available
				if (check == 0)
				{
					//add a new user
					szSQL = "INSERT INTO USER VALUES (?,?,0,0,0);";
					int rd = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt2, &pzTest);
					if (rd == SQLITE_OK)
					{
						sqlite3_bind_text(stmt2, 1, name, strlen(name), 0);
						sqlite3_bind_text(stmt2, 2, pass, strlen(pass), 0);

						//Insert the new User
						sqlite3_step(stmt2);
						sqlite3_finalize(stmt2);
						close();
						return true;
					}
					else
					{
						//insert command failed to prepare
						close();
						return false;
					}
				}
				else
				{
					//username is unavailable
					close();
					return false;
				}
			}
		}
		close();
	}
	else
	{
		//couldn't open db

		return false;
	}
	return false;
}
bool DatabaseManager::loginUser(std::string username, std::string password)
{
	//check if username exist
		//if it exist then check password
		//if password works, return true
		//if password fails, return false
	//if username doesnt exist login fail

	const char *name = username.c_str();
	const char *pass = password.c_str();
	if (open())
	{
		char *zErrMsg = 0; // error message
		sqlite3_stmt *stmt; //statement
		const char *pzTest; 
		char *szSQL; // actual raw sql
		
		//make sure that the user name exist
		szSQL = "SELECT COUNT(username) FROM user WHERE username = ? AND password = ?;";
		
		// perparing sql stmt
		int rc = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt, &pzTest);
		
		//if sucessfully prepared bind values and proceed
		if (rc == SQLITE_OK)
		{
			sqlite3_bind_text(stmt, 1, name, strlen(name), 0);
			sqlite3_bind_text(stmt, 2, pass, strlen(pass), 0);
			//execute statement;
			int result = sqlite3_step(stmt);
			
			//if a result is generated
			if (result == SQLITE_ROW)
			{
				//if result is greater than 1 then proceed
				int i = sqlite3_column_int(stmt, 0);
				if ( i == 1)
				{
					close();
					return true;
				}
				else
				{
					close();
					return false;
				}
			}
		}
		close();
	}
	else
	{
		//couldn't open db
		
		return false;
	}
	return false;
}
std::vector<std::string> DatabaseManager::getFriendsList(std::string username)
{
	//return a vector of users that are friends with the user
	std::vector<std::string> friendslist;
	const char *name = username.c_str();
	if (open())
	{
		char *zErrMsg = 0; // error message
		sqlite3_stmt *stmt; //statement
		const char *pzTest;
		char *szSQL; // actual raw sql
		//find people you are friends with
		szSQL = "SELECT friend FROM friends WHERE username = ?;";
		int rc = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt, &pzTest);
		if (rc == SQLITE_OK)
		{
			sqlite3_bind_text(stmt, 1, name, strlen(name), 0);
			int results = 0;
			while (true)
			{
				results = sqlite3_step(stmt);
				if (results == SQLITE_ROW)
				{
					//add them to the friendslist
					friendslist.push_back((char*)sqlite3_column_text(stmt, 0));
				}
				else
				{
					break;
				}
			}
			sqlite3_finalize(stmt);
		}
		close();
	}
	//return friends list
	return friendslist;
}

//returns userinfor in a wrapper class
UserInfo DatabaseManager::getUserInfo(std::string username)
{
	const char *name = username.c_str();
	
	if (open())
	{
		char *zErrMsg = 0; // error message
		sqlite3_stmt *stmt; //statement
		const char *pzTest;
		char *szSQL; // actual raw sql
		//get relevent data, do not retrieve password!
		szSQL = "SELECT highscore,gamesplayed,gameswon FROM user WHERE username = ?";
		int rc = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt, &pzTest);
		if (rc == SQLITE_OK)
		{
			sqlite3_bind_text(stmt, 1, name, strlen(name), 0);
			int result = sqlite3_step(stmt);
			
			if (result = SQLITE_ROW)
			{
				//create a userinfo wrapper class with all the statistics of user.
				UserInfo user = UserInfo(username, sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2));
				sqlite3_finalize(stmt);
				close();
				return user;
			}
		}
		close();
	}
	//return a userinfo class for the user based on username
	return UserInfo();
}

//updates a players game record
bool DatabaseManager::updateUserGames(std::string username, bool wonned)
{
	//find username in database and update the column
	const char *name = username.c_str();
	if (open())
	{
		char *zErrMsg = 0; // error message
		sqlite3_stmt *stmt; //statement
		const char *pzTest;
		char *szSQL; // actual raw sql

		//if they wonned, then increse their gameswon as well
		if (wonned)
		{
			szSQL = "UPDATE user SET gamesplayed = gamesplayed + 1 , gameswon = gameswon + 1 WHERE username = ?;";
		}
		else
		{
			szSQL = "UPDATE user SET gamesplayed = gamesplayed + 1 WHERE username = ?;";
		}
		int rc = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt, &pzTest);
		if (rc == SQLITE_OK)
		{
			sqlite3_bind_text(stmt, 1, name, strlen(name), 0);
			int result = sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			close();
			return true;
		}
		close();
	}
	
	return false;
}

//adds a friend connection
bool DatabaseManager::addFriend(std::string username, std::string mfriend)
{
	//convert string into const char
	const char *name = username.c_str();
	const char *bud = mfriend.c_str();

	//if this user is already there don't add else, add both combination
	if (open())
	{
		char *zErrMsg = 0; // error message
		sqlite3_stmt *stmt; //statement
		sqlite3_stmt *stmt2;
		
		const char *pzTest;
		char *szSQL; // actual raw sql
		//check if they already have a connection
		szSQL =  "SELECT COUNT(username) FROM friends WHERE username = ? AND friend = ?;";
		int rc = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt, &pzTest);

		//if sucessfully prepared bind values and proceed
		if (rc == SQLITE_OK)
		{
			sqlite3_bind_text(stmt, 1, name, strlen(name), 0);
			sqlite3_bind_text(stmt, 2, bud, strlen(bud), 0);
			//execute statement;
			int result = sqlite3_step(stmt);
			int check = sqlite3_column_int(stmt, 0);
			sqlite3_finalize(stmt);
			//if they arn't friends already make them friends
			if (check == 0)
			{
				szSQL = "INSERT INTO friends VALUES(?,?);";
				int rd = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt2, &pzTest);

				if (rd == SQLITE_OK)
				{
					//makes first connection
					sqlite3_bind_text(stmt2, 1, name, strlen(name), 0);
					sqlite3_bind_text(stmt2, 2, bud, strlen(bud), 0);
					sqlite3_step(stmt2);
					sqlite3_reset(stmt2);

					//makes second connection
					sqlite3_bind_text(stmt2, 1, bud, strlen(bud), 0);
					sqlite3_bind_text(stmt2, 2, name, strlen(name), 0);
					sqlite3_step(stmt2);
					sqlite3_finalize(stmt2);
					close();
					return true;
				}
			}
			else
			{
				close();
				return false;
			}
		}

			close();
	}
	
	return false;
}

//updates a players highscore
bool DatabaseManager::updateNewHighScore(std::string username, int newScore)
{
	const char *name = username.c_str();
	if (open())
	{
		char *zErrMsg = 0; // error message
		sqlite3_stmt *stmt; //statement
		const char *pzTest;
		char *szSQL; // actual raw sql
		//updates with a new highscore	
		szSQL = "UPDATE user SET highscore = ? WHERE username = ?;";
		
		int rc = sqlite3_prepare_v2(database, szSQL, strlen(szSQL), &stmt, &pzTest);
		if (rc == SQLITE_OK)
		{
			sqlite3_bind_int(stmt, 1, newScore);
			sqlite3_bind_text(stmt, 2, name, strlen(name), 0);
			int result = sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			close();
			return true;
		}
		close();
	}

	return false;
}