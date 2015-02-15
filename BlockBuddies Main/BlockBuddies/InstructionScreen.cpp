#include "InstructionScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"

InstructionScreen::InstructionScreen()
    :backSection(new Section(0.0f,
	                     0.0f,
						 420.0f,
						 620.0f,
                         GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
                         0.0f,
                         400.0f,
                         600.0f)),

     title(new TextBox("HELP",
                       0.0f,
                       -225.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

     instruction(new TextBox("Block Buddies is a match 3 game similar to Tetris Attack. Match 3 similar blocks together to clear them from the board. In multiplayer mode, clearing 4 or more together also sends blocks to the opponent.\n\nPress the up, down, left, or right arrow keys to move the cursor.\n\nPress W, A, S, or D to swap the current block with the top, left, bottom, or right respective block.\n\nPress Q to give yourself an extra layer of bottom blocks.",
                             0.0f,
                             0.0f,
                             300.0f,
                             Alignments::CENTER,
                             false,
                             true)),

     home(new Button(Screens::HOME,
                     "Back",
                     0.0f,
                     225.0f,
                     150.0f,
                     50.0f))
{
    UIElements.push_back(backSection);
    UIElements.push_back(section);
    UIElements.push_back(title);
    UIElements.push_back(instruction);
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