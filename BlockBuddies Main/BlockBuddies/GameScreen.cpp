#include "GameScreen.hpp"

// To be filled in at the gameplay people's discretion
GameScreen::GameScreen()
	: pressed(false), pressed2(false)
{
	bh = new BlockHandler(GraphicsManager::getInstance()->window.getSize().x, GraphicsManager::getInstance()->window.getSize().y);
	ch = new CursorHandler(bh->SCREENWIDTH, bh->SCREENHEIGHT, GraphicsManager::getInstance()->window.getSize().x, GraphicsManager::getInstance()->window.getSize().y);	
	//draws a large rectangle around the game screen
	rec.setSize(sf::Vector2f(bh->SCREENWIDTH, bh->SCREENHEIGHT));
	rec.setFillColor(sf::Color::Transparent);
	rec.setPosition(GraphicsManager::getInstance()->window.getSize().x/2 - bh->SCREENWIDTH/2, GraphicsManager::getInstance()->window.getSize().y/2 - bh->SCREENHEIGHT/2	);
	rec.setOutlineThickness(25);
	rec.setOutlineColor(sf::Color::Black);
}

void GameScreen::update()
{
	if (!bh->GameOver())
	{
		//keyboard movement for cursor
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (pressed == false)
			{
				ch->Left(sf::Keyboard::Key::Left);
				pressed = true; // Cannot hold right to move
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (pressed == false)
			{
				ch->Right(sf::Keyboard::Key::Right);
				pressed = true; // Cannot hold right to move
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (pressed == false)
			{
				ch->Up(sf::Keyboard::Key::Up);
				pressed = true; // Cannot hold right to move
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (pressed == false)
			{
				ch->Down(sf::Keyboard::Key::Down);
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
				bh->swapBlocksHorizL(ch->getMainCursor().getPosition().x, ch->getMainCursor().getPosition().y);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //swaps the main block with the right block
		{
			if (pressed2 == false)
			{
				bh->swapBlocksHorizR(ch->getMainCursor().getPosition().x, ch->getMainCursor().getPosition().y);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //swaps the main block with the top block
		{
			if (pressed2 == false)
			{
				bh->swapBlocksVertT(ch->getMainCursor().getPosition().x, ch->getMainCursor().getPosition().y);
				pressed2 = true;

			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //swaps the main block with the bottom block
		{
			if (pressed2 == false)
			{
				bh->swapBlocksVertB(ch->getMainCursor().getPosition().x, ch->getMainCursor().getPosition().y);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) //swaps the main block with the bottom block
		{
			if (pressed2 == false)
			{
				bh->raiseBlocks();
				pressed2 = true;
			}
		}
		else
			pressed2 = false; //cannot hold swap button to keep swapping
	}
	else
	{
		delete bh;
		delete ch;
		ScreenManager::getInstance()->switchScreen(RESULT);
	}
}

void GameScreen::draw()
{
	//draws a border around the game
	GraphicsManager::getInstance()->window.draw(rec);

	//draws blocks on screen
	for (int i = 0; i < bh->SCREENHEIGHT / 25; i++)
	{
		for (int j = 0; j < bh->SCREENWIDTH / 25; j++)
		{
			GraphicsManager::getInstance()->window.draw(bh->getBlocks(j, i));
		}
	}
	
	GraphicsManager::getInstance()->window.draw(ch->getMainCursor()); //draws main cursor
	GraphicsManager::getInstance()->window.draw(ch->getLeftCursor()); //draws left cursor
	GraphicsManager::getInstance()->window.draw(ch->getRightCursor()); //draws right cursor
	GraphicsManager::getInstance()->window.draw(ch->getTopCursor()); //draws top cursor
	GraphicsManager::getInstance()->window.draw(ch->getBottomCursor()); //draws bottom cursor

}