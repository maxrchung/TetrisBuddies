
#include "AnimatedSprite.h"
#include <cstdio>

AnimatedSprite::AnimatedSprite() : timeSinceLastFrame(0), currentFrame(0) {
	//act like a regular sprite for now
	this->addAnim("default");
	this->playAnim("default");
}

void AnimatedSprite::setFrameSize(int width, int height) {
	frameSize.x = width;
	frameSize.y = height;
	showFrame(0);
}


void AnimatedSprite::setBorderSize(int width, int height) {
	borderSize.x = width;
	borderSize.y = height;
	showFrame(0);
}

void AnimatedSprite::update(float deltaTime) {
	//don't play animations with negative framerate
	if (currentAnim->framerate < 0) return;

	//no need to play finished animation
	if (!currentAnim->isCyclic && (currentFrame == currentAnim->numFrames - 1)) return;

	//accumulate time
	timeSinceLastFrame += deltaTime;

	//do we need to change frames?
	if (((1.f / currentAnim->framerate) > timeSinceLastFrame)) return;

	//advance frame, skipping some if delta time > frametime
	int frameAdvance = int(timeSinceLastFrame * currentAnim->framerate);
	currentFrame += frameAdvance;

	//subtract frame interval(s)
	timeSinceLastFrame -= frameAdvance * (1.f / currentAnim->framerate);

	//cyclic wraparound / acyclic clamping
	while (currentFrame > currentAnim->numFrames - 1) {
		if (currentAnim->isCyclic) {
			currentFrame -= currentAnim->numFrames;
		}
		else {
			currentFrame = currentAnim->numFrames - 1;
		}
	}

	//run finished callback if we've just hit the last frame
	if (!currentAnim->isCyclic && (currentFrame == currentAnim->numFrames - 1)) {
		currentAnim->finishedFunc();
	}

	showFrame(currentFrame);
}

//default params: int startX = 0, int startY = 0, int numFrames = 1, int numPerRow = 1, float framerate = 1, bool isCyclic = true, callbackFunc = [] {}
void AnimatedSprite::addAnim(std::string name, int startX, int startY, int numFrames, int numPerRow, float framerate, bool isCyclic, std::function<void()> finishedFunc) {
	AnimSprAnimation * newAnim = new AnimSprAnimation;
	newAnim->name = name;
	newAnim->numFrames = numFrames;
	newAnim->startPos = sf::Vector2i(startX, startY);
	newAnim->numPerRow = numPerRow;
	newAnim->framerate = framerate;
	newAnim->isCyclic = isCyclic;
	newAnim->finishedFunc = finishedFunc;

	AnimsList.insert(std::make_pair(name, newAnim));
}

bool AnimatedSprite::playAnim(std::string name) {
	auto iter = AnimsList.begin();
	iter = AnimsList.find(name);

	if (iter != AnimsList.end()) {
		currentAnim = iter->second;
		currentFrame = 0;
		showFrame(0);

		return true;
	}

	return false;
}

std::string AnimatedSprite::getCurrentAnim() {
	return currentAnim->name;
}

void AnimatedSprite::showFrame(unsigned int frameNum) {
	//if (frameNum > currentAnim->numFrames - 1) return;

	sf::Vector2i frameCoordinates(frameNum % currentAnim->numPerRow, frameNum / currentAnim->numPerRow);
	sf::Vector2i offsetSize = frameSize + borderSize;
	sf::Vector2i framePos = currentAnim->startPos + sf::Vector2i(frameCoordinates.x * offsetSize.x, frameCoordinates.y * offsetSize.y);

	setTextureRect(sf::IntRect(framePos, frameSize));
}

sf::Vector2i AnimatedSprite::getFrameSize()
{
	return frameSize;
}