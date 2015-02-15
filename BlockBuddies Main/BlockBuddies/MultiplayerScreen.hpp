#ifndef MULTIPLAYERSCREEN_HPP
#define MULTIPLAYERSCREEN_HPP

#include "Screen.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "CursorHandler.hpp"
#include "GameStateObject.hpp"

class MultiplayerScreen : public Screen
{
public:
	MultiplayerScreen();
	void update();
	void draw();
    void reload();
private:

	unsigned int winX;
	unsigned int winY;
	GameStateObject gso;
	int blockSizeX;
	int blockSizeY;

	CursorHandler *ch;
	sf::RectangleShape p1Blocks[20][16];
	sf::RectangleShape p2Blocks[20][16];
	sf::RectangleShape p1Outline, p2Outline;
	bool blockSwitch;
	const int SCREENWIDTH = 400;
	const int SCREENHEIGHT = 500;
};

#endif//MULTIPLAYERSCREEN_HPP