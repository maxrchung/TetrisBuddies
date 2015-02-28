#ifndef MESSAGETYPE_HPP
#define MESSAGETYPE_HPP

enum PacketDecode
{
	//0
	PACKET_LOGIN,
	//1
	PACKET_REGISTER,
	//2
	PACKET_START,
	//3
	PACKET_GAMESTATE,
	//4
	PACKET_SWAP,
	//5
	PACKET_REQUESTNEWROW,
	//6
	PACKET_SCOREUPDATE,
	//7
	PACKET_GAMEOVER,
    //8
    PACKET_DISCONNECT,
    //9
    PACKET_CHECKALIVE,
	//10
	PACKET_USERINFOUPDATE,
	//11
	PACKET_MULTIPLAYERQUEUE,
	//12
	PACKET_MATCHFOUND,
	//13
	PACKET_CLEAR,
	//14
	PACKET_DROP,
    //15
    PACKET_JOINQUEUE,
    //16
    PACKET_LEAVEQUEUE,
    //17
    PACKET_FOUNDGAME, // Server tells Client that game has been found
	//18
	PACKET_WINNER,
	//19
	PACKET_NEWPENALTYROW

};

#endif