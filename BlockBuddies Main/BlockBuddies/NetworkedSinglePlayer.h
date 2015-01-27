#pragma once
#include "Screen.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "CursorHandler.hpp"
#include "GameStateObject.hpp"
#include "ClientManager.h"
#include "UIElement.hpp"
#include "TextBox.hpp"

#include <vector>
#include <tuple>
#include <iostream>



class NetworkedSinglePlayer : public Screen
{
public:
	NetworkedSinglePlayer();
	~NetworkedSinglePlayer();
	void update();
	void draw();
	sf::RectangleShape blocks[GameStateObject::boardHeight][GameStateObject::boardWidth];

	

private:

	typedef std::tuple<int, int> blocksWT;
	std::vector <blocksWT> blockToCheck;
	sf::Color first;
	sf::Color second;
	int dur = 400;
	sf::Clock clocks[20][16];
	unsigned index = 0;
	bool remove = false;
	
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
	int blockSizeX;
	int blockSizeY;
	void initGame();
	bool reset;
	sf::Sound swapSound;
	TextBox* username;
	TextBox* score;
	TextBox* highScore;
	TextBox* name;
};

