#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP

#include "SFML/Graphics.hpp"

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	static sf::RenderWindow window;
};

#endif//GRAPHICSMANAGER_HPP