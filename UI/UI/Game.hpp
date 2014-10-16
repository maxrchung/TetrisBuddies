#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/Graphics.hpp"
#include "ScreenManager.hpp"

class Game
{
public:
	Game();
	~Game();
	void run();
	void update();
	void draw();

	ScreenManager screenManager;
	sf::Clock fpsClock;
	bool isRunning = true;
};

#endif//GAME_HPP