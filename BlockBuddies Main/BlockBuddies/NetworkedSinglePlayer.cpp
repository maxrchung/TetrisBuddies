#include "NetworkedSinglePlayer.h"
#include "InputManager.hpp"
NetworkedSinglePlayer::NetworkedSinglePlayer()
: pressed(false), pressed2(false)
{
	winX = GraphicsManager::getInstance()->window.getSize().x;
	winY = GraphicsManager::getInstance()->window.getSize().y;
	//fill in initial board
	int gridPosy = 0;
	int gridPosx = 0;
	blockSizeX = (int)(winY / 20);
	blockSizeY = (int)(winY / 20);
	
	//draws a large rectangle around the game screen
	int gameScreenHeight = blockSizeX * 20;
	int gameScreenWidth = blockSizeX * 16;

	ch = new CursorHandler(gameScreenWidth, gameScreenHeight, winX, winY, blockSizeX , 5); //5 is the offset, dunno why yet
	rec.setSize(sf::Vector2f(gameScreenWidth, gameScreenHeight));
	rec.setFillColor(sf::Color::Transparent);
	rec.setPosition((winX/2) - gameScreenWidth/2, winY/2 - gameScreenHeight/2);
	rec.setOutlineThickness(blockSizeX);
	rec.setOutlineColor(sf::Color::Black);
	std::cout << ((winY * 4)/5) << "<<<<<<<< \n";
	
	//creates blocks and puts them in 2D array
	for (int i = gameScreenHeight; i > 0; i -= blockSizeY)
	{
		for (int j = 0; j < gameScreenWidth; j += blockSizeX)
		{
			sf::RectangleShape shape(sf::Vector2f(blockSizeX, blockSizeY));
			shape.setPosition(j + (winX/2 - gameScreenWidth/2), i - (winY/2 - gameScreenHeight/2) - 25); //puts it in the middle of the screen
			shape.setFillColor(sf::Color::Transparent); //transparent blocks to appear as empty space
			blocks[gridPosx][gridPosy] = shape;
			gridPosy++;
		}
		gridPosy = 0;
		gridPosx++;
	}
}


NetworkedSinglePlayer::~NetworkedSinglePlayer()
{
}

void NetworkedSinglePlayer::update()
{
	
	Screen::update();
	//update the game if there is an update available
	if (ClientManager::getInstance().isUpdated)
	{
		gso = ClientManager::getInstance().currentGSO;
		ClientManager::getInstance().isUpdated = false;
		int color;
		gso.Print();
		std::cout << "changing it on the screen now";
		gso.Print();
		//take this new gso and apply it to our board
		for (int i = 0; i < gso.boardHeight; i++)
		{
			for (int j = 0; j < gso.boardWidth; j++)
			{
				color = gso.gameBoard[i][j];

				switch (color)
				{
					//if its a 0 its empty?
					case 0:
					{
							  blocks[i][j].setFillColor(sf::Color::Transparent);
							  break;
					}
					case 1:
					{
							  blocks[i][j].setFillColor(sf::Color::Blue);
							  break;
					}
					case 2:
					{
							  blocks[i][j].setFillColor(sf::Color::Red);
							  break;
					}
					case 3:
					{
							  blocks[i][j].setFillColor(sf::Color::Yellow);
							  break;
					}
					case 4:
					{
							  blocks[i][j].setFillColor(sf::Color::Magenta);
							  break;
					}
					case 5:
					{
							  blocks[i][j].setFillColor(sf::Color::Green);
							  break;
					}
					default:
					{
							  blocks[i][j].setFillColor(sf::Color::Black);
							  break;
					}
				}
			}
		}

	}

	if (InputManager::getInstance()->backspace)
	{
		ClientManager::getInstance().requestSwap(15, 3, 14, 4);
	}

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
}

void NetworkedSinglePlayer::draw()
{
	Screen::draw();
	GraphicsManager::getInstance()->window.draw(rec);
	for (int i = 0; i < GameStateObject::boardHeight; i++)
	{
		for (int j = 0; j < GameStateObject::boardWidth; j++)
		{
			GraphicsManager::getInstance()->window.draw(blocks[i][j]);
		}
	}


	GraphicsManager::getInstance()->window.draw(ch->getMainCursor()); //draws main cursor
	GraphicsManager::getInstance()->window.draw(ch->getLeftCursor()); //draws left cursor
	GraphicsManager::getInstance()->window.draw(ch->getRightCursor()); //draws right cursor
	GraphicsManager::getInstance()->window.draw(ch->getTopCursor()); //draws top cursor
	GraphicsManager::getInstance()->window.draw(ch->getBottomCursor()); //draws bottom cursor
}