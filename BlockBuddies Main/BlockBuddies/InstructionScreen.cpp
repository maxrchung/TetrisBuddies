#include "InstructionScreen.hpp"
#include "InputManager.hpp"
#include "ScreenManager.hpp"

InstructionScreen::InstructionScreen()
    :backSection(new Section(0.0f,
	                     0.0f,
						 420.0f,
						 570.0f,
                         GraphicsManager::getInstance()->buttonColor,
                         true)),

     section(new Section(0.0f,
                         0.0f,
                         400.0f,
                         550.0f)),

     title(new TextBox("INSTRUCTIONS",
                       0.0f,
                       -200.0f,
                       300.0f,
                       Alignments::CENTER,
                       true)),

     instruction(new TextBox("Block Buddies is a match 3 game similar to Tetris Attack. Match 3 similar blocks together to clear them from the board.\n\nPress the up, down, left, or right arrow keys to move the cursor.\n\nPress W, A, S, or D to swap the current block with the top, left, bottom, or right respective block.\n\nPress Q to give the board an extra layer of bottom blocks.",
                             0.0f,
                             0.0f,
                             300.0f,
                             Alignments::CENTER,
                             false,
                             true)),

     home(new Button(Screens::HOME,
                     "Back",
                     0.0f,
                     200.0f,
                     150.0f,
                     50.0f))
{
    // So we don't update/draw the close button when
    // this screen is on top
    close->isDisplayed = false;

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
    {
        deselect();
        deactivate();
        fade.state = FadeStates::FADING_OUT;
        InputManager::getInstance()->resetInput();
    }

    if(InputManager::getInstance()->escape)
    {
        deselect();
        deactivate();
        fade.state = FadeStates::FADING_OUT;
        InputManager::getInstance()->resetInput();
    }
}

void InstructionScreen::draw()
{
    // Used to provide a darkening layer between the last layer
    // and the layers before it
    sf::RectangleShape darken(sf::Vector2f((float)GraphicsManager::getInstance()->window.getSize().x,
                                           (float)GraphicsManager::getInstance()->window.getSize().y));
    darken.setFillColor(sf::Color(0, 0, 0, fade.value/1.25f));
    GraphicsManager::getInstance()->window.draw(darken);

    // Calls base draw()
    Screen::draw();
}