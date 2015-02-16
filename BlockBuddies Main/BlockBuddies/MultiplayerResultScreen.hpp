#ifndef MULTIPLAYERRESULTSCREEN_HPP
#define MULTIPLAYERRESULTSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "Section.hpp"
#include "TextBox.hpp"

class MultiplayerResultScreen : public Screen
{
	public:
		MultiplayerResultScreen();
		void update();
		void draw();
        void reload();
	private:
        Section* backSection;
        Section* section;
        TextBox* title;
        TextBox* status;
        TextBox* result;
        Button* home;
        Button* game;
};
#endif// MULTIPLAYERRESULTSCREEN_HPP