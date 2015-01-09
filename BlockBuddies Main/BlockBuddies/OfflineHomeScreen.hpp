#ifndef OFFLINEHOMESCREEN_HPP
#define OFFLINEHOMESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "Section.hpp"
#include "TextBox.hpp"

class OfflineHomeScreen: public Screen
{
public:
    OfflineHomeScreen();
    void update();
    void draw();

private:
    Section* backSection;
    Section* section;
    TextBox* welcome;
    Button* offlineHome;
    Button* offlineGameType;
};

#endif//OFFLINEHOMESCREEN_HPP