#ifndef INSTRUCTIONSCREEN_HPP
#define INSTRUCTIONSCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "Section.hpp"
#include "TextBox.hpp"

// Screen you get into when you first login or register an account
// Basically the central hub to take you to other parts
class InstructionScreen: public Screen
{
public:
	InstructionScreen();
	void update();
	void draw();

private:
    Section* backSection;
	Section* section;
	TextBox* welcome;
	Button* home;
};

#endif//INSTRUCTIONSCREEN_HPP