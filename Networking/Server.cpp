#include "serverManager.h"

sf::TcpListener listener;
sf::TcpSocket server;

bool initConnection(int port)
{
	if (listener.listen(port) != sf::Socket::Done)
	{
		std::cout << "Error: Port listening";
		return false;
	}
	else
		return true;
	
}


bool connectClient()
{
	if (listener.accept(server) != sf::Socket::Done)
	{
		std::cout << "Error: Client connection";
		return false;
	}
	else return true;
	
}

void recieveMessage()
{
	char data[100];
	std::size_t received;

	if (server.receive(data, 100, received) != sf::Socket::Done)
	{
		std::cout << "Message was lost! \n";
	}

	std::cout << "Received " << received << " bytes The message reads: " << data << std::endl;
}

std::string sendMessage(char *toSend)
{
	char data[100] = "";
	std::string temp = toSend;

	strcpy_s(data, temp.c_str());;

	if (server.send(data, 100) != sf::Socket::Done)
	{
		std::cout << "Error: Message not sent\n";
		return "False";
	}

	return " ";

}


void sendPlayer(std::string name, int playerID, int rank)
{
	sf::Packet packet;
	packet << name << playerID << rank;
	server.send(packet);
}

void terminateConnection()
{
	server.disconnect();
}




	//Works but isn't the safest/best way
	//std::string message = "Welcome, client \n";
	//client.send(message.c_str(), message.size() + 1);
