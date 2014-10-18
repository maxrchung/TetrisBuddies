#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screen.hpp"

class ScreenManager
{
public:
	static void switchScreen(Screen& toScreen);
	static Screen& currentScreen;
};

#endif//SCREENMANAGER_HPP