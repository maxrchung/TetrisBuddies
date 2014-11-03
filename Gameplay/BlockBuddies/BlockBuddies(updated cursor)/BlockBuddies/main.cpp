#include <SFML/Graphics.hpp>
#include "BlockHandler.h"
#include "CursorHandler.h"
#include <iostream>


int main()
{
	BlockHandler *in = new BlockHandler();
	CursorHandler *cursor = new CursorHandler(in->SCREENWIDTH, in->SCREENHEIGHT);

	sf::RenderWindow window(sf::VideoMode(in->SCREENWIDTH, in->SCREENHEIGHT), "Block Buddies");

	//cursor variables
	bool pressed = false;
	bool pressed2 = false;

	// run the program as long as the window is open
	while (window.isOpen())
	{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//keyboard movement for cursor
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (pressed == false)
				{
					cursor->Left(sf::Keyboard::Key::Left);
					pressed = true; // Cannot hold right to move
				}

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (pressed == false)
				{
					cursor->Right(sf::Keyboard::Key::Right);
					pressed = true; // Cannot hold right to move
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (pressed == false)
				{
					cursor->Up(sf::Keyboard::Key::Up);
					pressed = true; // Cannot hold right to move
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (pressed == false)
				{
					cursor->Down(sf::Keyboard::Key::Down);
					pressed = true; // Cannot hold right to move
				}
			}
			else
				pressed = false;

			//keypress for block switching
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //swaps the main block with the left block
			{
				if (pressed2 == false)
				{
					in->swapBlocksHorizL(cursor->getMainCursor().getPosition().x, cursor->getMainCursor().getPosition().y);
					pressed2 = true;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //swaps the main block with the right block
			{
				if (pressed2 == false)
				{
					in->swapBlocksHorizR(cursor->getMainCursor().getPosition().x, cursor->getMainCursor().getPosition().y);
					pressed2 = true;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //swaps the main block with the top block
			{
				if (pressed2 == false)
				{
					in->swapBlocksVertT(cursor->getMainCursor().getPosition().x, cursor->getMainCursor().getPosition().y);
					pressed2 = true;
			
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //swaps the main block with the bottom block
			{
				if (pressed2 == false)
				{
					in->swapBlocksVertB(cursor->getMainCursor().getPosition().x, cursor->getMainCursor().getPosition().y);
					pressed2 = true;
				}
			}
			else
				pressed2 = false; //cannot hold swap button to keep swapping
		

			//background is white
			window.clear(sf::Color::White);

			//draws blocks on screen
			for (int i = 0; i < in->SCREENHEIGHT/25 ; i++)
			{
				for (int j = 0; j < in->SCREENWIDTH/25; j ++)
				{
					window.draw(in->getBlocks(j,i));
				}
			}

			window.draw(cursor->getMainCursor()); //draws main cursor
			window.draw(cursor->getLeftCursor()); //draws left cursor
			window.draw(cursor->getRightCursor()); //draws right cursor
			window.draw(cursor->getTopCursor()); //draws top cursor
			window.draw(cursor->getBottomCursor()); //draws bottom cursor

			window.display(); //displays window
	}

	delete in;
	delete cursor;

	return 0;
}