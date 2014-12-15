#pragma once
#include "Screen.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "CursorHandler.hpp"
#include "GameStateObject.hpp"
#include "ClientManager.h"

class NetworkedSinglePlayer : public Screen
{
public:
	NetworkedSinglePlayer();
	~NetworkedSinglePlayer();
	void update();
	void draw();
private:
	CursorHandler *ch;
	bool pressed, pressed2;
	sf::RectangleShape rec;
	sf::Clock clock;
	sf::Time timer;
	unsigned int winX;
	unsigned int winY;
	int gameScreenHeight;
	int gameScreenWidth;
	GameStateObject gso;
	sf::RectangleShape blocks[GameStateObject::boardHeight][GameStateObject::boardWidth];
	int blockSizeX;
	int blockSizeY;
	void initGame();
	bool reset;
};

