#include "InstructionScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"

InstructionScreen::InstructionScreen()
    :backSection(new Section(0.0f,
	                     0.0f,
						 420.0f,
						 570.0f,
                         GraphicsManager::getInstance()->buttonColor)),

     section(new Section(0.0f,
                         0.0f,
                         400.0f,
                         550.0f)),

     title(new TextBox("HELP",
                       0.0f,
                       -200.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

     instruction(new TextBox("Block Buddies is a multiplayer match 3 game similar to Tetris Attack. Match 3 similar blocks together to clear them from your board. Clearing 4 or more together also sends blocks to the opponent.\n\nPress the up, down, left, or right arrow keys to move the cursor.\n\nPress W, A, S, or D to swap the current block with the top, left, bottom, or right respective block.",
                             0.0f,
                             0.0f,
                             300.0f,
                             Alignments::CENTER,
                             false,
                             true)),

     home(new Button(Screens::HOME,
                     "BACK",
                     0.0f,
                     200.0f,
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