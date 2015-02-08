#include "NetworkedSinglePlayer.h"
#include "InputManager.hpp"
#include "SoundManager.h"
#include "AnimationManager.hpp"
#include <sstream>
#include <vector>
#include "BlockShowerManager.hpp"

NetworkedSinglePlayer::NetworkedSinglePlayer()
	: pressed(false), pressed2(false), reset(false),
	highScore(new TextBox("Player Score: ",
	410.0f,
	-380.0f,
	600.0f)),
	score(new TextBox("Score goes here",
	480.0f,
	-380.0f,
	600.0f)),
	username(new TextBox("Username: ",
	-665.0f,
	-380.0f,
	600.0f)),
	name(new TextBox("Player name goes here",
	-590.0f,
	-380.0f,
	600.0f))
{
	initGame();
	UIElements.push_back(highScore);
	UIElements.push_back(score);
	UIElements.push_back(username);
	UIElements.push_back(name);
	swapSound.setBuffer(*SoundManager::getInstance().getSound("heya"));
	
}


NetworkedSinglePlayer::~NetworkedSinglePlayer()
{
}

void NetworkedSinglePlayer::initGame()
{
	name->message.setString(ClientManager::getInstance().player.username);
	winX = GraphicsManager::getInstance()->window.getSize().x;
	winY = GraphicsManager::getInstance()->window.getSize().y;
	//fill in initial board
	int gridPosy = 0;
	int gridPosx = 0;
	blockSizeX = (int)(winY / 20);
	blockSizeY = (int)(winY / 20);

	//draws a large rectangle around the game screen
	gameScreenHeight = blockSizeX * 20;
	int offset = winY - gameScreenHeight;
	gameScreenWidth = blockSizeX * 16;

	ch = new CursorHandler(gameScreenWidth, gameScreenHeight, winX, winY, blockSizeX, -offset); //5 is the offset, dunno why yet
	rec.setSize(sf::Vector2f(gameScreenWidth, gameScreenHeight - offset));
	rec.setFillColor(sf::Color::Transparent);
	rec.setPosition((winX / 2) - gameScreenWidth / 2, (winY / 2 - gameScreenHeight / 2));
	rec.setOutlineThickness(blockSizeX);
	rec.setOutlineColor(sf::Color::Black);
	

	//creates blocks and puts them in 2D array
	for (int i = gameScreenHeight; i > 0; i -= blockSizeY)
	{
		for (int j = 0; j < gameScreenWidth; j += blockSizeX)
		{
			
			sf::RectangleShape shape(sf::Vector2f(blockSizeX, blockSizeY));
			shape.setPosition(j + (winX / 2 - gameScreenWidth / 2), i - (winY / 2 - gameScreenHeight / 2) - blockSizeX); //puts it in the middle of the screen
			shape.setFillColor(sf::Color::Transparent); //transparent blocks to appear as empty space
			blocks[gridPosx][gridPosy] = shape;
			gridPosy++;
		}
		gridPosy = 0;
		gridPosx++;
	}
}
void NetworkedSinglePlayer::update()
{
	//takes care of displaying the score. 
	std::string scoreString;
	int Number = (int)gso.score;
	scoreString = static_cast<std::ostringstream*>(&(std::ostringstream() << Number))->str();
	score->message.setString(scoreString);
	Screen::update();
	if (reset)
	{
		initGame();
		reset = false;
	}
	if (!ClientManager::getInstance().gameOver)
	{
		//update the game if there is an update available
		if (ClientManager::getInstance().isUpdated)
		{
			gso = ClientManager::getInstance().currentGSO;
			ClientManager::getInstance().isUpdated = false;

			if (gso.newRowActive){
				ch->Up(sf::Keyboard::Key::Up);

			}

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
					sf::Color c(0, 0, 0, 200);
					switch (color)
					{
						//if its a 0 its empty?
					case 0:
					{
						blocks[i][j].setFillColor(sf::Color::Transparent);
						blocks[i][j].setOutlineThickness(-2);
						blocks[i][j].setOutlineColor(sf::Color::Transparent);
						break;
					}
					case 1:
					{
						c.b = 128;
						blocks[i][j].setFillColor(c);
						c.a = 255;
						blocks[i][j].setOutlineThickness(-2);
						blocks[i][j].setOutlineColor(c);
						break;
					}
					case 2:
					{
						c.r = 255;
						blocks[i][j].setFillColor(c);
						c.a = 255;
						blocks[i][j].setOutlineThickness(-2);
						blocks[i][j].setOutlineColor(c);
						break;
					}
					case 3:
					{
						c.r = 255;
						c.g = 140;
						blocks[i][j].setFillColor(c);
						c.a = 255;
						blocks[i][j].setOutlineThickness(-2);
						blocks[i][j].setOutlineColor(c);
						break;
					}
					case 4:
					{
						c.r = 148;
						c.b = 211;
						blocks[i][j].setFillColor(c);
						c.a = 255;
						blocks[i][j].setOutlineThickness(-2);
						blocks[i][j].setOutlineColor(c);
						break;
					}
					case 5:
					{
						c.r = 50;
						c.g = 205;
						c.b = 50;
						blocks[i][j].setFillColor(c);
						c.a = 255;
						blocks[i][j].setOutlineThickness(-2);
						blocks[i][j].setOutlineColor(c);
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
			ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY(), ch->getCursorX() + 1);
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

		//keypress for block switching
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //swaps the main block with the left block
		{
			if (pressed2 == false && ch->getCursorX() > 0)//cant switch if left side off screen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY(), ch->getCursorX() - 1);
				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();
				ScreenManager::getInstance()->shake(.5);

				int y = ch->getCursorY();
				int x = ch->getCursorX();
				
				AnimationManager::getInstance()->add(blocks[y][x], blocks[y][x - 1]);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //swaps the main block with the right block
		{
			if (pressed2 == false && ch->getCursorX() < 15)//cant switch if right block is off screen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY(), ch->getCursorX() + 1);
				pressed2 = true;
				ScreenManager::getInstance()->shake(.5);
				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();

				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->add(blocks[y][x], blocks[y][x + 1]);

			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //swaps the main block with the top block
		{
			if (pressed2 == false && ch->getCursorY() < 19) // cant switch if top block is offscreen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY() + 1, ch->getCursorX());
				pressed2 = true;
				ScreenManager::getInstance()->shake(.5);
				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();
				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->add(blocks[y][x], blocks[y+1][x]);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //swaps the main block with the bottom block
		{
			if (pressed2 == false && ch->getCursorY() > 0)//cant switch if bottom block is off screen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY() - 1, ch->getCursorX());
				pressed2 = true;
				ScreenManager::getInstance()->shake(.5);
				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();
				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->add(blocks[y][x], blocks[y-1][x]);
			}
		}	
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			ClientManager::getInstance().requestNewRow();
			pressed2 = true;
		}
		else
			pressed2 = false; //cannot hold swap button to keep swapping


	}
	else
	{
		SoundManager::getInstance().playMusic("Sounds/Slamstorm.ogg");
		reset = true;
		if (ClientManager::getInstance().isConnected)
			ScreenManager::getInstance()->switchScreen(RESULT);
		else
			ScreenManager::getInstance()->switchScreen(OFFLINERESULT);

		
	}

    Screen::update();
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

	AnimationManager::getInstance()->update();

	GraphicsManager::getInstance()->window.draw(ch->getMainCursor()); //draws main cursor
	GraphicsManager::getInstance()->window.draw(ch->getLeftCursor()); //draws left cursor
	GraphicsManager::getInstance()->window.draw(ch->getRightCursor()); //draws right cursor
	GraphicsManager::getInstance()->window.draw(ch->getTopCursor()); //draws top cursor
	GraphicsManager::getInstance()->window.draw(ch->getBottomCursor()); //draws bottom cursor
	highScore->message.setColor(sf::Color::Black);
	score->message.setColor(sf::Color::Black);
	username->message.setColor(sf::Color::Black);
	name->message.setColor(sf::Color::Black);

}


void NetworkedSinglePlayer::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_OUT;
}