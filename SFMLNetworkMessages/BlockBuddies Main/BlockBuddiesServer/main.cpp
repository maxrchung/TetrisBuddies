/*

To do:

make a new main function that tests out all the game logic stuff so far
(might have to temporarily make all the functions public to test them individually)


implement gravity
get clearing detection working, make sure it updates the scores and the timers correctly
get chaining working 
(maybe make it a loop-
	after a piece is moved
		if the "clear list" isn't empty
			remove the pieces from the board that are on the list
			perform gravity, add any pieces that moved by falling onto a list
			check for pieces to clear, add them to the clear list if appropriate
			repeat until clear list is empty
)

test that the game works in the loop as it should

*/





#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "ClientMessages.hpp"
#include "GameStateObject.hpp"
#include "ServerMessages.hpp"



int main(){

}

/*
int main()
{

	sf::Clock clock;

	sf::TcpListener listener;
	sf::TcpSocket serverSocket;
	sf::TcpSocket clientSocket;
	GameStateObject gso;
	ClientMessages cm;
	ServerMessages sm;


	//create a server listening for a client connection at port 3014
	//create a client connection at port 5000 and establish a connection
	listener.listen(3014);
	clientSocket.connect("127.0.0.1", 3014);

	listener.accept(serverSocket);
	//std::cout << "Client connected to server on: " << onServer.getRemoteAddress() << ", port " << onServer.getRemotePort() << std::endl;
	//std::cout << "Server connected to client on: " << onClient.getRemoteAddress() << ", port " << onClient.getRemotePort() << std::endl;

	sf::Packet receivedData;

	/*

	//here, testing that all the client messages are sent properly and
	//understood by the server


	//send "new row request" from client to server
	receivedData.clear();
	clientSocket.send(cm.NewRowPacket());
	serverSocket.receive(receivedData);
	//std::cout << "Size of 'received data' " << receivedData.getDataSize() << std::endl;
	sm.ProcessMessage(receivedData);

	//send "start game request" from client to server"
	receivedData.clear();
	clientSocket.send(cm.StartPacket());
	serverSocket.receive(receivedData);
	sm.ProcessMessage(receivedData);

	//send "swap piece request" from client to server
	receivedData.clear();
	clientSocket.send(cm.SwapPacket(2, 5, 3, 5));
	serverSocket.receive(receivedData);
	sm.ProcessMessage(receivedData);
	*/



	/*
	//here, testing that the game board is created properly:
	//(gameBoard is back to being private, so this won't work any more)
	for (int rowNum = 0; rowNum < 12; rowNum++){
	for (int colNum = 0; colNum < 6; colNum++){
	gso.gameBoard[rowNum][colNum] = rowNum + colNum;
	}
	}
	*/
	//gso.Print();






	//here, testing that all the server messages are sent
	//properly and understood by the client

	//send "start game command" from server to client
	receivedData.clear();
	serverSocket.send(sm.StartPacket());
	clientSocket.receive(receivedData);
	cm.ProcessMessage(receivedData);

	//send "game over command" from server to client
	receivedData.clear();
	serverSocket.send(sm.GameOverPacket());
	clientSocket.receive(receivedData);
	cm.ProcessMessage(receivedData);
	//send "temp row contents" from server to client
	//receivedData.clear();

	//clientSocket.receive(receivedData);
	//cm.ProcessMessage(receivedData);

	//send game state from server to client
	receivedData.clear();
	serverSocket.send(sm.GameStatePacket(gso));
	clientSocket.receive(receivedData);
	cm.ProcessMessage(receivedData);



	int i = 0;
	while (i < 30){
	sf::Time sleepTime = sf::milliseconds(16) - clock.restart();
	sf::sleep(sleepTime);
	std::cout << "Slept for " << sleepTime.asMilliseconds() << std::endl;
	i++;
	}

	std::cin.get();
}

*/