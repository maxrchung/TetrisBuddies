#ifndef SCREEN_HPP
#define SCREEN_HPP

// Parent Screen that all other Screens inherit off of
class Screen
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
};

#endif SCREEN_HPP