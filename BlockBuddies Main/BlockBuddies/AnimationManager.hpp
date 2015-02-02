#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "SFML/Graphics.hpp"
#include <vector>

class AnimationManager
{
public:
	static AnimationManager* getInstance();
	void init();
	void update();
	void draw();
	void add(sf::RectangleShape r, sf::RectangleShape r2);
private:
	void swap();
	std::vector <sf::RectangleShape> s;
	sf::Time time;
	sf::Clock clock;
	sf::Color c1, o1, c2, o2;
	int blockx, blocky, blockx2, blocky2;
	bool stop;
	int fade;
	static AnimationManager* instance;
};

#endif//ANIMATIONMANAGER_HPP