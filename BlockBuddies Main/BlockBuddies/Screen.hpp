#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Selectable.hpp"
#include <vector>
#include "Button.hpp"
#include "UIElement.hpp"
#include <SFML\Audio.hpp>
#include "Fade.hpp"

class Button;

// This Screens enum is an indicator of where a button is going to go.
// For example, the RegisterButton, when pressed, will take the player
// to the RegisterScreen. The reason why I chose to use an enum over char*
// was because I can do a pretty nicely formatted switch-case for the 
// switchScreen function. It should also be a little more efficient
enum Screens 
{ 
    LOGIN, 
    REGISTER,
    HOME,
    PROFILE,
    GAMETYPE,
    GAME,
    RESULT,
    OFFLINEHOME,
    OFFLINEGAMETYPE,
    OFFLINERESULT,
    CLOSE,
    OFFLINECLOSE,
    MULTIPLAYER,
	ONLINESINGLE,
    QUEUE,
    NOTIFICATION,
    INSTRUCTION,
    MULTIPLAYERRESULT,
    NONE
};

// Parent Screen that all other Screens inherit off of
class Screen
{
public:
    Screen();
	virtual void update();
	virtual void draw();
    virtual void reload();
    void deselect();
    void deactivate();
    Button* close;
    Fade fade;

protected:
	std::vector <UIElement*> UIElements;
    std::vector <Selectable*> selectables;
};

#endif//SCREEN_HPP