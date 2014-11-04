#ifndef PROFILESCREEN_HPP
#define PROFILESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

// Screen that displays the logged in user's statistics
// and stats. In the future we may enhance this to allow
// for searching up rankings and the likes
class ProfileScreen: public Screen
{
public:
	ProfileScreen();
	void update();

	std::vector<Button*> buttons;
};

#endif//PROFILESCREEN_HPP