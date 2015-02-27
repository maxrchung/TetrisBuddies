#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/Graphics.hpp"
#include <thread>

// The overarching class in charge of basically everything
class Game
{
public:
    static Game* getInstance();
    void init();
	void run();
	void update();
    void cursorUpdate();
	void draw();
    void startLoadingThread();
    void loadingUpdate();
    void stopLoadingThread();

    std::thread loadingThread;
    // Indicates whether the game is loading or not
    bool isLoading = false;

	bool isRunning = true;

    sf::Clock cursorHideClock;
    float cursorHideTimer = 0.0f;
    sf::Vector2i prevMousePos;

private:
    Game(){};
    Game(Game const&){};
    Game& operator=(Game const&){};

    static Game* instance;
};

#endif//GAME_HPP