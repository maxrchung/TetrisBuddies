/*

To do:

***debug the CheckForMatches- matches keep getting missed





A lot of stuff got changed when I put "private:" back in.
make sure all those issues are ironed out.
Also, there's the matter of the inital game setup stuff.
How does that need to be structured?


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


void TestMatch3(){
	
	//testing horizontal match here:
	//this horizontal test passed
	/*
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(1, 1, 2, 1, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(3, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(0, 2, 0, 3);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//testing vertical match here:
	//this vertical test passed:
	/*
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(1, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(1, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(1, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(2, 0, 3, 0);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//this test passed
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(2, 3, 2, 3, 2, 3, 1));
	gl.InsertRowAt(1, CreateRow(3, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 2, 3, 2, 3, 1));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 2, 3, 2, 1));

	gl.SwapPieces(0, 6, 1, 6);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();

}

void TestMatch4(){


	//testing horizontal here:
	//this passes. It clears the 4 and the 3 above it
	/*
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(1, 1, 2, 1, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(3, 2, 1, 2, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 3, 2, 3, 2));

	gl.SwapPieces(0, 2, 1, 2);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//this test passed
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(1, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(3, 1, 3, 2, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(1, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(1, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 3, 2, 3, 2));

	gl.SwapPieces(1, 0, 1, 1);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();

}

void TestMatch5(){

	//testing horizontal here:
	/* this test passed
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(1, 1, 2, 1, 1, 3, 2));
	gl.InsertRowAt(1, CreateRow(3, 2, 1, 2, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 3, 2, 3, 2));

	gl.SwapPieces(0, 2, 1, 2);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//testing vertical here:
	//this test passed
	/*
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(1, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(1, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 1, 2, 3, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(1, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(1, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(5, CreateRow(3, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(2, 0, 2, 1);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//testing L up-right here:
	//this test passed:
	/*
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(1, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(1, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 1, 1, 3, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(1, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(5, CreateRow(3, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(2, 0, 3, 0);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//testing L up-left here:
	//this test passed
	/*
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(2, 3, 2, 1, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(3, 2, 3, 1, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 1, 1, 3, 1, 3, 2));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(5, CreateRow(3, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(2, 3, 2, 4);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//testing L down-left here:
	//this passed
	/*
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(2, 1, 1, 3, 1, 3, 2));
	gl.InsertRowAt(1, CreateRow(3, 2, 3, 1, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 2, 1, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(5, CreateRow(3, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(0, 3, 0, 4);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//testing L down-right here:
	//thsi test passed
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(2, 3, 1, 3, 1, 1, 2));
	gl.InsertRowAt(1, CreateRow(3, 2, 3, 1, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 2, 1, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 2, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(5, CreateRow(3, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(0, 2, 0, 3);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
}

void TestMatch7(){
	//testing 5 horizontal 3 vertical here
	//this passed
	/*
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(2, 3, 2, 1, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(3, 1, 1, 2, 1, 1, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 2, 1, 2, 3, 2));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 1, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 3, 2, 3, 2));
	gl.InsertRowAt(5, CreateRow(3, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(0, 3, 1, 3);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
	*/

	//testing 3 horizontal 5 vertical here
	GameLogic gl;
	gl.InsertRowAt(0, CreateRow(2, 3, 2, 1, 2, 3, 2));
	gl.InsertRowAt(1, CreateRow(3, 2, 3, 1, 3, 2, 3));
	gl.InsertRowAt(2, CreateRow(2, 3, 1, 3, 1, 1, 2));
	gl.InsertRowAt(3, CreateRow(3, 2, 3, 1, 3, 2, 3));
	gl.InsertRowAt(4, CreateRow(2, 3, 2, 1, 2, 3, 2));
	gl.InsertRowAt(5, CreateRow(3, 2, 3, 2, 3, 2, 3));

	gl.SwapPieces(2, 2, 2, 3);

	gl.Print();
	gl.PrintBTCFM();
	gl.ProcessBTCFM();
	gl.PrintBlocksMarkedForDeletion();
	gl.ClearMatches();
	gl.Print();
}


void TestGameTickNoSocket(){

	GameLogic gl;
	GameStateObject clientGS;
	ClientMessages cm;
	ServerMessages sm;
	sf::Packet receivedData;

	int command = -1;


	receivedData.clear();

	//loop here:
	//write a loop (while not game over) that takes input and turns it into packets
	//pass the packets to receiveMessage
	//run the game tick


	gl.ReceiveMessage(cm.StartPacket());
	//test against clientGS (a local GSO).  That's the whole point.
	do{

		gl.GameTick();


		while (!gl.outgoingMessages.empty()){
			cm.ProcessMessage(gl.outgoingMessages.front(), clientGS);
			gl.outgoingMessages.pop();
		}

		clientGS.Print();


		std::cout << "\nEnter Command Number: (1-start 2-swap 3-new row 4-quit)";
		std::cin >> command;

		if (command == 1){
			gl.ReceiveMessage(cm.StartPacket());
		}

		else if (command == 2){

			int r1, c1, r2, c2;

			std::cout << "Which pieces do you want to swap?\n";
			std::cin >> r1 >> c1 >> r2 >> c2;

			gl.ReceiveMessage(cm.SwapPacket(r1, c1, r2, c2));
		}

		else if (command == 3){
			gl.ReceiveMessage(cm.NewRowPacket());
		}

		else if (command == 4)
		{
			return;
		}




	} while (!gl.IsGameOver());

}

void TestGameTickWithSocket(){
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
}

void main(){
	
	//TestInitialBoardCreation();
	//TestRowInsertion();
	//TestSwap();
	//TestMessages();
	
	//TestGameTickNoSocket();

	//TestMatch4();
	TestMatch7();

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
	//gl.PopulateTempRow();

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

