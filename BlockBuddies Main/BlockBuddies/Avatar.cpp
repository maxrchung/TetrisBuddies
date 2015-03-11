#include "Avatar.h"


Avatar::Avatar(sf::Vector2f pos, bool isPlayer1) : mPos(pos), isP1(isPlayer1)
{
	//set up vars
	velocity = 100;
	distance = 800;
	//grab textures
	if (isP1)
	avatarImage = _getTexture("Textures/ryuSprite.png");
	else
	avatarImage = _getTexture("Textures/evilRyuSprite.png");
	//set up sprite
	sprite.setPosition(mPos);
	sprite.setTexture(*avatarImage);
	sprite.setFrameSize(74, 104);
	sprite.addAnim("idle", 0, 209, 11, 6, 5, true);
	std::function<void()> goToIdle = [&](){sprite.setFrameSize(72, 104); sprite.playAnim("idle"); };
	std::function<void()> fireHaduken = [&](){haduken(); sprite.setFrameSize(72, 104); sprite.playAnim("idle"); };
	
	sprite.addAnim("spawn", 0, 0, 16, 8, 5, false, goToIdle);
	sprite.addAnim("haduken", 0, 416, 5, 5, 5, false, fireHaduken);
	sprite.addAnim("SpHaduken", 0, 520, 12, 6, 10, false, fireHaduken);
	sprite.playAnim("spawn");

}


Avatar::~Avatar()
{
	for (auto it = hadukenList.begin(); it != hadukenList.end(); it++)
		delete (*it);
}

void Avatar::update(float deltaTime)
{
	//update sprite
	sprite.update(deltaTime);
	//update hadukens
	for (auto it = hadukenList.begin(); it != hadukenList.end();)
	{
		(*it)->update(deltaTime);
		//check if they have gone too far
		if (std::abs((*it)->getPosition().x - mPos.x) > distance)
		{
			auto itToErase = it;
			it++;
			delete (*itToErase);
			hadukenList.erase(itToErase);
			continue;
		}
		//else move them forward
		//if player one fire to the right
		//else go to the left
		if (isP1)
			(*it)->move(sf::Vector2f((velocity*deltaTime), 0));
		else
			(*it)->move(sf::Vector2f((-velocity*deltaTime), 0));

		it++;
	}
}
void Avatar::draw(sf::RenderWindow& window)
{
	//draw our hadukens
	for (auto it = hadukenList.begin(); it != hadukenList.end(); it++) {
		window.draw((**it));
	}
	//draw the sprite
	window.draw(sprite);
}
void Avatar::haduken()
{
	//sprite.setFrameSize(114, 92);
	//76 37
	AnimatedSprite* newSprite = new AnimatedSprite();
	newSprite->setTexture(*_getTexture("Textures/Haduken.png"));
	newSprite->setFrameSize(76, 37);
	newSprite->setScale(sprite.getScale());
	centerOrigin(*newSprite);
	if (isP1)
		newSprite->setPosition(sf::Vector2f(sprite.getPosition().x + (sprite.getGlobalBounds().width*0.75),
		sprite.getPosition().y + sprite.getGlobalBounds().height / 3));
	else
		newSprite->setPosition(sf::Vector2f(sprite.getPosition().x - (sprite.getGlobalBounds().width*0.75),
		sprite.getPosition().y + sprite.getGlobalBounds().height / 3));

	newSprite->addAnim("glow", 0, 0, 8, 8, 10);
	newSprite->playAnim("glow");
	hadukenList.push_back(newSprite);

}
