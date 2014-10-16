#ifndef SCREEN_HPP
#define SCREEN_HPP

class Screen
{
public:
	Screen();
	~Screen();
	virtual void draw() = 0;
};

#endif SCREEN_HPP