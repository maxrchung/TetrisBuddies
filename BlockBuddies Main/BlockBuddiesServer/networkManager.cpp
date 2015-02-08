#include "NetworkManager.h"
#include "DatabaseManager.h"
#include "Player.h"
#include "UserInfo.h"
#include <iostream>
#include "MessageType.h"

NetworkManager* NetworkManager::instance;

NetworkManager* NetworkManager::getInstance()
{
	if(!instance)
		instance = new NetworkManager;
	return instance;
}

void NetworkManager::init()
{
    messageThread = std::thread(&NetworkManager::checkForConnections, this);
    multiplayer = MatchMakingHandler();
}

void NetworkManager::newHighScore(int newScore, std::string username)
{
	DatabaseManager::getInstance().updateNewHighScore(username,newScore);
}

//Used to indicate a loss or a win by passing true or false
void NetworkManager::addWin(std::string username, bool win)
{
	DatabaseManager::getInstance().updateUserGames(username, win);
}



// Loops through player packet queues and responds to
// each packet
void NetworkManager::update()
{
    // Needed for removing a player from the list

    Player* toDisconnect = NULL;

    for(auto& player : connectPlayers)
    {
		
        if(!player.receivedPackets.empty())
        {
            sf::Packet packet = player.receivedPackets.front();
            queueAccess.lock();
            player.receivedPackets.pop();
            queueAccess.unlock();
			
			sf::Packet notPopped;
			notPopped = packet;

            std::cout << std::endl;
            std::cout << "Popped off packet" << std::endl;

            PacketDecode decode;
            int decodeIndex;
            packet >> decodeIndex;
            decode = PacketDecode(decodeIndex);
			
			
            switch(decode)
            {
                case PacketDecode::PACKET_LOGIN:
                {
					//gameHandler.ResetGame();
                    std::string user;
                    std::string pass;
                    packet >> user 
                           >> pass;
                    if (DatabaseManager::getInstance().loginUser(user, pass))
                    {
                        UserInfo userInfo = DatabaseManager::getInstance().getUserInfo(user);
                        player.playerInfo = userInfo;
                        sf::Packet answer;
                        answer << true // Indicates successful login
                               << userInfo;
                        player.playerSocket->send(answer);

                        std::cout << "Sent login packet accept" << std::endl;
                    }
                    else
                    {
                        sf::Packet answer;
                        answer << false;
                        player.playerSocket->send(answer);
                        std::cout << "Sent login packet reject" << std::endl;
                    }
                    break;
                }

                case PacketDecode::PACKET_REGISTER:
                {
                    std::string user;
                    std::string pass;
                    packet >> user 
                           >> pass;

                    // Returns true if a user can be registered
                    // else returns false if the account already exists
                    if (DatabaseManager::getInstance().registerUser(user, pass))
                    {
                        int i = 1;
                        UserInfo userInfo = DatabaseManager::getInstance().getUserInfo(user);
                        sf::Packet answer;
                        answer << true
                               << userInfo;
                        player.playerSocket->send(answer);

                        std::cout << "Sent packet register accept" << std::endl;
                    }
                    else
                    {
                        sf::Packet answer;
                        answer << false;
                        player.playerSocket->send(answer);

                        std::cout << "Sent packet register reject" << std::endl;
                    }
                    break;
                }

                // A player is ready to join the queue
				case PacketDecode::PACKET_JOINQUEUE:
				{
					multiplayer.activePlayers.push_back(player);
					multiplayer.checkForMatches();

                    std::cout << "Received packet join queue" << std::endl;
                    std::cout << "activePlayers" << std::endl;
                    for(int i = 0; i < multiplayer.activePlayers.size(); i++)
                        std::cout << multiplayer.activePlayers[i].myAddress << std::endl;
                    break;
				}

                case PacketDecode::PACKET_LEAVEQUEUE:
                {
                    int toRemove = -1;
                    for(int i = 0; i < (int) multiplayer.activePlayers.size(); i++)
                    {
                        // Removes the player from the queue by looping and matching IP addresses
                        if(multiplayer.activePlayers[i].myAddress == player.myAddress)
                        {
                            toRemove = i;
                        }
                    }

                    if(toRemove != -1)
                        multiplayer.activePlayers.erase(multiplayer.activePlayers.begin() + toRemove);

                    std::cout << "activePlayers" << std::endl;
                    for(int i = 0; i < multiplayer.activePlayers.size(); i++)
                        std::cout << multiplayer.activePlayers[i].myAddress << std::endl;

                    std::cout << "Received packet leave queue" << std::endl;
                    break;
                }

                case PacketDecode::PACKET_DISCONNECT:
                {
                    sf::Packet answer;
                    answer << PacketDecode::PACKET_DISCONNECT;
                    player.playerSocket->send(answer);
                    std::cout << "Sent disconnect packet" << std::endl;

                    toDisconnect = &player;
                    break;
                }

                case PacketDecode::PACKET_CHECKALIVE:
                {
                    std::cout << "Received checkalive packet" << std::endl;
                    player.receiveAliveTimer.restart();

                    break;
                }
                default:
                {
					if (!singlePlayer.singlePlayer.count(player.myAddress))
						singlePlayer.makeGame(player);

					singlePlayer.addMessage(notPopped, player.myAddress);
					
					break;
				}
            }
       }

	   if (tick.asSeconds() < 1)
	   {
		   tick += clock.getElapsedTime();
	   }
	   else
	   {
		   singlePlayer.update();
		   tick = sf::Time::Zero;
		   clock.restart();
	   }
       
       if (singlePlayer.singlePlayer.size() >= 1)
       {
           while (!singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.outgoingMessages.empty())
           {
               sf::Packet toSend = singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.outgoingMessages.front();
               singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.outgoingMessages.pop();
               player.playerSocket->send(toSend);
           }
       }



       // Remove player if he has not responded
       if (player.receiveAliveTimer.getElapsedTime().asSeconds() > Player::receiveAliveLimit)
           toDisconnect = &player;
    }

    // Disconnect afterwards so we don't run into iterating problems
    if (toDisconnect)
    {
        std::cout << "Size of connectPlayers: " << connectPlayers.size() << std::endl;
        queueAccess.lock();
        connectPlayers.remove(*toDisconnect);
        queueAccess.unlock();
        std::cout << "Removed disconnected player" << std::endl;
        std::cout << "Size of connectPlayers: " << connectPlayers.size() << std::endl;
    }

    // Send an alive message periodically to all the players
    if(sendAliveTimer.getElapsedTime().asSeconds() > sendAliveInterval)
    {
        sendAliveTimer.restart();

        sf::Packet packet;
        packet << PacketDecode::PACKET_CHECKALIVE;

        for(auto& player : connectPlayers)
        {
            std::cout << "Send check alive packet" << std::endl;
            player.playerSocket->send(packet);
        }
    }

    multiplayer.update();
}

// Checks for conneciton requests and incoming messages
void NetworkManager::checkForConnections()
{
	listener.listen(5000);
	connections.add(listener);

	while (running)
	{
		// Make the selector wait for data on any socket
		if (connections.wait())
		{
			//If incoming connection add it else check others for packets
			if (connections.isReady(listener))
			{
				sf::TcpSocket* client = new sf::TcpSocket;
				if (listener.accept(*client) == sf::Socket::Done)
				{
                    connectPlayers.push_back(Player(client));
					connections.add(*client);
				}
				else
				{
					delete client;
				}
			}

			else
			{
                queueAccess.lock();
				// The listener socket is not ready, test all other sockets (the clients)
				for (auto& player : connectPlayers)
				{
					if (connections.isReady(*player.playerSocket))
					{
						sf::Packet packet;
                        if(player.playerSocket->receive(packet) == sf::Socket::Done)
						{
                            player.receivedPackets.push(packet);
							
						}
                    }
                }
                queueAccess.unlock();
            }
        }
    }
}