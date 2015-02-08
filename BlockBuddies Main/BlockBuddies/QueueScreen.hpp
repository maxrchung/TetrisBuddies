#ifndef QUEUESCREEN_HPP
#define QUEUESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "Section.hpp"

// Screen to login with account
class QueueScreen : public Screen
{
public:
	QueueScreen();

    void update();
	void draw();
    void reload();
    void foundGame();

private:
    Section* backSection;
	// All the various parts we create
	Section* section;
	TextBox* title;
	TextBox* status;

    Button* cancel;
    sf::Clock loadingTimer;
    int ellipsesCounter = 0;
    int reverse = 1;
    sf::Clock foundTimer;
    bool loadingGame = false;
};

#endif//QUEUESCREEN_HPP