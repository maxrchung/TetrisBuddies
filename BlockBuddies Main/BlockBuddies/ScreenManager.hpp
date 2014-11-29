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

    // currentScreens is a pointer to a vector of the currently displayed screen
    // The reason it is a vector is because we may have overlaying screens that pop-up
    // For example, one could be on the LoginScreen, and when the player presses the close button,
    // An overlaying screen pops up that'll signify whether they would like to logout, exit 
    // completely return to home, cancel, etc.
    Screen* currentScreen;

private:
    // All the Screens are created beforehand so they don't have to be reinstantiated every single time
    std::map <Screens, Screen*> screens;

    ScreenManager(){};
    ScreenManager(ScreenManager const&){};
    ScreenManager& operator=(ScreenManager const&){};

    static ScreenManager* instance;
};

#endif//SCREENMANAGER_HPP