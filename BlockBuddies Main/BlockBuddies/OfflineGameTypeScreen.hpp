#ifndef OFFLINEGAMETYPESCREEN_HPP
#define OFFLINEGAMETYPESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "Section.hpp"

// Screen that displays the available gametypes to play
class OfflineGameTypeScreen : public Screen
{
public:
    OfflineGameTypeScreen();
    void update();
    void draw();

private:
    Section* section;
    Button* home;
    Button* gameType;
    Button* game;
};

#endif//OFFLINEGAMETYPESCREEN_HPP