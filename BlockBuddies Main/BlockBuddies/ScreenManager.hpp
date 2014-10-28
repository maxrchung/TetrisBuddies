#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screen.hpp"

// This Screens enum is an indicator of where a button is going to go.
// For example, the RegisterButton, when pressed, will take the player
// to the RegisterScreen. The reason why I chose to use an enum was because
// I can do a pretty nicely formatted switch-case for the switchScreen
// function. It should also be a little more efficient than using char*.
enum Screens {LOGIN, REGISTER, HOME, PROFILE, GAMETYPE, GAME};

class ScreenManager
{
public:
	static ScreenManager* getInstance();

	void init();
	void switchScreen(const Screens toScreen);
	Screen* currentScreen;
private:
	ScreenManager(){};
	ScreenManager(ScreenManager const&){};
	ScreenManager& operator=(ScreenManager const&){};

	static ScreenManager* instance;
};

#endif//SCREENMANAGER_HPP