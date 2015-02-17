#include "AnimationManager.hpp"
#include "GraphicsManager.hpp"
#include <iostream>
AnimationManager* AnimationManager::instance;

AnimationManager* AnimationManager::getInstance()
{
	if (!instance)
		instance = new AnimationManager();

	return instance;
}

void AnimationManager::update()
{
	time = clock.getElapsedTime();
	swap();
	if (!s.empty())
		draw();
}

void AnimationManager::draw()
{
	GraphicsManager::getInstance()->window.draw(s.at(0));
	GraphicsManager::getInstance()->window.draw(s.at(1));
}

void AnimationManager::swap()
{	
	if (time.asMilliseconds() < 300 && !s.empty())
	{
		//swapping with top or bottom
		if (blockx == blockx2 && !stop)
		{
			if (blocky > blocky2) //this means swapping with the top block
			{
				if (s.at(0).getPosition().y > blocky2)
				{
					//25 is how far the blocks are from each other
					s.at(0).setPosition(blockx, s.at(0).getPosition().y - time.asSeconds()*25); 
					if (s.at(0).getPosition().y < blocky2)
						s.at(0).setPosition(blockx, blocky2);
				}
				else if (s.at(0).getPosition().y == blocky2)
				{
					s.at(1).setPosition(blockx, s.at(1).getPosition().y + time.asSeconds() * 25);
					if (s.at(1).getPosition().y > blocky)
					{
						s.at(1).setPosition(blockx2, blocky);
						stop = true;
					}
				}
			}
			else if (blocky < blocky2 && !stop) //this means swapping with the bottom block
			{
				if (s.at(0).getPosition().y < blocky2)
				{
					//25 is how far the blocks are from each other
					s.at(0).setPosition(blockx, s.at(0).getPosition().y + time.asSeconds() * 25);
					if (s.at(0).getPosition().y > blocky2)
						s.at(0).setPosition(blockx, blocky2);
				}
				else if (s.at(0).getPosition().y == blocky2)
				{
					s.at(1).setPosition(blockx, s.at(1).getPosition().y - time.asSeconds() * 25);
					if (s.at(1).getPosition().y < blocky)
					{
						s.at(1).setPosition(blockx2, blocky);
						stop = true;
					}
				}
			}//end else if
		}//end if

		//swapping with left or right
		if (blocky == blocky2 && !stop)
		{
			if (blockx > blockx2) //this means swapping with the left block
			{
				if (s.at(0).getPosition().x > blockx2)
				{
					//25 is how far the blocks are from each other
					s.at(0).setPosition(s.at(0).getPosition().x - time.asSeconds() * 25, blocky);
					if (s.at(0).getPosition().x < blockx2)
						s.at(0).setPosition(blockx2, blocky);
				}
				else if (s.at(0).getPosition().x == blockx2)
				{
					s.at(1).setPosition(s.at(1).getPosition().x + time.asSeconds() * 25, blocky);
					if (s.at(1).getPosition().x > blockx)
					{
						s.at(1).setPosition(blockx, blocky2);
						stop = true;
					}
				}
			}
			else if (blockx < blockx2 && !stop) //this means swapping with the right block
			{
				if (s.at(0).getPosition().x < blockx2)
				{
					//25 is how far the blocks are from each other
					s.at(0).setPosition(s.at(0).getPosition().x + time.asSeconds() * 25, blocky);
					if (s.at(0).getPosition().x > blockx2)
						s.at(0).setPosition(blockx2, blocky);
				}
				else if (s.at(0).getPosition().x == blockx2)
				{
					s.at(1).setPosition(s.at(1).getPosition().x - time.asSeconds() * 25, blocky);
					if (s.at(1).getPosition().x < blockx)
					{
						s.at(1).setPosition(blockx, blocky2);
						stop = true;
					}
				}
			}//end else if
		}//end if

	}
	else
	{
		clock.restart();
		s.clear();
		stop = false;
	}
}

void AnimationManager::add(sf::RectangleShape r, sf::RectangleShape r2)
{
	s.push_back(r);
	s.push_back(r2);
	blockx = r.getPosition().x;
	blocky = r.getPosition().y;
	blockx2 = r2.getPosition().x;
	blocky2 = r2.getPosition().y;
}