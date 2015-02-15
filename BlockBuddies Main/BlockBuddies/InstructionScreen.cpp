#include "InstructionScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"

InstructionScreen::InstructionScreen()
    :backSection(new Section(0.0f,
	                     0.0f,
						 1020.0f,
						 620.0f,
                         GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
                         0.0f,
                         1000.0f,
                         600.0f)),

     welcome(new TextBox("Welcome to Block Buddies!",
                         0.0f,
                         0.0f,
                         300.0f)),

     home(new Button(Screens::HOME,
                     "",
                     -175.0f,
                     -225.0f,
                     150.0f,
                     50.0f))

{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(welcome);
    UIElements.push_back(home);

    selectables = { home };
}

void InstructionScreen::update()
{
    // Calls base update()
    Screen::update();

    if (home->isActivated ||
        (InputManager::getInstance()->enter && home->isSelected))
            ScreenManager::getInstance()->switchScreen(home->toScreen);
}

void InstructionScreen::draw()
{
    // Calls base draw()
    Screen::draw();
}