#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/Graphics.hpp"

class Game
{
public:
	Game();
	void run();
	void update();
	void draw();

	bool isRunning = true;
};

#endif//GAME_HPP