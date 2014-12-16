#pragma once
#pragma once

#include <string>
#include <vector>
#include <map>
#include <SFML/Audio.hpp>
class SoundManager
{

public:
	//call sound manager just like any other singlton
	static SoundManager& getInstance()
	{
		static SoundManager instance;
		return instance;
	}
	//load the song from a filenam and give it a key to find it by
	void loadSound(std::string,std::string);
	//returns a soundbuffer from the map based on its name, by default there is one sound, "scream"
	sf::SoundBuffer* getSound(std::string);
	// play music
	void playMusic(std::string);
	void stopMusic();
	void setMusicVolume(float);
	void setMusicLoop(bool);
private:
	SoundManager() {
		//load initial sounds
		loadSound("scream", "Sounds/WilhelmScream.wav");
		loadSound("repressed", "Sounds/repressed.wav");
		loadSound("heya", "Sounds/SSBB_Link_Smash_Down.wav");
	}                                  // Private constructor
	~SoundManager();
	SoundManager(const SoundManager&);                 // Prevent copy-construction
	SoundManager& operator=(const SoundManager&);
	//map of sounds
	std::map < std::string, sf::SoundBuffer* > soundMap;
	sf::Music music;
};