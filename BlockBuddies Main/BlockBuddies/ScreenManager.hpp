#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screen.hpp"

class ScreenManager
{
public:
	static ScreenManager* getInstance();

	void init();
	void switchScreen(Screen* toScreen);
	Screen* currentScreen;
private:
	ScreenManager(){};
	ScreenManager(ScreenManager const&){};
	ScreenManager& operator=(ScreenManager const&){};

	static ScreenManager* instance;
};

#endif//SCREENMANAGER_HPP