#include "DatabaseManager.h"
#include "NetworkManager.h"



int main()
{	
	//Test account. If admin/password doesn't work for you then uncomment this and run it once. After you'll be able to acces the game
	//DatabaseManager::getInstance().registerUser("admin", "password");
	NetworkManager postMaster;
	sf::Thread thread(&NetworkManager::checkForConnections, &postMaster);
	thread.launch();

	while (true)
	{
		//Handle what is needed
		/*sf::Packet packet;
		std::string str = "bob";
		packet << str;
		if (!NetworkManager::connectPlayers.empty())
		{
			NetworkManager::connectPlayers.front().playerSocket->send(packet);

		}*/
	}

	return 0;
}