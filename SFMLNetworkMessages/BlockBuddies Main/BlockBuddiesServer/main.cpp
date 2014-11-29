/*

To do:

A lot of stuff got changed when I put "private:" back in.
make sure all those issues are ironed out.
Also, there's the matter of the inital game setup stuff.
How does that need to be structured?

Make absolutely sure messages are sent and received properly
Get the game state put into a packet and decoded properly

Test the GameTick() by using the send and receive messages

make sure GameOver is handled appropriately

finish adding score at the end of CheckForMatches









//implement gravity
//get clearing detection working, make sure it updates the scores and the timers correctly
get chaining working 
(maybe make it a loop-
	after a piece is moved
		if the "clear list" isn't empty
			remove the pieces from the board that are on the list
//			perform gravity, add any pieces that moved by falling onto a list
//			check for pieces to clear, add them to the clear list if appropriate
			repeat until clear list is empty
)



*/





#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "ClientMessages.hpp"
#include "GameStateObject.hpp"
#include "ServerMessages.hpp"
#include "GameLogic.hpp"

std::array<int, 7> CreateRow(int c1, int c2, int c3, int c4, int c5, int c6, int c7){
	std::array<int, 7> ret;
	ret[0] = c1;
	ret[1] = c2;
	ret[2] = c3;
	ret[3] = c4;
	ret[4] = c5;
	ret[5] = c6;
	ret[6] = c7;
	return ret;
}

std::array<int, 7> CreateRow(int c){
	std::array<int, 7> ret;

	for (int i = 0; i < 7; i++){
		ret[i] = c;
	}

	return ret;
}


void TestMessages();

void TestInitialBoardCreation(){
	GameLogic gl;
	gl.Print();

	//gl.InitialBoardPopulation();
	gl.Print();
}

void TestRowInsertion(){
	GameLogic gl;
	//gl.InitialBoardPopulation();
	gl.Print();
	//gl.InsertBottomRow();
	//gl.gso.Print();
	gl.PrintBTCFM();
	//gl.ProcessBTCFM();

	
	//gl.InsertBottomRow();
	//gl.InsertBottomRow();
	//gl.InsertBottomRow();
	//gl.InsertBottomRow();
	gl.Print();
	


}

/*
void TestSwap(){
	GameLogic gl;


	gl.InsertRowAt(0, CreateRow(1, 1, 1, 1, 1, 0, 1));
	gl.InsertRowAt(1, CreateRow(2, 2, 2, 2, 2, 0, 2));
	gl.InsertRowAt(2, CreateRow(3, 3, 3, 4, 4, 0, 3));

	//swap l/r
	gl.gso.Print();
	gl.SwapPieces(2, 2, 2, 3);
	gl.gso.Print();
	//swap u/d
	gl.SwapPieces(1, 2, 2, 2);
	gl.gso.Print();

	//swap l/r with gravity
	gl.SwapPieces(2, 4, 2, 5);
	gl.gso.Print();

	//swap u/d with gravity
	gl.SwapPieces(2, 0, 3, 0);
	gl.gso.Print();
}
*/

void TestGameTick(){

	//write a loop (while not game over) that takes input and turns it into packets
	//pass the packets to receiveMessage
	//run the game tick
	//


	//test against a local GSO.  That's the whole point.

}

void main(){
	
	//TestInitialBoardCreation();
	//TestRowInsertion();
	//TestSwap();
	TestMessages();
	

	std::cin.get();
}


/*
int main(){



	GameLogic gl;
	gl.gso.Print();

	sf::Clock clock;

	gl.InsertRowAt(2, CreateRow(1, 1, 1, 2, 1, 1));
	//gl.gso.Print();
	

	gl.InsertRowAt(5, CreateRow(1, 2, 2, 2, 2, 2));
	gl.InsertRowAt(8, CreateRow(1, 3, 0, 3, 0, 0));
	
	//gl.gso.Print();

	//gl.InsertBottomRow();
	//gl.InsertBottomRow();


	//gl.ApplyGravity();
	
	gl.InsertRowAt(11, CreateRow(4, 4, 4, 4, 4, 4));
	//gl.gso.Print();
	gl.ApplyGravity();
	gl.SwapPieces(1, 0, 2, 0); 
	gl.SwapPieces(1, 1, 2, 1);
	gl.SwapPieces(2, 2, 1, 2);
	gl.SwapPieces(1, 2, 1, 3);

	//gl.InsertRowAt(11, CreateRow(4, 4, 4, 2, 2, 2));

	//gl.ApplyGravity();


	//gl.CheckForMatches(0, 1);
	//gl.PrintBlocksMarkedForDeletion();

	//gl.InitialBoardPopulation();
	gl.InsertRowAt(4, CreateRow(1, 3, 0, 3, 0, 0));
	gl.InsertRowAt(5, CreateRow(1, 3, 0, 3, 0, 0));
	gl.gso.Print();
	gl.SwapPieces(5, 0, 6, 0);
	gl.gso.Print();
	gl.ApplyGravity();
	gl.gso.Print();

	
	sf::Time sleepTime = clock.restart();
	sf::sleep(sleepTime);
	std::cout << "Slept for " << sleepTime.asMilliseconds() << std::endl;
	



	std::cin.get();
}


*/

void TestMessages()
{

	//sf::Clock clock;

	sf::TcpListener listener;
	sf::TcpSocket serverSocket;
	sf::TcpSocket clientSocket;
	GameLogic gl;
	GameStateObject clientGS;
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



	//send game state from server to client
	receivedData.clear();

	gl.InsertRowAt(0, CreateRow(6));
	gl.InsertRowAt(1, CreateRow(1));
	gl.InsertRowAt(2, CreateRow(2));
	gl.InsertRowAt(3, CreateRow(3));
	gl.InsertRowAt(4, CreateRow(4));
	gl.InsertRowAt(5, CreateRow(5));
	gl.InsertRowAt(6, CreateRow(4));
	gl.PopulateTempRow();

	serverSocket.send(sm.GameStatePacket(gl));
	clientSocket.receive(receivedData);
	cm.ProcessMessage(receivedData, clientGS);
	


	std::cout << "\nServerGS: " << std::endl;
	gl.Print();

	std::cout << "\nClient GS:" << std::endl;
	clientGS.Print();



	//here, testing that all the client messages are sent properly and
	//understood by the server

	/*
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



	//gso.Print();






	//here, testing that all the server messages are sent
	//properly and understood by the client

	//send "start game command" from server to client
	//receivedData.clear();
	//serverSocket.send(sm.StartPacket(gl));
//	clientSocket.receive(receivedData);
	//cm.ProcessMessage(receivedData, clientGS);

	/*
	//send "game over command" from server to client
	receivedData.clear();
	serverSocket.send(sm.GameOverPacket());
	clientSocket.receive(receivedData);
	cm.ProcessMessage(receivedData);
	//send "temp row contents" from server to client
	//receivedData.clear();

	//clientSocket.receive(receivedData);
	//cm.ProcessMessage(receivedData);


	*/

}

