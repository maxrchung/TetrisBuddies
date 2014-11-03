#include <SFML/Graphics.hpp>
#include "BlockHandler.h"
#include <iostream>


int main()
{
	BlockHandler *in = new BlockHandler();
	sf::RenderWindow window(sf::VideoMode(in->SCREENWIDTH, in->SCREENHEIGHT), "Block Buddies");

	//cursor variables
	bool pressed = false;
	bool pressed2 = false;
	sf::RectangleShape cursors(sf::Vector2f(50, 50));
	cursors.setFillColor(sf::Color::Transparent);
	cursors.setPosition(0, 0);
	cursors.setOutlineThickness(5);
	cursors.setOutlineColor(sf::Color::Black);
	cursors.getPosition();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//background is white
		window.clear(sf::Color::White);

		//Cursor keyboard movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (cursors.getPosition().x == 0) // edge of screen, do nothing
			{
			}
			else
			{
				if (pressed == false)
				{
					cursors.setPosition(cursors.getPosition().x - 25, cursors.getPosition().y); //left cursor movement
					pressed = true; // Cannot hold left to move
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (cursors.getPosition().x == in->SCREENWIDTH-50) //edge of screen, do nothing
			{
			}
			else
			{
				if (pressed == false)
				{
					cursors.setPosition(cursors.getPosition().x + 25, cursors.getPosition().y); // right cursor movement
					pressed = true; // Cannot hold right to move
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (cursors.getPosition().y == in->SCREENHEIGHT - 50) // bottom of screen, do nothing
			{
			}
			else
			{
				if (pressed == false)
				{
					cursors.setPosition(cursors.getPosition().x, cursors.getPosition().y + 25); // down cursor movement 
					pressed = true; //Cannot hold down to move
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (cursors.getPosition().y == 0) //top of screen, do nothing
			{
			}
			else
			{
				if (pressed == false)
				{
					cursors.setPosition(cursors.getPosition().x, cursors.getPosition().y - 25); // up cursor movement
					pressed = true; //Cannot hold up to move
				}
			}
		}
		else
			pressed = false; //prevent holding a button to move


		//keypress for block switching
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //swaps top horizontal blocks
		{
			if (pressed2 == false)
			{
				in->swapBlocksHorizT(cursors.getPosition().x, cursors.getPosition().y);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) //swaps bottom horizontal blocks
		{
			if (pressed2 == false)
			{
				in->swapBlocksHorizB(cursors.getPosition().x, cursors.getPosition().y);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //swaps left vertical blocks
		{
			if(pressed2 == false)
			{
				in->swapBlocksVertL(cursors.getPosition().x, cursors.getPosition().y);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) //swaps right vertical blocks
		{
			if (pressed2 == false)
			{
				in->swapBlocksVertR(cursors.getPosition().x, cursors.getPosition().y);
				pressed2 = true;
			}
		}
		else
			pressed2 = false; //cannot hold swap button to keep swapping

		//draws blocks on screen
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j ++)
			{
				window.draw(in->getBlocks(j,i));
			}
		}

		window.draw(cursors); //draws cursor
		window.display(); //displays window
	}

	delete in;

	return 0;
}