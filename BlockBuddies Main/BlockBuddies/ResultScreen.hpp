#ifndef RESULTSCREEN_HPP
#define RESULTSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "Section.hpp"
#include "TextBox.hpp"

class ResultScreen : public Screen
{
	public:
		ResultScreen();
		void update();
		void draw();
        void reload();
	private:
        Section* backSection;
        Section* section;
        TextBox* title;
        TextBox* status;
        TextBox* scoreTag; // "Score"
        TextBox* score; // Ex. "5000"
        Button* home;
        Button* game;
		std::string scoreString;
		bool updated;
};
#endif REULSTSCREEN_HPP //ResultScreen.hpp