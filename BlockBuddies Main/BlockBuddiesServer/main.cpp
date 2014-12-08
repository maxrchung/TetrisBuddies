#include "NetworkManager.h"
#include <windows.h>
#include <thread>


int main()
{	
    NetworkManager::getInstance()->init();

	while(NetworkManager::getInstance()->running)
	{
		//Handle what is needed
        NetworkManager::getInstance()->update();
	}

	return 0;
}