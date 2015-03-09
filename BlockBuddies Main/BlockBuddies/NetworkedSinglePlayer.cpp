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
	600.0f)),
	oldHighScore(new TextBox("Score to beat: ",
	410.0f,
	-350.0f,
	600.0f)),
	scoreToBeat(new TextBox("Score to beat goes here",
	490.0f,
	-350.0f,
	600.0f))

{
	initGame();
	UIElements.push_back(highScore);
	UIElements.push_back(score);
	UIElements.push_back(username);
	UIElements.push_back(name);
	UIElements.push_back(oldHighScore);
	UIElements.push_back(scoreToBeat);
	swapSound.setBuffer(*SoundManager::getInstance().getSound("heya"));
	
}


NetworkedSinglePlayer::~NetworkedSinglePlayer()
{
}

void NetworkedSinglePlayer::initGame()
{
	
	winX = GraphicsManager::getInstance()->window.getSize().x;
	winY = GraphicsManager::getInstance()->window.getSize().y;
	//fill in initial board
	int gridPosy = 0;
	int gridPosx = 0;
	blockSizeX = (int)(winY / gso.boardHeight);
	blockSizeY = (int)(winY / gso.boardHeight);

	AnimationManager::getInstance()->setBlockSize(blockSizeX);

	//draws a large rectangle around the game screen
	gameScreenHeight = blockSizeX * gso.boardHeight;
	int offset = winY - gameScreenHeight;
	gameScreenWidth = blockSizeX * gso.boardWidth;

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
			updateBlocks();

			if (!gso.clearingBlocks.empty())
			{
				for (int i = 0; i < gso.clearingBlocks.size(); i++)
				{
					AnimationManager::getInstance()->addClear(blocks[gso.clearingBlocks.at(i).first][gso.clearingBlocks.at(i).second]);
				}
				AnimationManager::getInstance()->setClearingAdd();
			}

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
				//ScreenManager::getInstance()->shake(.5);

				int y = ch->getCursorY();
				int x = ch->getCursorX();
				
				AnimationManager::getInstance()->addSwap(blocks[y][x], blocks[y][x - 1]);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //swaps the main block with the right block
		{
			if (pressed2 == false && ch->getCursorX() < 15)//cant switch if right block is off screen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY(), ch->getCursorX() + 1);
				pressed2 = true;
				//ScreenManager::getInstance()->shake(.5);
				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();

				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->addSwap(blocks[y][x], blocks[y][x + 1]);

			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //swaps the main block with the top block
		{
			if (pressed2 == false && ch->getCursorY() < 19) // cant switch if top block is offscreen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY() + 1, ch->getCursorX());
				pressed2 = true;
				//ScreenManager::getInstance()->shake(.5);
				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();
				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->addSwap(blocks[y][x], blocks[y + 1][x]);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //swaps the main block with the bottom block
		{
			if (pressed2 == false && ch->getCursorY() > 0)//cant switch if bottom block is off screen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY() - 1, ch->getCursorX());
				pressed2 = true;
				//ScreenManager::getInstance()->shake(.5);
				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();
				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->addSwap(blocks[y][x], blocks[y - 1][x]);
			}
		}	
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			if (pressed2 == false){
			ClientManager::getInstance().requestNewRow();
			pressed2 = true;
			}
		}
		else
			pressed2 = false; //cannot hold swap button to keep swapping


	}
	else
	{
		SoundManager::getInstance().playMusic("Sounds/Slamstorm.ogg", false);
		reset = true;
		if (ClientManager::getInstance().isConnected)
		{
			gso = GameStateObject();
			updateBlocks();
			ScreenManager::getInstance()->switchScreen(RESULT);
		}
		else
			ScreenManager::getInstance()->switchScreen(OFFLINERESULT);

		
	}

    if(InputManager::getInstance()->escape)
    {
        ScreenManager::getInstance()->addScreen(close->toScreen);
    }

    Screen::update();
}
void NetworkedSinglePlayer::updateBlocks()
{
	int color;
	//gso.Print();
	//std::cout << "changing it on the screen now";
	//gso.Print();
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
			case 1: //blue case
			{
				c.b = 128;
				blocks[i][j].setFillColor(c);
				c.a = 255;
				blocks[i][j].setOutlineThickness(-2);
				blocks[i][j].setOutlineColor(c);
				
				break;
			}
			case 2: //red case
			{
				c.r = 255;
				blocks[i][j].setFillColor(c);
				c.a = 255;
				blocks[i][j].setOutlineThickness(-2);
				blocks[i][j].setOutlineColor(c);
				
				break;
			}
			case 3://yellow case
			{
				c.r = 255;
				c.g = 140;
				blocks[i][j].setFillColor(c);
				c.a = 255;
				blocks[i][j].setOutlineThickness(-2);
				blocks[i][j].setOutlineColor(c);
				
				break;
			}
			case 4:// purple case
			{
				c.r = 148;
				c.b = 211;
				blocks[i][j].setFillColor(c);
				c.a = 255;
				blocks[i][j].setOutlineThickness(-2);
				blocks[i][j].setOutlineColor(c);
				
				break;
			}
			case 5://green case
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
			default: //error case
			{
				blocks[i][j].setFillColor(sf::Color::Black);
				break;
			}
			}
		}
	}
}
void NetworkedSinglePlayer::draw()
{
	name->message.setString(ClientManager::getInstance().player.username);
	scoreToBeat->message.setString(std::to_string(ClientManager::getInstance().player.highScore));
	Screen::draw();

	GraphicsManager::getInstance()->window.draw(rec);
	
	for (int i = 0; i < GameStateObject::boardHeight; i++)
	{
		for (int j = 0; j < GameStateObject::boardWidth; j++)
		{
			GraphicsManager::getInstance()->window.draw(blocks[i][j]);
			//set the shape on the block
			blockShape.setPosition(blocks[i][j].getPosition());
		
			switch (gso.gameBoard[i][j])
			{
			//
			case 1: //blue case
				blockShape.setTexture(*_getTexture("Textures/bluestar.png"));
				//defualt textures are 24 by 24 so scale them to match block size
				blockShape.setScale(sf::Vector2f((float)blockSizeX / 24, (float)blockSizeY / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			case 2: //red case
				blockShape.setTexture(*_getTexture("Textures/redgear.png"));
				blockShape.setScale(sf::Vector2f((float)blockSizeX / 24, (float)blockSizeY / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			case 3:// yellow case
				blockShape.setTexture(*_getTexture("Textures/yellowsquare.png"));
				blockShape.setScale(sf::Vector2f((float)blockSizeX / 24, (float)blockSizeY / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			case 4://purple
				blockShape.setTexture(*_getTexture("Textures/purplespade.png"));
				blockShape.setScale(sf::Vector2f((float)blockSizeX / 24, (float)blockSizeY / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			case 5://green
				blockShape.setTexture(*_getTexture("Textures/greentriangle.png"));
				blockShape.setScale(sf::Vector2f((float)blockSizeX / 24, (float)blockSizeY / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			default:
				break;
			}
			
			
		}
	}
	

	GraphicsManager::getInstance()->window.draw(ch->getMainCursor()); //draws main cursor
	GraphicsManager::getInstance()->window.draw(ch->getLeftCursor()); //draws left cursor
	GraphicsManager::getInstance()->window.draw(ch->getRightCursor()); //draws right cursor
	GraphicsManager::getInstance()->window.draw(ch->getTopCursor()); //draws top cursor
	GraphicsManager::getInstance()->window.draw(ch->getBottomCursor()); //draws bottom cursor
	highScore->message.setColor(sf::Color::Black);
	oldHighScore->message.setColor(sf::Color::Black);
	scoreToBeat->message.setColor(sf::Color::Black);
	score->message.setColor(sf::Color::Black);
	username->message.setColor(sf::Color::Black);
	name->message.setColor(sf::Color::Black);

}


void NetworkedSinglePlayer::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_OUT;
}