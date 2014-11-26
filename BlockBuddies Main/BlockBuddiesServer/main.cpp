#include "DatabaseManager.h"
#include "NetworkManager.h"
#include <windows.h>


int main()
{	
	NetworkManager postMaster;
	sf::Thread thread(&NetworkManager::checkForConnections, &postMaster);
	thread.launch();

	while (true)
	{
		//Handle what is needed
	}

	return 0;
}