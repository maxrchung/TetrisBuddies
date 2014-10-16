#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screen.hpp"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	void switchScreen(Screen* screen);
	Screen* currentScreen;
};

#endif//SCREENMANAGER_HPP