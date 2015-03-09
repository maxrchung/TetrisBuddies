#pragma once
#pragma once

#include <string>
#include <vector>
#include <map>
#include <SFML/Audio.hpp>
#include <random>
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
	// play music set to loop by default
	void playMusic(std::string, bool = true);
	void playMusicRandom();
	void stopMusic();
	void setMusicVolume(float);
	void setMusicLoop(bool);
	void addToSongList(std::string songPath);
	sf::Music music;
private:
	SoundManager() {
		//load initial sounds
		loadSound("scream", "Sounds/WilhelmScream.wav");
		loadSound("repressed", "Sounds/repressed.wav");
		loadSound("heya", "Sounds/SSBB_Link_Smash_Down.wav");
		loadSound("blast", "Sounds/blast.wav");
		loadSound("charge", "Sounds/TrimmedCharge.ogg");

		addToSongList("Sounds/Slamtris.ogg");
		addToSongList("Sounds/HardCoreTetris.ogg");
		addToSongList("Sounds/01 Tetris (Themes B And C).ogg");
	}                                  // Private constructor
	~SoundManager();
	SoundManager(const SoundManager&);                 // Prevent copy-construction
	SoundManager& operator=(const SoundManager&);
	//map of sounds
	std::map < std::string, sf::SoundBuffer* > soundMap;
	std::vector<std::string> songList;
	bool rStarted;
};