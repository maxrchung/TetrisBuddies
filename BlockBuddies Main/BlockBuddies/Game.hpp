#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/Graphics.hpp"

// The overarching class in charge of basically everything
class Game
{
public:
	Game();
	void run();
	void update();
	void draw();

	static bool isRunning;
};

#endif//GAME_HPP