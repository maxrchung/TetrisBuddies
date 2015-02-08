#pragma once
#include "UserInfo.h"
#include <SFML/Network.hpp>
#include <queue>
class Player
{
public:
	Player(sf::TcpSocket* userSocket);
	Player();
	~Player();

	UserInfo playerInfo;
	sf::TcpSocket* playerSocket;
    std::queue<sf::Packet> receivedPackets;

    sf::Clock receiveAliveTimer;
	sf::IpAddress myAddress;
    // Server automatically removes the player after
    // some time limit
    static int receiveAliveLimit;
    
	Player& operator=(Player p);
    bool operator==(Player p);
};

