#include "TextureManager.hpp"

sf::Texture* TextureManager::getTexture(std::string texturePath) {
	//do we have it loaded already? if so return a reference
	auto iter = textureMap.begin();
	iter = textureMap.find(texturePath);
	if (iter != textureMap.end()) {
		return iter->second;
	}

	//if not, load the texture, insert it into the map, and return a reference
	sf::Texture* tex = new sf::Texture();
	if (!tex->loadFromFile(texturePath))
		tex->loadFromFile("Textures/filenotfound.png");
	textureMap.insert(std::make_pair(texturePath, tex));

	return tex;
}