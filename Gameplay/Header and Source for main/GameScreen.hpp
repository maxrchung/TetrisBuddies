#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.hpp"
#include "GraphicsManager.hpp"
#include "BlockHandler.hpp"
#include "CursorHandler.hpp"
// This is the Screen for the actual game itself
// We will most likely need to make separate games for separate game types,
// i.e. ranked, casual, and solo play, but for now we have this single GameScreen
// here to use
class GameScreen: public Screen
{
public:
	GameScreen();
	void update();
	void draw();

private:
	BlockHandler *bh;
	CursorHandler *ch;
	bool pressed, pressed2;
	sf::RectangleShape rec;

};

#endif//GAMESCREEN_HPP