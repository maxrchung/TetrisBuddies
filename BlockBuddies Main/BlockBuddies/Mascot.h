#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "TextureManager.hpp"

class Mascot
{
public:
	Mascot();
	~Mascot();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void cheer();
	AnimatedSprite miku;
};

