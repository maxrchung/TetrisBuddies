#ifndef RESULTSCREEN_HPP
#define RESULTSCREEN_HPP

#include <vector>
#include "Screen.hpp"
#include "Button.hpp"
#include "GraphicsManager.hpp"

class ResultScreen : public Screen
{
	public:
		ResultScreen();
		void update();
		void draw();
	private:
	std::vector<Button*> buttons;
};
#endif REULSTSCREEN_HPP //ResultScreen.hpp