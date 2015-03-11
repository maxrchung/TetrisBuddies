#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "TextureManager.hpp"
#include <list>

class Avatar
{
public:
	Avatar(sf::Vector2f pos, bool isP1);
	~Avatar();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	
	sf::Vector2f mPos;
	AnimatedSprite sprite;

	bool isP1;
	float velocity;
	float distance;
private:
	sf::Texture* avatarImage;
	std::list<AnimatedSprite*> hadukenList;
	void haduken();
};

