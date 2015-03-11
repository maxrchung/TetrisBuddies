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
#include "TextureManager.hpp"
#include "Avatar.h"
#include "Mascot.h"
class MultiplayerScreen : public Screen
{
public:
	MultiplayerScreen();
	void update();
	void draw();
	void reload();
	void enter();
private:
	bool firstRun = true;
	sf::Clock timePiece;
	sf::Time currentTime;
	//Display info
	TextBox* playerOneName;
	TextBox* playerTwoName;
	TextBox* timer;
	TextBox* nextRowLeft;
	TextBox* nextRowL2;
	TextBox* nextRowRight;
	TextBox* nextRowR2;
	TextBox* isPaused;
	TextBox* nextRowIn;
	TextBox* comboCounter;

	std::vector <std::pair<int, int>> dangerColumns;
	std::vector <int> dangerMark;
	unsigned int winX;
	unsigned int winY;
	int gameScreenHeight;
	int gameScreenWidth;
	int blockSize;
	int dangerColumnCounter;
	CursorHandler *ch;
	CursorHandler *ch2;
	sf::RectangleShape p1Blocks[GameStateObject::boardHeight][GameStateObject::boardWidth];
	sf::RectangleShape p2Blocks[GameStateObject::boardHeight][GameStateObject::boardWidth];
	sf::RectangleShape p1NextBlocks[GameStateObject::boardWidth];
	sf::RectangleShape p2NextBlocks[GameStateObject::boardWidth];
	sf::RectangleShape p1Outline, p2Outline;
	sf::RectangleShape tempRowRec1, tempRowRec2;
	sf::Sprite blockShape;
	GameStateObject p1GSO;
	GameStateObject p2GSO;
	bool pressed, pressed2;
	bool blockSwitch;
	void initGame();
	bool reset;
	void updateBlocks();
	sf::Sound swapSound;
	const int SCREENWIDTH = 400;
	const int SCREENHEIGHT = 500;

	Avatar* p1Avatar;
	Avatar* p2Avatar;

	Mascot miku1;
	Mascot miku2;

	sf::Clock clock;
	sf::Time lastFrameTime;
};
#endif//MULTIPLAYERSCREEN_HPP