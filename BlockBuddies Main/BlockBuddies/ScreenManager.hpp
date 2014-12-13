#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Screen.hpp"
#include <map>

// ScreenManager takes care of switching screens and holds
// a currentScreen variable
class ScreenManager
{
public:
    static ScreenManager* getInstance();

    void init();
    void update();
    void draw();
    void switchScreen(const Screens toScreen);
    void addScreen(const Screens toScreen);
    void popScreen();
    void closeGame();

    // currentScreens is a vector of the current screens displayed on screen
    // The reason why we need to make it a structure instead of just one Screen*
    // is because we may have overlay screens, such as the CloseScreen put
    // on top of other screens
    std::vector<Screen*> currentScreens;

	//allow the screen to shakeit

	void shake(int);
private:
    // All the Screens are created beforehand so they don't have to be reinstantiated every single time
    std::map <Screens, Screen*> screens;

    ScreenManager(){};
    ScreenManager(ScreenManager const&){};
    ScreenManager& operator=(ScreenManager const&){};

    static ScreenManager* instance;

	//Timers to decide when to stop the screen shake
	sf::Clock clock;
	sf::Time shakeTimer;
	sf::Vector2f initPos;
	sf::View view;
};

#endif//SCREENMANAGER_HPP