#include "ClientManager.h"
#include "windows.h"
#include <iostream>
#include "MessageType.h"
#include "ScreenManager.hpp"
#include "LoginScreen.hpp"
//Connects to the server socket
//Currently connects on the local machine only

bool ClientManager::initConnection(sf::IpAddress IP, int portNumber)
{
	//Tries to connect
	sf::Socket::Status status = socket.connect(IP, portNumber);
	//Checks if it was able to connect
	if (status != sf::Socket::Done)
	{
		isConnected = false;
		return false;
	}
	else 
	{
		isConnected = true;

        sendAliveTimer.restart();
        receiveAliveTimer.restart();

        // Hidden this parameter
        messageThread = std::thread(&ClientManager::messageWait, this);
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
		std::cout << "its a packet with code :" << code << std::endl;
		switch (code)
		{
			case PacketDecode::PACKET_GAMESTATE:
			{
				packet >> currentGSO;
				isUpdated = true;
				std::cout << "were updating the gso \n";
				break;
			}

            case PacketDecode::PACKET_CHECKALIVE:
            {
                receiveAliveTimer.restart();
               // std::cout << "Receive check alive packet" << std::endl;
                break;
            }

			case PacketDecode::PACKET_GAMEOVER:
			{
				gameOver = true;
				std::cout << "game Over \n";
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
      //  std::cout << "Send check alive packet" << std::endl;
    }

    // Disconnects if no response from server
    if(receiveAliveTimer.getElapsedTime().asSeconds() > receiveAliveLimit)
    {
        std::cout << "No response from server, disconnecting" << std::endl;
        ScreenManager::getInstance()->switchScreen(Screens::LOGIN);

        // Some funky casting to write message onto LoginScreen's status.
        // Most likely we'll remove this and replace the connection lost 
        // notification with a popup window
        dynamic_cast<LoginScreen*>((ScreenManager::getInstance()->currentScreens)[0])->status->message.setString("Lost connection with server");

        ClientManager::getInstance().closeConnection();
    }
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

    // Block until we receive a message
    while(receivedPackets.empty()) 
    {
        std::cout << "looping..." << std::endl;
    }

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
		return true;
	}
    else
        return false;
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

    // Block until a packet is in the queue
    while(receivedPackets.empty()) {}

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

void ClientManager::requestStartGame()
{
	sf::Packet toSend;
	toSend = messageMaker.StartPacket();
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
			std::cout << "packet came in \n";
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