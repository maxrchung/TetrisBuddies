#include "Mascot.h"


Mascot::Mascot()
{
	sf::Texture* animSpriteTexture = _getTexture("Textures/mikuSprite.png");
	animSpriteTexture->setSmooth(true);

	miku.setTexture(*animSpriteTexture);
	miku.addAnim("idle", 0, 0, 20, 20, 10, true);
	miku.setFrameSize(59, 64);
	miku.playAnim("idle");
	std::function<void()> foo = [&](){ 	miku.setFrameSize(59, 64);
	miku.playAnim("idle"); };
	miku.addAnim("scream", 0, 235, 8, 8, 10, false, foo);

}


Mascot::~Mascot()
{
}

void Mascot::cheer()
{
	miku.setFrameSize(85, 66);
	miku.playAnim("scream");
}
void Mascot::update(float deltaTime)
{
	miku.update(deltaTime);
}

void Mascot::draw(sf::RenderWindow& window)
{
	window.draw(miku);
}