#ifndef RESULTSSCREEN_HPP
#define RESULTSSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"

class ResultsScreen: public Screen
{
public:
	ResultsScreen();
	~ResultsScreen();

	Button gameLobbyButton(Screen* toScreen);
	Button homeButton(Screen* toScreen);
};

#endif//RESULTSSCREEN_HPP