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
}

void NetworkManager::newHighScore(int newScore, std::string username)
{
	//DatabaseManager::getInstance().updateNewHighScore(username,newScore);
}

//Used to indicate a loss or a win by passing true or false
void NetworkManager::addWin(std::string username, bool win)
{
	//DatabaseManager::getInstance().updateUserGames(username, win);
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
					databaseAccess.lock();
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
					databaseAccess.unlock();
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
					databaseAccess.lock();
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
					databaseAccess.unlock();
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

				case PacketDecode::PACKET_MULTIPLAYERQUEUE:
				{
					multiplayer.activePlayers.push(player);
					multiplayer.checkForMatches();
				} 

				default:
				{
					if (!singlePlayer.singlePlayer.count(player.myAddress))
						singlePlayer.makeGame(player);

					singlePlayer.addMessage(notPopped, player.myAddress);
					//gameHandler.ReceiveMessage(notPopped);
					//gameHandler.GameTick();

					//!gameHandler.outgoingMessages.empty()
					//This might need to be changed to allow only one message per tick.
					
					break;
				}
            }

			if (singlePlayer.singlePlayer.count(player.myAddress))
			{ 

			if (singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.gameHasStarted && singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.isGameOver)
			{
				sf::Packet lost;
				lost << PacketDecode::PACKET_GAMEOVER;
				int result;
				if (player.playerInfo.highScore < singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.GetScore())
				{
					databaseAccess.lock();
					bool works = false;
					while (!works)
					{
						works = DatabaseManager::getInstance().updateNewHighScore(player.playerInfo.username, singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.GetScore());
						if (works == false)
						{
							std::chrono::milliseconds dura(2000);
							std::this_thread::sleep_for(dura);
						}
					}
					databaseAccess.unlock();

					sf::Packet update;

					databaseAccess.lock();
					update << PacketDecode::PACKET_USERINFOUPDATE;
					update << DatabaseManager::getInstance().getUserInfo(player.playerInfo.username);
					databaseAccess.unlock();

					player.playerSocket->send(update);
					std::cout << "/////////////////////////////////////////////////////////////////////////////"
						<< "\ngameOver Sent \n";
				}
				player.playerSocket->send(lost);
				singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.ResetGame();
				std::cout << "/////////////////////////////////////////////////////////////////////////////"
					<<"\ngameOver Sent \n";
				
			}
		}

			if (singlePlayer.singlePlayer.size() >= 1)
			{
				singlePlayer.update();
				while (!singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.outgoingMessages.empty())
				{
					sf::Packet toSend = singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.outgoingMessages.front();
					singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.outgoingMessages.pop();
					player.playerSocket->send(toSend);
				}

			}

       }

		if (singlePlayer.singlePlayer.count(player.myAddress) && !singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.IsGameOver())
		{
			if (tick.asMilliseconds() < 10)
			{
				tick += clock.getElapsedTime();
			}
			else
			{
				singlePlayer.singlePlayer.at(player.myAddress)->playerOneGame.GameTick();
				tick = sf::Time::Zero;
			}

			clock.restart();
		}

		// Remove player if he has not responded
		if(player.receiveAliveTimer.getElapsedTime().asSeconds() > Player::receiveAliveLimit)
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