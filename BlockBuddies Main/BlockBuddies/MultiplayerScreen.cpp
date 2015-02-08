#include "MultiplayerScreen.hpp"
#include "BlockShowerManager.hpp"

MultiplayerScreen::MultiplayerScreen()
	:blockSwitch(false)
{
	ch = new CursorHandler(SCREENWIDTH, SCREENHEIGHT, GraphicsManager::getInstance()->window.getSize().x, GraphicsManager::getInstance()->window.getSize().y,
		 GraphicsManager::getInstance()->window.getSize().x / 2 - SCREENWIDTH * 3 / 2, GraphicsManager::getInstance()->window.getSize().y / 2 - SCREENHEIGHT / 2);
	//draws a large rectangle around the game screen for p1
	p1Outline.setSize(sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	p1Outline.setFillColor(sf::Color::Transparent);
	p1Outline.setPosition(GraphicsManager::getInstance()->window.getSize().x / 2 - SCREENWIDTH*3/2, GraphicsManager::getInstance()->window.getSize().y / 2 - SCREENHEIGHT / 2);
	p1Outline.setOutlineThickness(25);
	p1Outline.setOutlineColor(sf::Color::Black);
	//draws a large rectangle around the game screen for p2
	p2Outline.setSize(sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	p2Outline.setFillColor(sf::Color::Transparent);
	p2Outline.setPosition(GraphicsManager::getInstance()->window.getSize().x / 2 + SCREENWIDTH / 2, GraphicsManager::getInstance()->window.getSize().y / 2 - SCREENHEIGHT / 2);
	p2Outline.setOutlineThickness(25);
	p2Outline.setOutlineColor(sf::Color::Black);

}

void MultiplayerScreen::update()
{
	//keypress for cursor movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		ch->Left(sf::Keyboard::Key::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		ch->Right(sf::Keyboard::Key::Right);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		ch->Up(sf::Keyboard::Key::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		ch->Down(sf::Keyboard::Key::Down);
	}

	//keypress for block switching
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //swaps the main block with the left block
	{
		if (blockSwitch == false)
		{

			blockSwitch = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //swaps the main block with the right block
	{
		if (blockSwitch == false)
		{
			blockSwitch = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //swaps the main block with the top block
	{
		if (blockSwitch == false)
		{
			blockSwitch = true;

		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //swaps the main block with the bottom block
	{
		if (blockSwitch == false)
		{
			blockSwitch = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) //creates a new line of blocks at the bottom
	{
		if (blockSwitch == false)
		{
			blockSwitch = true;
		}
	}
	else
		blockSwitch = false; //cannot hold swap button to keep swapping

    Screen::update();
}

void MultiplayerScreen::draw()
{
	GraphicsManager::getInstance()->window.draw(p1Outline);
	GraphicsManager::getInstance()->window.draw(p2Outline);

	//draws blocks on screen
	for (int i = 0; i < SCREENHEIGHT / 25; i++)
	{
		for (int j = 0; j < SCREENWIDTH / 25; j++)
		{
			GraphicsManager::getInstance()->window.draw(p1Blocks[i][j]);
		}
	}

	for (int i = 0; i < SCREENHEIGHT / 25; i++)
	{
		for (int j = 0; j < SCREENWIDTH / 25; j++)
		{
			GraphicsManager::getInstance()->window.draw(p2Blocks[i][j]);
		}
	}
	GraphicsManager::getInstance()->window.draw(ch->getMainCursor()); //draws main cursor
	GraphicsManager::getInstance()->window.draw(ch->getLeftCursor()); //draws left cursor
	GraphicsManager::getInstance()->window.draw(ch->getRightCursor()); //draws right cursor
	GraphicsManager::getInstance()->window.draw(ch->getTopCursor()); //draws top cursor
	GraphicsManager::getInstance()->window.draw(ch->getBottomCursor()); //draws bottom cursor

    Screen::draw();
}

void MultiplayerScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_OUT;
}