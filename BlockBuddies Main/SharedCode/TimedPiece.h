#ifndef TIMEDPIECE_H
#define TIMEDPIECE_H


#include <utility>
#include <SFML/Network.hpp>

//this is for every piece that needs something to happen to it
//blockNum: the coordinates of the block
//duration: how long until the event happens
struct TimedPiece{
	std::pair<int, int> blockNum;
	int duration;

	TimedPiece(){
		blockNum.first = 0;
		blockNum.second = 0;
		duration = 0;
	}

	TimedPiece(int x, int y, int z){
		blockNum.first = x;
		blockNum.second = y;
		duration = z;
	}

	bool operator < (const TimedPiece& str) const
	{return (duration < str.duration);}

	bool operator >(const TimedPiece& str) const
	{return (duration > str.duration);}

};

//sf::Packet& operator <<(sf::Packet& packet, const TimedPiece& tp){return packet << tp.blockNum.first << tp.blockNum.second << tp.duration;}

//sf::Packet& operator >>(sf::Packet& packet, TimedPiece& tp){return packet >> tp.blockNum.first >> tp.blockNum.second >> tp.duration;}

#endif