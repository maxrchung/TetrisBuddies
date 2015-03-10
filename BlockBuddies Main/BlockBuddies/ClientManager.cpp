#include "ClientManager.h"
#include "windows.h"
#include <iostream>
#include "MessageType.h"
#include "ScreenManager.hpp"
#include "LoginScreen.hpp"
#include "Game.hpp"
#include "QueueScreen.hpp"
#include "BlockShowerManager.hpp"
//Connects to the server socket
//Currently connects on the local machine only

bool ClientManager::initConnection(sf::IpAddress IP, int portNumber)
{
    Game::getInstance()->startLoadingThread();
	//Tries to connect
	sf::Socket::Status status = socket.connect(IP, portNumber);
	multiplayer = false;
	//Checks if it was able to connect
	if (status != sf::Socket::Done)
	{
		isConnected = false;
        Game::getInstance()->stopLoadingThread();
		return false;
	}
	else 
	{
		isConnected = true;

        sendAliveTimer.restart();
        receiveAliveTimer.restart();

        // Hidden this parameter
        messageThread = std::thread(&ClientManager::messageWait, this);
        Game::getInstance()->stopLoadingThread();
		return true;
	}
	isUpdated = false;
	gameOver = false;
}

void ClientManager::update()
{
    // No point in continuing further if you're not connected
    // with the server
    if(!isConnected)
        return;

    if(!receivedPackets.empty())
    {
        sf::Packet packet = receivedPackets.front();
        queueAccess.lock();
        receivedPackets.pop();
        queueAccess.unlock();

        /*PacketDecode decode;
        int decodeIndex;
        packet >> decodeIndex;
        decode = PacketDecode(decodeIndex); 
		*/

        // There are no packets that are currently handled in this function 
        // This is because when you call loginUser() or registerUser()
        // you automatically block in these functions until the server
        // responds or your request times out
        
        // We will, however, most likely need this section for things that 
        // require constant updates, such as game updates
		int code;
        packet >> code;
        std::cout << std::endl;
        std::cout << "Send check alive packet" << std::endl;

		switch (code)
		{
			case PacketDecode::PACKET_GAMESTATE:
			{
				if (!multiplayer)
				{
					//Temp storage. Does nothing
					bool temp;
					packet >> temp;
					packet >> currentGSO;
					isUpdated = true;
					std::cout << "were updating the gso \n";
				}
				else
				{
					bool PlayerTwo;
					packet >> PlayerTwo;
					if (!PlayerTwo && !isPlayerTwo)
					{ 
						std::cout << "I've got player one's GSO! \n";
						packet >> currentGSO;
						isUpdated = true;
						packetCount++;
					}
					else
					{
						packet >> secondGSO;
						std::cout << "I've got player two's GSO! \n";
						isOpponentUpdated = true;
						packetCount = 0;
					}
				}
				break;
			}
			case PacketDecode::PACKET_PLAYERNUMBER:
			{
				bool temp;
				packet >> temp;
				isPlayerTwo = temp;
				if (!isPlayerTwo)
					std::cout << "I'm player oneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee" << std::endl;
				else
					std::cout << "I'm player twoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" << std::endl;

				break;
			}

            case PacketDecode::PACKET_CHECKALIVE:
            {
                receiveAliveTimer.restart();
                std::cout << "Receive check alive packet" << std::endl;
                break;
            }

            case PacketDecode::PACKET_FOUNDGAME:
            {
                ((QueueScreen*)ScreenManager::getInstance()->currentScreens.back())->foundGame();
				multiplayer = true;
                std::cout << "Receive found game packet" << std::endl;
				break;
            }

			case PacketDecode::PACKET_GAMEOVER:
			{
				gameOver = true;
				wonGame = false;
				lastScore = currentGSO.score;
				currentGSO = GameStateObject();
				std::cout << "game Over \n";
				break;
			}
			case PacketDecode::PACKET_USERINFOUPDATE:
			{
				std::string saveName = player.username;
				packet >> player;
				player.username = saveName;
				infoUpdate = true;
				break;
			}
			case PacketDecode::PACKET_WINNER:
			{
				wonGame = true;
				gameOver = true;
				break;
			}
			case PacketDecode::PACKET_CLEAR:
			{
				//fill me in
				break;
			}
			default:
			{
			    break;
			}
		}
    }

    // Sends a packet periodically to tell the server that it is alive
    if(sendAliveTimer.getElapsedTime().asSeconds() > sendAliveInterval)
    {
        sendAliveTimer.restart();

        //Sends the check alive packet
        sf::Packet checkAlive;
        checkAlive << PacketDecode::PACKET_CHECKALIVE;

        socket.send(checkAlive);
        std::cout << "Send check alive packet" << std::endl;
    }

    // Disconnects if no response from server
    if(receiveAliveTimer.getElapsedTime().asSeconds() > receiveAliveLimit)
    {
        std::cout << "No response from server, disconnecting" << std::endl;

        ScreenManager::getInstance()->switchScreen(Screens::LOGIN);
        BlockShowerManager::getInstance()->fade.state = FadeStates::FADING_IN;
        ScreenManager::getInstance()->addScreen(Screens::NOTIFICATION, "The game lost connection with the server. The server may be down or your connection may have dropped.");


        ClientManager::getInstance().closeConnection();
    }
}

void ClientManager::sendCursorUpdate(int x, int y)
{
	sf::Packet cursorUpdate;
	cursorUpdate << PacketDecode::PACKET_CURSORPOSITION;
	cursorUpdate << x;
	cursorUpdate << y;
	socket.send(cursorUpdate);
}

bool ClientManager::isMultiplayer()
{
	return multiplayer;
}

bool ClientManager::loginUser(std::string username , std::string password)
{
	//Sends the log in
	sf::Packet login;
	login << PacketDecode::PACKET_LOGIN
          << username 
          << password;

    queueAccess.lock();
    // Clear the queue before taking in the result
    receivedPackets = std::queue<sf::Packet>();
    queueAccess.unlock();

	socket.send(login);
    std::cout << "Send login packet" << std::endl;

    Game::getInstance()->startLoadingThread();

    // Block until we receive a message
    while(receivedPackets.empty()) 
    {
        std::cout << "looping..." << std::endl;
    }

    Game::getInstance()->stopLoadingThread();

	sf::Packet result = receivedPackets.front();
    queueAccess.lock();
    receivedPackets.pop();
    queueAccess.unlock();

    std::cout << "Receive login packet" << std::endl;

	bool success;
	result >> success;

	if (success)
	{
        // See UserInfo's >> overload
		result >> player;
		infoUpdate = true;
		return true;
	}
    else
        return false;
}

void ClientManager::leaveGameEarly()
{
	sf::Packet leaveGame;
	leaveGame << PacketDecode::PACKET_EARLYREMOVE;
	socket.send(leaveGame);
}

bool ClientManager::registerUser(std::string username, std::string password)
{
	sf::Packet registerPacket;
    registerPacket << PacketDecode::PACKET_REGISTER
                   << username
                   << password;
    queueAccess.lock();
    // Clear the queue before taking in the result
    receivedPackets = std::queue<sf::Packet>();
    queueAccess.unlock();
	socket.send(registerPacket);
    std::cout << "Sending register packet" << std::endl;

    Game::getInstance()->startLoadingThread();

    // Block until a packet is in the queue
    while(receivedPackets.empty()) {}

    Game::getInstance()->stopLoadingThread();

	sf::Packet result = receivedPackets.front();
    queueAccess.lock();
    receivedPackets.pop();
    queueAccess.unlock();

    std::cout << "Receive register packet" << std::endl;

	bool success;
	result >> success;

	if(success)
	{
        // See UserInfo's >> overload
        result >> player;
        return true;
	}
    else
		return false;
}

void ClientManager::joinQueue()
{
    sf::Packet joinPacket;
    joinPacket << PacketDecode::PACKET_JOINQUEUE;
	socket.send(joinPacket);
    

    std::cout << "Sending joinQueue packet" << std::endl;
}

void ClientManager::leaveQueue()
{
    sf::Packet leavePacket;
    leavePacket << PacketDecode::PACKET_LEAVEQUEUE;
	socket.send(leavePacket);

    std::cout << "Sending leaveQueue packet" << std::endl;
}

void ClientManager::requestStartGame()
{
	sf::Packet toSend;
	toSend = messageMaker.StartPacket();
	gameOver = false;
	socket.send(toSend);
}

void ClientManager::requestMultiplayerGame()
{
	sf::Packet toSend;
	toSend = messageMaker.RequestMultiplayer();
	socket.send(toSend);
}

void ClientManager::insertPenaltyRow()
{
	sf::Packet requestPR;
	requestPR << PacketDecode::PACKET_NEWPENALTYROW;
	socket.send(requestPR);
}

void ClientManager::requestNewRow(){
	sf::Packet toSend;
	toSend = messageMaker.NewRowPacket();
	socket.send(toSend);
}

void ClientManager::requestSwap(sf::Uint8 p1row, sf::Uint8 p1col, sf::Uint8 p2row, sf::Uint8 p2col)
{
	sf::Packet toSend;
	toSend = messageMaker.SwapPacket(p1row, p1col, p2row, p2col);
	socket.send(toSend);

}



void ClientManager::messageWait()
{	
	while (isConnected)
	{
		sf::Packet packet;
		if (socket.receive(packet) != sf::Socket::Done)
		{
            // Error message
		}
		else
		{
            queueAccess.lock();
            receivedPackets.push(packet);
            queueAccess.unlock();
		}
	}
}

// Disconnects socket and (wow)closes connection
void ClientManager::closeConnection()
{
    isConnected = false;

    sf::Packet disconnect;
    disconnect << PacketDecode::PACKET_DISCONNECT;
    queueAccess.lock();
    // Clear the queue before taking in the result
    receivedPackets = std::queue<sf::Packet>();
    queueAccess.unlock();
	socket.send(disconnect);
    std::cout << "Sending disconnect packet" << std::endl;

    socket.disconnect();

    // This blocks the current thread until messageThread stops
    messageThread.join();
}