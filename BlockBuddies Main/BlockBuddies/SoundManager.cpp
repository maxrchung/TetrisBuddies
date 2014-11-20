#include "SoundManager.h"
#include <iostream>

SoundManager::~SoundManager()
{
}
//sound is loaded into the buffer, if the filename is not found prints out, can be changed into a error later.
void SoundManager::loadSound(std::string songName, std::string fileName)
{
	//create a new soundbuffer;
	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	//load the file
	if (buffer->loadFromFile(fileName))
	{
		//insert into the map
		soundMap.insert(std::pair<std::string, sf::SoundBuffer*>(songName, buffer));
	}
	else
	{
		std::cout << "Sound Not Loaded \n";
	}
}
//return the sound buffer
sf::SoundBuffer* SoundManager::getSound(std::string songName)
{
	sf::SoundBuffer* buff =  soundMap.at(songName);
	return buff;
}