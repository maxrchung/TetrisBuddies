#ifndef GAMETYPESCREEN_HPP
#define GAMETYPESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

// Screen that displays the available gametypes to play
class GameTypeScreen : public Screen
{
public:
	GameTypeScreen();
	void update();
	void draw();

private:
	std::vector<Button*> buttons;
};

#endif//GAMETYPESCREEN_HPP