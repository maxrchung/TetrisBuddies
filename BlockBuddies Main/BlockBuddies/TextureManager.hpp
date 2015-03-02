#pragma once

#include <SFML\Graphics.hpp>
#include <map>

class TextureManager
{
public:

	static TextureManager& getInstance() {
		static TextureManager instance;
		return instance;
	}
	sf::Texture* getTexture(std::string texturePath);

private:
	TextureManager() {};
	~TextureManager() {};
	TextureManager(const TextureManager&);
	TextureManager& operator =(const TextureManager&);

	std::map<std::string, sf::Texture*> textureMap;
};

inline sf::Texture* _getTexture(std::string path) {
	return TextureManager::getInstance().getTexture(path);
}

