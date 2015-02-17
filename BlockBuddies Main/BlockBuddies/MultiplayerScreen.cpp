#include "MultiplayerScreen.hpp"
#include "BlockShowerManager.hpp"
#include "AnimationManager.hpp"
MultiplayerScreen::MultiplayerScreen()
:blockSwitch(false), pressed(false), pressed2(false), reset(false)
{
	initGame();
	swapSound.setBuffer(*SoundManager::getInstance().getSound("heya"));

}

void MultiplayerScreen::initGame()
{
	winX = GraphicsManager::getInstance()->window.getSize().x;
	winY = GraphicsManager::getInstance()->window.getSize().y;

	//fill in initial board
	int gridPosy = 0;
	int gridPosx = 0;
	blockSizeX = 25;
	blockSizeY = 25;

	int offset = winY - SCREENHEIGHT;

	ch = new CursorHandler(SCREENWIDTH, SCREENHEIGHT, winX, winY, winX / 2 - SCREENWIDTH * 3 / 2, winY / 2 - SCREENHEIGHT / 2, blockSizeX, 0);

	//draws a large rectangle around the game screen for p1
	p1Outline.setSize(sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	p1Outline.setFillColor(sf::Color::Transparent);
	p1Outline.setPosition(winX / 2 - SCREENWIDTH * 3 / 2, winY / 2 - SCREENHEIGHT / 2);
	p1Outline.setOutlineThickness(25);
	p1Outline.setOutlineColor(sf::Color::Black);
	//draws a large rectangle around the game screen for p2
	p2Outline.setSize(sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));
	p2Outline.setFillColor(sf::Color::Transparent);
	p2Outline.setPosition(winX / 2 + SCREENWIDTH / 2, winY / 2 - SCREENHEIGHT / 2);
	p2Outline.setOutlineThickness(25);
	p2Outline.setOutlineColor(sf::Color::Black);


	//creates blocks and puts them in 2D array for p1
	for (int i = SCREENHEIGHT; i > 0; i -= blockSizeY)
	{
		for (int j = 0; j < SCREENWIDTH; j += blockSizeX)
		{

			sf::RectangleShape shape(sf::Vector2f(blockSizeX, blockSizeY));
			shape.setPosition(j + (winX / 2 - SCREENWIDTH * 3 / 2), i - ((winY / 2) - SCREENHEIGHT) - 5 ); //puts it in the middle of the screen
			shape.setFillColor(sf::Color::Transparent); //transparent blocks to appear as empty space
			p1Blocks[gridPosx][gridPosy] = shape;
			gridPosy++;
		}
		gridPosy = 0;
		gridPosx++;
	}

	gridPosx = 0;
	gridPosy = 0;
	for (int i = SCREENHEIGHT; i > 0; i -= blockSizeY)
	{
		for (int j = 0; j < SCREENWIDTH; j += blockSizeX)
		{

			sf::RectangleShape shape(sf::Vector2f(blockSizeX, blockSizeY));
			shape.setPosition(j + (winX / 2 + SCREENWIDTH / 2), i - ((winY / 2) - SCREENHEIGHT ) - 5); //puts it in the middle of the screen
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

				AnimationManager::getInstance()->add(p1Blocks[y][x], p1Blocks[y][x - 1]);
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

				AnimationManager::getInstance()->add(p1Blocks[y][x], p1Blocks[y][x + 1]);

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

				AnimationManager::getInstance()->add(p1Blocks[y][x], p1Blocks[y + 1][x]);
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

				AnimationManager::getInstance()->add(p1Blocks[y][x], p1Blocks[y - 1][x]);
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
	AnimationManager::getInstance()->update();
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