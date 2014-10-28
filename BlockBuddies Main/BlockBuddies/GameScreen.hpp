#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.hpp"

class GameScreen: public Screen
{
public:
	GameScreen();
	void update();
	void draw();
};

#endif//GAMESCREEN_HPP