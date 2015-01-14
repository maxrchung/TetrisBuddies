#include "BlockMeteor.hpp"
#include "GraphicsManager.hpp"
#include <stdlib.h>

BlockMeteor::BlockMeteor()
{
}

void BlockMeteor::update()
{
    boundingRect.setPosition(boundingRect.getPosition().x, boundingRect.getPosition().y + speed);
}

void BlockMeteor::draw()
{
    GraphicsManager::getInstance()->window.draw(boundingRect);
}