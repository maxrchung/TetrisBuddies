#ifndef OFFLINERESULTSCREEN_HPP
#define OFFLINERESULTSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "Section.hpp"
#include "TextBox.hpp"

class OfflineResultScreen : public Screen
{
	public:
		OfflineResultScreen();
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
        Button* login;
        Button* offlineGame;
};
#endif//OFFLINERESULTSCREEN_HPP