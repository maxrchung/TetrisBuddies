#include "MultiplayerScreen.hpp"
#include "BlockShowerManager.hpp"
#include "AnimationManager.hpp"
#include <cmath>
MultiplayerScreen::MultiplayerScreen()
:blockSwitch(false), pressed(false), pressed2(false), reset(false)
{
	initGame();
	swapSound.setBuffer(*SoundManager::getInstance().getSound("heya"));

}

void MultiplayerScreen::initGame()
{
	//fill in initial board
	int gridPosy = 0;
	int gridPosx = 0;
	blockSize = (GraphicsManager::getInstance()->window.getSize().y/ p1GSO.boardHeight) * .9;

	winX = GraphicsManager::getInstance()->window.getSize().x - (GraphicsManager::getInstance()->window.getSize().x % blockSize);
	winY = GraphicsManager::getInstance()->window.getSize().y - (GraphicsManager::getInstance()->window.getSize().y % blockSize);

	AnimationManager::getInstance()->setBlockSize(blockSize);

	int gbHeight = (p1GSO.boardHeight * blockSize);
	int gbWidth = (blockSize * p1GSO.boardWidth);
	
	int p1OutlineX = blockSize;
	int p1OutlineY = (winY / 2 - gbHeight / 2) - ((winY / 2 - gbHeight / 2) % blockSize);
	int p2OutlineX = winX - (gbWidth + blockSize);
	int p2OutlineY = (winY / 2 - gbHeight / 2) - ((winY / 2 - gbHeight / 2) % blockSize);

	int offset = (winX % blockSize);

	ch = new CursorHandler(gbWidth, gbHeight, winX, winY, p1OutlineX, p1OutlineY, blockSize, offset);

	//draws a large rectangle around the game screen for p1
	p1Outline.setSize(sf::Vector2f(gbWidth, gbHeight));
	p1Outline.setFillColor(sf::Color::Transparent);
	p1Outline.setPosition(p1OutlineX + blockSize, p1OutlineY + blockSize);
	p1Outline.setOutlineThickness(blockSize);
	p1Outline.setOutlineColor(sf::Color::Black);
	//draws a large rectangle around the game screen for p2
	p2Outline.setSize(sf::Vector2f(gbWidth, gbHeight));
	p2Outline.setFillColor(sf::Color::Transparent);
	p2Outline.setPosition(p2OutlineX - blockSize, p2OutlineY + blockSize);
	p2Outline.setOutlineThickness(blockSize);
	p2Outline.setOutlineColor(sf::Color::Black);


	//creates blocks and puts them in 2D array for p1
	for (int i = gbHeight; i > 0; i -= blockSize)
	{
		for (int j = 0; j < gbWidth; j += blockSize)
		{
			sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
			shape.setPosition(j + p1OutlineX + blockSize, i - p1OutlineY + blockSize *2); //puts it in the middle of the screen
			shape.setFillColor(sf::Color::Transparent); //transparent blocks to appear as empty space
			p1Blocks[gridPosx][gridPosy] = shape;
			gridPosy++;
		}
		gridPosy = 0;
		gridPosx++;
	}

	gridPosx = 0;
	gridPosy = 0;
	for (int i = gbHeight; i > 0; i -= blockSize)
	{
		for (int j = 0; j < gbWidth; j += blockSize)
		{

			sf::RectangleShape shape(sf::Vector2f(blockSize, blockSize));
			shape.setPosition(j + p2OutlineX - blockSize, i - p2OutlineY + blockSize *2); //puts it in the middle of the screen
			shape.setFillColor(sf::Color::Transparent); //transparent blocks to appear as empty space
			p2Blocks[gridPosx][gridPosy] = shape;
			gridPosy++;
		}
		gridPosy = 0;
		gridPosx++;
	}
}
void MultiplayerScreen::update()
{
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
			p1GSO = ClientManager::getInstance().currentGSO;
			p2GSO = ClientManager::getInstance().secondGSO;
			ClientManager::getInstance().isUpdated = false;

			if (p1GSO.newRowActive){
				ch->Up(sf::Keyboard::Key::Up);

			}
			updateBlocks();

			if (!p1GSO.clearingBlocks.empty())
			{
				for (int i = 0; i < p1GSO.clearingBlocks.size(); i++)
				{
					AnimationManager::getInstance()->addClear(p1Blocks[p1GSO.clearingBlocks.at(i).first][p1GSO.clearingBlocks.at(i).second]);
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

				int y = ch->getCursorY();
				int x = ch->getCursorX();

				AnimationManager::getInstance()->addSwap(p1Blocks[y][x], p1Blocks[y][x - 1]);
				pressed2 = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //swaps the main block with the right block
		{
			if (pressed2 == false && ch->getCursorX() < 15)//cant switch if right block is off screen
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
			if (pressed2 == false && ch->getCursorY() < 19) // cant switch if top block is offscreen
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
		SoundManager::getInstance().playMusic("Sounds/Slamstorm.ogg");
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

    if (InputManager::getInstance()->escape)
    {
        ScreenManager::getInstance()->addScreen(close->toScreen);
    }

    Screen::update();
}

void MultiplayerScreen::updateBlocks()
{
	int color1;

	for (int i = 0; i < p1GSO.boardHeight; i++)
	{
		for (int j = 0; j < p1GSO.boardWidth; j++)
		{
			color1 = p1GSO.gameBoard[i][j];
			sf::Color c(0, 0, 0, 200);
			switch (color1)
			{
				//if its a 0 its empty?
			case 0:
			{
					  p1Blocks[i][j].setFillColor(sf::Color::Transparent);
					  p1Blocks[i][j].setOutlineThickness(-2);
					  p1Blocks[i][j].setOutlineColor(sf::Color::Transparent);
					  break;
			}
			case 1:
			{
					  c.b = 128;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-2);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 2:
			{
					  c.r = 255;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-2);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 3:
			{
					  c.r = 255;
					  c.g = 140;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-2);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 4:
			{
					  c.r = 148;
					  c.b = 211;
					  p1Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p1Blocks[i][j].setOutlineThickness(-2);
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
					  p1Blocks[i][j].setOutlineThickness(-2);
					  p1Blocks[i][j].setOutlineColor(c);
					  break;
			}
			default:
			{
					   p1Blocks[i][j].setFillColor(sf::Color::Black);
					   break;
			}
			}
		}
	}

	for (int i = 0; i < p2GSO.boardHeight; i++)
	{
		for (int j = 0; j < p2GSO.boardWidth; j++)
		{
			color1 = p2GSO.gameBoard[i][j];
			sf::Color c(0, 0, 0, 200);
			switch (color1)
			{
				//if its a 0 its empty?
			case 0:
			{
					  p2Blocks[i][j].setFillColor(sf::Color::Transparent);
					  p2Blocks[i][j].setOutlineThickness(-2);
					  p2Blocks[i][j].setOutlineColor(sf::Color::Transparent);
					  break;
			}
			case 1:
			{
					  c.b = 128;
					  p2Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p2Blocks[i][j].setOutlineThickness(-2);
					  p2Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 2:
			{
					  c.r = 255;
					  p2Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p2Blocks[i][j].setOutlineThickness(-2);
					  p2Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 3:
			{
					  c.r = 255;
					  c.g = 140;
					  p2Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p2Blocks[i][j].setOutlineThickness(-2);
					  p2Blocks[i][j].setOutlineColor(c);
					  break;
			}
			case 4:
			{
					  c.r = 148;
					  c.b = 211;
					  p2Blocks[i][j].setFillColor(c);
					  c.a = 255;
					  p2Blocks[i][j].setOutlineThickness(-2);
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
					  p2Blocks[i][j].setOutlineThickness(-2);
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
	Screen::draw();

	GraphicsManager::getInstance()->window.draw(p1Outline);
	GraphicsManager::getInstance()->window.draw(p2Outline);
	//draws blocks on screen
	for (int i = 0; i < p1GSO.boardHeight; i++)
	{
		for (int j = 0; j < p1GSO.boardWidth; j++)
		{
			GraphicsManager::getInstance()->window.draw(p1Blocks[i][j]);
			//set the shape on the block
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
	GraphicsManager::getInstance()->window.draw(ch->getLeftCursor()); //draws left cursor
	GraphicsManager::getInstance()->window.draw(ch->getRightCursor()); //draws right cursor
	GraphicsManager::getInstance()->window.draw(ch->getTopCursor()); //draws top cursor
	GraphicsManager::getInstance()->window.draw(ch->getBottomCursor()); //draws bottom cursor

    
}

void MultiplayerScreen::reload()
{
    BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_OUT;
}