#ifndef BLOCKSHOWER_HPP
#define BLOCKSHOWER_HPP

#include "BlockMeteor.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "Fade.hpp"

// Background block shower that falls down behind menus
class BlockShowerManager
{
public:
    static BlockShowerManager* getInstance();
    void init();
    void update();
    void draw();
    void reload(BlockMeteor&);
    Fade fade;

private:
    std::vector<BlockMeteor> meteors;
    BlockShowerManager(){};
    BlockShowerManager(BlockShowerManager const&){};
    BlockShowerManager& operator=(BlockShowerManager const&){};

    static BlockShowerManager* instance;
};

#endif//BLOCKSHOWER_HPP