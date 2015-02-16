#ifndef MULTIPLAYERSCREEN_HPP
#define MULTIPLAYERSCREEN_HPP

#include "Screen.hpp"
#include "GraphicsManager.hpp"
#include "ScreenManager.hpp"
#include "CursorHandler.hpp"
#include "GameStateObject.hpp"
#include "ClientManager.h"
#include "UIElement.hpp"
#include "TextBox.hpp"
#include "SoundManager.h"
#include "InputManager.hpp"


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
	sf::RectangleShape p1Blocks[GameStateObject::boardHeight][GameStateObject::boardWidth];
	sf::RectangleShape p2Blocks[GameStateObject::boardHeight][GameStateObject::boardWidth];
	sf::RectangleShape p1Outline, p2Outline;
	GameStateObject p1GSO;
	GameStateObject p2GSO;
	bool pressed, pressed2;
	bool blockSwitch;
	void initGame();
	bool reset;
	int blockSizeX;
	int blockSizeY;
	void updateBlocks();
	sf::Sound swapSound;
	const int SCREENWIDTH = 400;
	const int SCREENHEIGHT = 500;
};
#endif//MULTIPLAYERSCREEN_HPP