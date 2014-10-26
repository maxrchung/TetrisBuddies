#include "Client.h"

sf::TcpSocket socket;

bool initConnection(sf::IpAddress IP, int portNumber)
{
	sf::Socket::Status status = socket.connect(sf::IpAddress::getLocalAddress(), portNumber);
	if (status != sf::Socket::Done)
	{
		std::cout << "Can't Connect!";
		return false;
	}
	else return true;
};



 std::string sendMessage(std::string toSend)
{
	char data[100] = "";
	std::string temp = toSend;

	strcpy_s(data, temp.c_str());;

	if (socket.send(data, 100) != sf::Socket::Done)
	{
		std::cout << "Error: Message not sent\n";
		return "False";
	}

	return " ";


}

void recieveMessage()
{
	char data[100];
	std::size_t received;

	if (socket.receive(data, 100, received) != sf::Socket::Done)
	{
		std::cout << "Message was lost! \n";
	}

	std::cout << "Received " << received << " bytes The message reads: " << data << std::endl;
}


void createUser()
{
	sf::Packet playerInfo;
	socket.receive(playerInfo);

	//insert code to creat a new object here


}


