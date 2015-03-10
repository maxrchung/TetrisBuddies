#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <vector>

class AnimationManager
{
public:
	static AnimationManager* getInstance();
	void init();
	void update();
	void draw();
	void addSwap(sf::RectangleShape r, sf::RectangleShape r2);
	void addClear(sf::RectangleShape b);
	void addDanger(sf::RectangleShape d);
	void setBlockSize(int size);
	void setClearingAdd();
	void clearDangerBlocks();
	void pauseAnimation();
	void unpauseAnimation();
	void setTextureDanger();
private:
	void swap();
	void clear();
	void danger();
	void setTextureSwap(int index);
	std::vector <sf::Sprite> swapSprites;
	std::vector <sf::RectangleShape> s;
	std::vector <std::pair<sf::Sprite, int >> dangerSprites;
	std::vector <sf::Color> dangerBlocks;
	std::vector <std::pair<sf::RectangleShape, int>> clearBlocks;
	std::vector <sf::RectangleShape> ctemp;
	std::vector <float> acceleration;
	std::vector <sf::Time> ctime;
	std::vector <sf::Clock> cclock;
	sf::Time stime;
	sf::Clock sclock;
	sf::Sound clearSound, matchFlashing, matchFlashing2, matchFlashing3;
	int blockx, blocky, blockx2, blocky2;
	int blockSize;
	bool stop, dangerUp, clearAddFinish, pause;
	float speed;
	static AnimationManager* instance;
};

#endif//ANIMATIONMANAGER_HPP