#include "DatabaseManager.h"
#include "NetworkManager.h"



int main()
{	
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