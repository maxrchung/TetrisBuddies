#include "ResultScreen.hpp"

ResultScreen::ResultScreen()
	: buttons({ new Button(Screens::HOME,
	"Home",
	0.0f,
	125.0f,
	150.0f,
	50.0f),

	new Button(Screens::GAME,
	"Play Again?",
	0.0f,
	200.0f,
	150.0f,
	50.0f) })
{

}

void ResultScreen::update()
{

	for (auto i : buttons)
	{
		if (i->label.getString() == "Home")
		{
			if (i->isActivated)
			{
				ScreenManager::getInstance()->switchScreen(HOME);
				break;
			}
		}
		else if (i->label.getString() == "Play Again?")
		{
			if (i->isActivated)
				ScreenManager::getInstance()->switchScreen(GAME);
			break;
		}
	}
}

void ResultScreen::draw()
{
}