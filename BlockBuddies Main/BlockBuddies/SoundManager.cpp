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

void SoundManager::playMusic(std::string songName, bool loop)
{
	if (music.getStatus() != music.Playing)
	{
		if (music.openFromFile(songName))
		{
			music.play();
		}
		else
		{
			std::cout << "song not found" << std::endl;
		}
	}
	else
	{
		music.stop();
		if (music.openFromFile(songName))
		{
			music.play();
		}
		else
		{
			std::cout << "song not found" << std::endl;
		}
	}

	music.setLoop(loop);
}

void SoundManager::playMusicRandom()
{
	music.setLoop(false);
	//if no songs in the list don't play anything
	if (songList.empty())
	{
		return;
	}
	std::srand(time(NULL));
	std::string nextSong;

	nextSong = songList[rand() % songList.size()];
	
	if (music.getStatus() == music.Playing)
	{
		music.stop();
	}

	if (music.openFromFile(nextSong))
	{
		music.play();
	}
	else
	{
		std::cout << "song not found" << std::endl;
	}
	
}
void SoundManager::stopMusic()
{
	music.stop();
}
void SoundManager::setMusicVolume(float volume)
{
	music.setVolume(volume);
}
void SoundManager::setMusicLoop(bool loop)
{
	music.setLoop(loop);
}

void SoundManager::addToSongList(std::string songPath)
{
	songList.push_back(songPath);
}