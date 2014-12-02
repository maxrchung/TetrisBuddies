#ifndef PROFILESCREEN_HPP
#define PROFILESCREEN_HPP
#include "TextBox.hpp"
#include "Screen.hpp"
#include "Button.hpp"
#include "Section.hpp"

// Screen that displays the logged in user's statistics
// and stats. In the future we may enhance this to allow
// for searching up rankings and the likes
class ProfileScreen: public Screen
{
public:
	ProfileScreen();
	void update();
	void draw();

private:
	Section* section;
	TextBox* usernameTag;
	TextBox* highscoreTag;
	TextBox* gamesplayedTag;
	TextBox* gameswonTag;

	TextBox* nameTag;
	TextBox* hsTag;
	TextBox* gpTag;
	TextBox* gwTag;

    Button* home;
    Button* profile;
    Button* gameType;
};

#endif//PROFILESCREEN_HPP