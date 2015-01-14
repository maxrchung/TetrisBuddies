#ifndef BLOCKMETEOR_HPP
#define BLOCKMETEOR_HPP

#include "SFML/Graphics.hpp"

// Individual block piece of BlockShower
class BlockMeteor
{
friend class BlockShowerManager;
public:
    BlockMeteor();
    void update();
    void draw();

private:
    sf::RectangleShape boundingRect;

    // How fast the block travels down
    float speed;
};

#endif//BLOCKMETEOR_HPP