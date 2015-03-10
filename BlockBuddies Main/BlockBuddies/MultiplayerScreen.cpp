#include "MultiplayerScreen.hpp"
#include "BlockShowerManager.hpp"
#include "AnimationManager.hpp"
#include <cmath>

//Bigger the Y value, the lower it'll be
//The smaller the x value, the more left.
MultiplayerScreen::MultiplayerScreen()
:blockSwitch(false), pressed(false), pressed2(false), reset(false),
 playerOneName(new TextBox("Replace me!",
 -590.0f,
 -350.0f,
 600.0f)),
 playerTwoName(new TextBox("And me!",
 450.0f,
 -350.0f,
 600.0f)),
 timer(new TextBox("01:27",
 -10.0f,
 -380.0f,
 600.0f)),
 nextRowLeft(new TextBox("Next",
 -680.0f,
 330.0f,
 600.0f)),
 nextRowL2(new TextBox("Row",
 -680.0f,
 345.0f,
 600.0f)),
 nextRowRight(new TextBox("Next",
 360.0f,
 330.0f,
 600.0f)),
 nextRowR2(new TextBox("Row",
 360.0f,
 345.0f,
 600.0f)),
 comboCounter(new TextBox("3x!",
 -365.0f,
 -325.0f,
 600.0f))

{
	initGame();
	swapSound.setBuffer(*SoundManager::getInstance().getSound("heya"));
	UIElements.push_back(playerOneName);
	UIElements.push_back(playerTwoName);
	UIElements.push_back(timer);
	UIElements.push_back(nextRowLeft);
	UIElements.push_back(nextRowL2);
	UIElements.push_back(nextRowRight);
	UIElements.push_back(nextRowR2);
	UIElements.push_back(comboCounter);
}

void MultiplayerScreen::initGame()
{
	winX = GraphicsManager::getInstance()->window.getSize().x;
	winY = GraphicsManager::getInstance()->window.getSize().y;
	//fill in initial board
	int gridPosy = 0;
	int gridPosx = 0;
	gameScreenHeight = (int)(winY * 0.8);
	blockSize = std::floor((float)gameScreenHeight / GameStateObject::boardHeight);

	AnimationManager::getInstance()->setBlockSize(blockSize);
	dangerColumnCounter = 0;

	int offset = gameScreenHeight - (blockSize * GameStateObject::boardHeight);
	gameScreenWidth = blockSize * GameStateObject::boardWidth;

	/*
	int p1OutlineX = blockSize;
	int p1OutlineY = (winY / 2 - gbHeight / 2) - ((winY / 2 - gbHeight / 2) % blockSize);
	int p2OutlineX = winX - (gbWidth + blockSize);
	int p2OutlineY = (winY / 2 - gbHeight / 2) - ((winY / 2 - gbHeight / 2) % blockSize);
	*/

	//draws a large rectangle around the game screen for p1
	p1Outline.setSize(sf::Vector2f(gameScreenWidth, -blockSize * GameStateObject::boardHeight));
	p1Outline.setFillColor(sf::Color::Transparent);
	p1Outline.setPosition(2 * blockSize, (winY - (3 * blockSize)));
	p1Outline.setOutlineThickness(blockSize/3);
	p1Outline.setOutlineColor(sf::Color::Black);


	//draws a large rectangle around the game screen for p2
	p2Outline.setSize(sf::Vector2f(gameScreenWidth, -blockSize * GameStateObject::boardHeight));
	p2Outline.setFillColor(sf::Color::Transparent);
	p2Outline.setPosition(winX - (2 * blockSize) - gameScreenWidth, (winY - (3 * blockSize)));
	p2Outline.setOutlineThickness(blockSize/3);
	p2Outline.setOutlineColor(sf::Color::Black);

	//draws temp row for player 1
	tempRowRec1.setSize(sf::Vector2f(gameScreenWidth, blockSize));
	tempRowRec1.setFillColor(sf::Color::Transparent);
	tempRowRec1.setPosition(2 * blockSize, (winY - (2.5 * blockSize)));
	tempRowRec1.setOutlineThickness(blockSize / 3);
	tempRowRec1.setOutlineColor(sf::Color::Black);

	//draws temp row for player 2
	tempRowRec2.setSize(sf::Vector2f(gameScreenWidth, blockSize));
	tempRowRec2.setFillColor(sf::Color::Transparent);
	tempRowRec2.setPosition(winX - (2 * blockSize) - gameScreenWidth, (winY - (2.5 * blockSize)));
	tempRowRec2.setOutlineThickness(blockSize / 3);
	tempRowRec2.setOutlineColor(sf::Color::Black);

	//creates blocks and puts them in 2D array for p1
	for (int i = 0; i < GameStateObject::boardHeight; i++)
	{
		for (int j = 0; j < GameStateObject::boardWidth; j++)
		{
			sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
			shape.setPosition(p1Outline.getPosition().x + (j * blockSize), p1Outline.getPosition().y - (i * blockSize) - blockSize);
			//shape.setPosition(j + (winX / 2 - gameScreenWidth / 2), i - (winY / 2 - gameScreenHeight / 2) - blockSizeX); //puts it in the middle of the screen
			shape.setFillColor(sf::Color::Transparent); //transparent blocks to appear as empty space
			p1Blocks[gridPosx][gridPosy] = shape;
			gridPosy++;

		}
		gridPosy = 0;
		gridPosx++;
	}

	//creates the temp row below this
	for (int i = 0; i < GameStateObject::boardWidth; i++)
	{
		sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
		shape.setPosition(tempRowRec1.getPosition().x + (i * blockSize), tempRowRec1.getPosition().y);
		shape.setFillColor(sf::Color::Transparent);
		p1NextBlocks[i] = shape;
	}
	gridPosx = 0;
	gridPosy = 0;

	//creates blocks and puts them in 2D array for p2
	for (int i = 0; i < GameStateObject::boardHeight; i++)
	{
		for (int j = 0; j < GameStateObject::boardWidth; j++)
		{
			sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
			shape.setPosition(p2Outline.getPosition().x + (j * blockSize), p2Outline.getPosition().y - (i * blockSize) - blockSize);
			//shape.setPosition(j + (winX / 2 - gameScreenWidth / 2), i - (winY / 2 - gameScreenHeight / 2) - blockSizeX); //puts it in the middle of the screen
			shape.setFillColor(sf::Color::Transparent); //transparent blocks to appear as empty space
			p2Blocks[gridPosx][gridPosy] = shape;
			gridPosy++;

		}
		gridPosy = 0;
		gridPosx++;
	}

	ClientManager::getInstance().multiplayer = true;

	//creates the temp row below this
	for (int i = 0; i < GameStateObject::boardWidth; i++)
	{
		sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
		shape.setPosition(tempRowRec2.getPosition().x + (i * blockSize), tempRowRec2.getPosition().y);
		shape.setFillColor(sf::Color::Transparent);
		p2NextBlocks[i] = shape;
	}

	ch = new CursorHandler(p1Blocks[(GameStateObject::boardHeight / 2) - 1][(GameStateObject::boardWidth / 2) - 1].getPosition(),
		p1Outline.getPosition(), gameScreenHeight, gameScreenWidth, blockSize);
	ch2 = new CursorHandler(p2Blocks[(GameStateObject::boardHeight / 2) - 1][(GameStateObject::boardWidth / 2) - 1].getPosition(),
		p2Outline.getPosition(), gameScreenHeight, gameScreenWidth, blockSize);
	
}
void MultiplayerScreen::update()
{
	if (reset)
	{
		initGame();
		reset = false;
	}

	//if song runs out play rando song
	if (SoundManager::getInstance().music.getStatus() != SoundManager::getInstance().music.Playing)
	{
		SoundManager::getInstance().playMusicRandom();
	}

	if (!ClientManager::getInstance().gameOver)
	{
		//update the game if there is an update available
		if (ClientManager::getInstance().isUpdated)
		{

			p1GSO = ClientManager::getInstance().currentGSO;
			p2GSO = ClientManager::getInstance().secondGSO;
			ClientManager::getInstance().isUpdated = false;

			if (p1GSO.newRowActive)
				ch->Up(sf::Keyboard::Key::Up);
			if (p2GSO.newRowActive)
				ch2->Up(sf::Keyboard::Key::Up);
			ch2->setCursorAt(p2GSO.cursorPos.first, p2GSO.cursorPos.second);

			//This can be further optimized to only update a particular player if both states aren't  updated.
			updateBlocks();
			
			if (!p1GSO.clearingBlocks.empty())
			{
				for (int i = 0; i < p1GSO.clearingBlocks.size(); i++)
				{
					AnimationManager::getInstance()->addClear(p1Blocks[p1GSO.clearingBlocks.at(i).first][p1GSO.clearingBlocks.at(i).second]);
				}
				AnimationManager::getInstance()->setClearingAdd();
			}

			AnimationManager::getInstance()->clearDangerBlocks();

			dangerColumns.clear();
			dangerColumnCounter = 0;
			for (int row = 0; row < GameStateObject::boardWidth; row++)
			{
				if (p1Blocks[GameStateObject::boardHeight - 4][row].getFillColor() != sf::Color::Transparent)
					dangerMark.push_back(row);
				else
					dangerMark.push_back(-1);
			}

			for (int col = 0; col < GameStateObject::boardHeight; col++)
			{
				for (int row = 0; row < GameStateObject::boardWidth; row++)
				{
					if (dangerMark.at(row) != -1 && p1Blocks[col][row].getFillColor() != sf::Color::Transparent)
					{
						AnimationManager::getInstance()->addDanger(p1Blocks[col][row]);
						dangerColumns.push_back(std::make_pair(col, row));
					}
				}
			}
			dangerMark.clear();

			AnimationManager::getInstance()->setTextureDanger();

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (pressed == false)
			{
				ch->Left(sf::Keyboard::Key::Left);
				ClientManager::getInstance().sendCursorUpdate(ch->getCursorX(), ch->getCursorY());
				pressed = true; // Cannot hold right to move
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (pressed == false)
			{
				ch->Right(sf::Keyboard::Key::Right);
				ClientManager::getInstance().sendCursorUpdate(ch->getCursorX(), ch->getCursorY());
				pressed = true; // Cannot hold right to move
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (pressed == false)
			{
				ch->Up(sf::Keyboard::Key::Up);
				ClientManager::getInstance().sendCursorUpdate(ch->getCursorX(), ch->getCursorY());
				pressed = true; // Cannot hold right to move
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (pressed == false)
			{
				ch->Down(sf::Keyboard::Key::Down);
				ClientManager::getInstance().sendCursorUpdate(ch->getCursorX(), ch->getCursorY());
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

				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->addSwap(p1Blocks[y][x], p1Blocks[y][x - 1]);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //swaps the main block with the right block
		{
			if (pressed2 == false && ch->getCursorX() < ch->getCursorX() < GameStateObject::boardWidth - 1)//cant switch if right block is off screen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY(), ch->getCursorX() + 1);
				pressed2 = true;

				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();

				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->addSwap(p1Blocks[y][x], p1Blocks[y][x + 1]);

			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //swaps the main block with the top block
		{
			if (pressed2 == false && ch->getCursorY() < GameStateObject::boardHeight - 1) // cant switch if top block is offscreen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY() + 1, ch->getCursorX());
				pressed2 = true;

				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();
				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->addSwap(p1Blocks[y][x], p1Blocks[y + 1][x]);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //swaps the main block with the bottom block
		{
			if (pressed2 == false && ch->getCursorY() > 0)//cant switch if bottom block is off screen
			{
				ClientManager::getInstance().requestSwap(ch->getCursorY(), ch->getCursorX(), ch->getCursorY() - 1, ch->getCursorX());
				pressed2 = true;

				if (swapSound.getStatus() != swapSound.Playing)
					swapSound.play();
				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->addSwap(p1Blocks[y][x], p1Blocks[y - 1][x]);
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
		AnimationManager::getInstance()->clearDangerBlocks();
		dangerColumns.clear();
		dangerMark.clear();
		SoundManager::getInstance().playMusic("Sounds/Slamstorm.ogg", false);
		reset = true;
		if (ClientManager::getInstance().isConnected)
		{
			p1GSO = GameStateObject();
			p2GSO = GameStateObject();
			updateBlocks();
			ScreenManager::getInstance()->switchScreen(MULTIPLAYERRESULT);
		}
		else
			ScreenManager::getInstance()->switchScreen(OFFLINERESULT);
	}

	AnimationManager::getInstance()->unpauseAnimation();

    if (InputManager::getInstance()->escape)
    {
        ScreenManager::getInstance()->addScreen(close->toScreen);
		AnimationManager::getInstance()->pauseAnimation();
    }

    Screen::update();
}

void MultiplayerScreen::updateBlocks()
{
	int color;
	//fill in temp rows for p1
	for (int i = 0; i < GameStateObject::boardWidth; i++)
	{
		color = p1GSO.tempRow[i];
		sf::Color c(0, 0, 0, 200);
		switch (color)
		{
			//if its a 0 its empty?
		case 0:
		{
			p1NextBlocks[i].setFillColor(sf::Color::Transparent);
			p1NextBlocks[i].setOutlineThickness(-2);
			p1NextBlocks[i].setOutlineColor(sf::Color::Transparent);

			break;
		}
		case 1: //blue case
		{
			c.b = 128;
			p1NextBlocks[i].setFillColor(c);
			c.a = 255;
			p1NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p1NextBlocks[i].setOutlineColor(c);

			break;
		}
		case 2: //red case
		{
			c.r = 255;
			p1NextBlocks[i].setFillColor(c);
			c.a = 255;
			p1NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p1NextBlocks[i].setOutlineColor(c);

			break;
		}
		case 3://yellow case
		{
			c.r = 255;
			c.g = 140;
			p1NextBlocks[i].setFillColor(c);
			c.a = 255;
			p1NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p1NextBlocks[i].setOutlineColor(c);

			break;
		}
		case 4:// purple case
		{
			c.r = 148;
			c.b = 211;
			p1NextBlocks[i].setFillColor(c);
			c.a = 255;
			p1NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p1NextBlocks[i].setOutlineColor(c);

			break;
		}
		case 5://green case
		{
			c.r = 50;
			c.g = 205;
			c.b = 50;
			p1NextBlocks[i].setFillColor(c);
			c.a = 255;
			p1NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p1NextBlocks[i].setOutlineColor(c);

			break;
		}
		default: //error case
		{
			p1NextBlocks[i].setFillColor(sf::Color::Black);
			break;
		}
		}

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////


	//fill in temp rows for p2
	for (int i = 0; i < GameStateObject::boardWidth; i++)
	{
		color = p2GSO.tempRow[i];
		sf::Color c(0, 0, 0, 200);
		switch (color)
		{
			//if its a 0 its empty?
		case 0:
		{
			p2NextBlocks[i].setFillColor(sf::Color::Transparent);
			p2NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p2NextBlocks[i].setOutlineColor(sf::Color::Transparent);

			break;
		}
		case 1: //blue case
		{
			c.b = 128;
			p2NextBlocks[i].setFillColor(c);
			c.a = 255;
			p2NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p2NextBlocks[i].setOutlineColor(c);

			break;
		}
		case 2: //red case
		{
			c.r = 255;
			p2NextBlocks[i].setFillColor(c);
			c.a = 255;
			p2NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p2NextBlocks[i].setOutlineColor(c);

			break;
		}
		case 3://yellow case
		{
			c.r = 255;
			c.g = 140;
			p2NextBlocks[i].setFillColor(c);
			c.a = 255;
			p2NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p2NextBlocks[i].setOutlineColor(c);

			break;
		}
		case 4:// purple case
		{
			c.r = 148;
			c.b = 211;
			p2NextBlocks[i].setFillColor(c);
			c.a = 255;
			p2NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p2NextBlocks[i].setOutlineColor(c);

			break;
		}
		case 5://green case
		{
			c.r = 50;
			c.g = 205;
			c.b = 50;
			p2NextBlocks[i].setFillColor(c);
			c.a = 255;
			p2NextBlocks[i].setOutlineThickness(-blockSize / 8);
			p2NextBlocks[i].setOutlineColor(c);

			break;
		}
		default: //error case
		{
			p2NextBlocks[i].setFillColor(sf::Color::Black);
			break;
		}
		}

	}


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////


	int color1;
	int color2;

	for (int i = 0; i < GameStateObject::boardHeight; i++)
	{
		for (int j = 0; j < GameStateObject::boardWidth; j++)
		{
			color1 = p1GSO.gameBoard[i][j];
			color2 = p2GSO.gameBoard[i][j];
			sf::Color c(0, 0, 0, 200);
			switch (color1)
			{
				//if its a 0 its empty?
			case 0:
			{
					  p1Blocks[i][j].setFillColor(sf::Color::Transparent);
					  p1Blocks[i][j].setOutlineThickness(-blockSize / 8);
					  p1Blocks[i][j].setOutlineColor(sf::Color::Transparent);
					  break;
			}
			case 1:
			{
					  c.b = 128;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-blockSize / 8);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 2:
			{
					  c.r = 255;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-blockSize / 8);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 3:
			{
					  c.r = 255;
					  c.g = 140;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-blockSize / 8);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 4:
			{
					  c.r = 148;
					  c.b = 211;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-blockSize / 8);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 5:
			{
					  c.r = 50;
					  c.g = 205;
					  c.b = 50;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-blockSize / 8);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			default:
			{
					   p1Blocks[i][j].setFillColor(sf::Color::Black);
					   break;
			}
			}

			c = sf::Color(0, 0, 0, 200);
			//for player 2
			switch (color2)
			{
				//if its a 0 its empty?
			case 0:
			{
				p2Blocks[i][j].setFillColor(sf::Color::Transparent);
				p2Blocks[i][j].setOutlineThickness(-blockSize / 8);
				p2Blocks[i][j].setOutlineColor(sf::Color::Transparent);
				break;
			}
			case 1:
			{
				c.b = 128;
				p2Blocks[i][j].setFillColor(c);
				c.a = 255;
				p2Blocks[i][j].setOutlineThickness(-blockSize / 8);
				p2Blocks[i][j].setOutlineColor(c);
				break;
			}
			case 2:
			{
				c.r = 255;
				p2Blocks[i][j].setFillColor(c);
				c.a = 255;
				p2Blocks[i][j].setOutlineThickness(-blockSize / 8);
				p2Blocks[i][j].setOutlineColor(c);
				break;
			}
			case 3:
			{
				c.r = 255;
				c.g = 140;
				p2Blocks[i][j].setFillColor(c);
				c.a = 255;
				p2Blocks[i][j].setOutlineThickness(-blockSize / 8);
				p2Blocks[i][j].setOutlineColor(c);
				break;
			}
			case 4:
			{
				c.r = 148;
				c.b = 211;
				p2Blocks[i][j].setFillColor(c);
				c.a = 255;
				p2Blocks[i][j].setOutlineThickness(-blockSize / 8);
				p2Blocks[i][j].setOutlineColor(c);
				break;
			}
			case 5:
			{
				c.r = 50;
				c.g = 205;
				c.b = 50;
				p2Blocks[i][j].setFillColor(c);
				c.a = 255;
				p2Blocks[i][j].setOutlineThickness(-blockSize / 8);
				p2Blocks[i][j].setOutlineColor(c);
				break;
			}
			default:
			{
				p2Blocks[i][j].setFillColor(sf::Color::Black);
				break;
			}
			}
		}
	}

		
	
}
void MultiplayerScreen::draw()
{
	playerOneName->message.setString(ClientManager::getInstance().player.username);
	playerTwoName->message.setString(ClientManager::getInstance().opponentsName);

	Screen::draw();

	GraphicsManager::getInstance()->window.draw(p1Outline);
	GraphicsManager::getInstance()->window.draw(p2Outline);
	GraphicsManager::getInstance()->window.draw(tempRowRec1);
	GraphicsManager::getInstance()->window.draw(tempRowRec2);
	//draw the temp row and overlay the sprite on top for p1
	for (int i = 0; i < GameStateObject::boardWidth; i++)
	{
		GraphicsManager::getInstance()->window.draw(p1NextBlocks[i]);
		blockShape.setPosition(p1NextBlocks[i].getPosition());
		switch (p1GSO.tempRow[i])
		{
		case 1: //blue case
			blockShape.setTexture(*_getTexture("Textures/bluestar.png"));
			//defualt textures are 24 by 24 so scale them to match block size
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		case 2: //red case
			blockShape.setTexture(*_getTexture("Textures/redgear.png"));
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		case 3:// yellow case
			blockShape.setTexture(*_getTexture("Textures/yellowsquare.png"));
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		case 4://purple
			blockShape.setTexture(*_getTexture("Textures/purplespade.png"));
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		case 5://green
			blockShape.setTexture(*_getTexture("Textures/greentriangle.png"));
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		default:
			break;
		}
	}

	//draw the temp row and overlay the sprite on top for p2
	for (int i = 0; i < GameStateObject::boardWidth; i++)
	{
		GraphicsManager::getInstance()->window.draw(p2NextBlocks[i]);
		blockShape.setPosition(p2NextBlocks[i].getPosition());
		switch (p2GSO.tempRow[i])
		{
		case 1: //blue case
			blockShape.setTexture(*_getTexture("Textures/bluestar.png"));
			//defualt textures are 24 by 24 so scale them to match block size
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		case 2: //red case
			blockShape.setTexture(*_getTexture("Textures/redgear.png"));
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		case 3:// yellow case
			blockShape.setTexture(*_getTexture("Textures/yellowsquare.png"));
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		case 4://purple
			blockShape.setTexture(*_getTexture("Textures/purplespade.png"));
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		case 5://green
			blockShape.setTexture(*_getTexture("Textures/greentriangle.png"));
			blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
			GraphicsManager::getInstance()->window.draw(blockShape);
			break;
		default:
			break;
		}
	}

	//draws blocks on screen
	for (int i = 0; i < p1GSO.boardHeight; i++)
	{
		for (int j = 0; j < p1GSO.boardWidth; j++)
		{
			GraphicsManager::getInstance()->window.draw(p1Blocks[i][j]);
			
			if (!dangerColumns.empty() && dangerColumns.at(dangerColumnCounter).first == i && dangerColumns.at(dangerColumnCounter).second == j)
			{
				if (dangerColumnCounter < dangerColumns.size() - 1)
					dangerColumnCounter++;
				else
					dangerColumnCounter = 0;
			}
			else
			{//set the shape on the block
				blockShape.setPosition(p1Blocks[i][j].getPosition());
				//grab the color from gamestate
				switch (p1GSO.gameBoard[i][j])
				{
					//
				case 1: //blue case
					blockShape.setTexture(*_getTexture("Textures/bluestar.png"));
					//defualt textures are 24 by 24 so scale them to match block size
					blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
					GraphicsManager::getInstance()->window.draw(blockShape);
					break;
				case 2: //red case
					blockShape.setTexture(*_getTexture("Textures/redgear.png"));
					blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
					GraphicsManager::getInstance()->window.draw(blockShape);
					break;
				case 3:// yellow case
					blockShape.setTexture(*_getTexture("Textures/yellowsquare.png"));
					blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
					GraphicsManager::getInstance()->window.draw(blockShape);
					break;
				case 4://purple
					blockShape.setTexture(*_getTexture("Textures/purplespade.png"));
					blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
					GraphicsManager::getInstance()->window.draw(blockShape);
					break;
				case 5://green
					blockShape.setTexture(*_getTexture("Textures/greentriangle.png"));
					blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
					GraphicsManager::getInstance()->window.draw(blockShape);
					break;
				default:
					break;
				}
			}

		}
	}

	for (int i = 0; i < p2GSO.boardHeight; i++)
	{
		for (int j = 0; j < p2GSO.boardWidth; j++)
		{
			GraphicsManager::getInstance()->window.draw(p2Blocks[i][j]);
			//set the shape on the block
			blockShape.setPosition(p2Blocks[i][j].getPosition());
			//grab the color from gamestate
			switch (p2GSO.gameBoard[i][j])
			{
				//
			case 1: //blue case
				blockShape.setTexture(*_getTexture("Textures/bluestar.png"));
				//defualt textures are 24 by 24 so scale them to match block size
				blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			case 2: //red case
				blockShape.setTexture(*_getTexture("Textures/redgear.png"));
				blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			case 3:// yellow case
				blockShape.setTexture(*_getTexture("Textures/yellowsquare.png"));
				blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			case 4://purple
				blockShape.setTexture(*_getTexture("Textures/purplespade.png"));
				blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			case 5://green
				blockShape.setTexture(*_getTexture("Textures/greentriangle.png"));
				blockShape.setScale(sf::Vector2f((float)blockSize / 24, (float)blockSize / 24));
				GraphicsManager::getInstance()->window.draw(blockShape);
				break;
			default:
				break;
			}

		}
	}

	GraphicsManager::getInstance()->window.draw(ch->getMainCursor()); //draws main cursor
	if (ch->getCursorX() > 0)
		GraphicsManager::getInstance()->window.draw(ch->getLeftCursor()); //draws left cursor
	if (ch->getCursorX() < GameStateObject::boardWidth - 1)
		GraphicsManager::getInstance()->window.draw(ch->getRightCursor()); //draws right cursor
	if (ch->getCursorY() < GameStateObject::boardHeight - 1)
		GraphicsManager::getInstance()->window.draw(ch->getTopCursor()); //draws top cursor
	if (ch->getCursorY() > 0)
		GraphicsManager::getInstance()->window.draw(ch->getBottomCursor()); //draws bottom cursor

	GraphicsManager::getInstance()->window.draw(ch2->getMainCursor()); //draws p2 main cursor
	if (ch2->getCursorX() > 0)
		GraphicsManager::getInstance()->window.draw(ch2->getLeftCursor()); //draws p2 left cursor
	if (ch2->getCursorX() < GameStateObject::boardWidth - 1)
		GraphicsManager::getInstance()->window.draw(ch2->getRightCursor()); //draws p2 right cursor
	if (ch2->getCursorY() < GameStateObject::boardHeight - 1)
		GraphicsManager::getInstance()->window.draw(ch2->getTopCursor()); //draws p2 top cursor
	if (ch2->getCursorY() > 0)
		GraphicsManager::getInstance()->window.draw(ch2->getBottomCursor()); //draws p2 bottom cursor

	playerOneName->message.setColor(sf::Color::Black);
	playerTwoName->message.setColor(sf::Color::Black);
	timer->message.setColor(sf::Color::Black);
	nextRowLeft->message.setColor(sf::Color::Black);
	nextRowL2->message.setColor(sf::Color::Black);
	nextRowRight->message.setColor(sf::Color::Black);
	nextRowR2->message.setColor(sf::Color::Black);
	comboCounter->message.setColor(sf::Color::Black);
    
}

void MultiplayerScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_OUT;
}