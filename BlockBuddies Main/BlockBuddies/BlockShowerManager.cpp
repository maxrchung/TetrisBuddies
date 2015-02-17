#include "BlockShowerManager.hpp"
#include "GraphicsManager.hpp"

BlockShowerManager* BlockShowerManager::instance;

BlockShowerManager* BlockShowerManager::getInstance()
{
    if(!instance)
        instance = new BlockShowerManager();

    return instance;
}

void BlockShowerManager::init()
{
    fade = Fade((int)(255 * 0.9f));
    fade.state = FadeStates::FADING_IN;
    // Initializes all the meteors to random positions
    meteors = std::vector<BlockMeteor>(30);
    for(int i = 0; i < 30; i++)
    {
        meteors[i] = BlockMeteor();
        reload(meteors[i]);
        meteors[i].boundingRect.setPosition(meteors[i].boundingRect.getPosition().x,
                                            rand() % GraphicsManager::getInstance()->window.getSize().y - meteors[i].boundingRect.getSize().y);
    }
}

void BlockShowerManager::update()
{
    fade.update();

    // No point in updating the meteors if it is not visible
    if(fade.state != FadeStates::FADED_OUT)
    {
        for (auto& meteor : meteors)
        {
            meteor.update();
            meteor.boundingRect.setFillColor(sf::Color(meteor.boundingRect.getFillColor().r,
                                                       meteor.boundingRect.getFillColor().g,
                                                       meteor.boundingRect.getFillColor().b,
                                                       fade.value));

            if (meteor.boundingRect.getGlobalBounds().top - meteor.boundingRect.getSize().y
                    > GraphicsManager::getInstance()->window.getSize().y)
            {
                reload(meteor);
            }
        }
    }
}

void BlockShowerManager::draw()
{
    for(auto meteor : meteors)
        meteor.draw();
}

// When a block goes past the bottom
void BlockShowerManager::reload(BlockMeteor& bm)
{
    // Size: 25 to 125
    float size = rand()%100 + 25;
    bm.boundingRect.setSize(sf::Vector2f(size, size));

    // Speed: 1 to 3
    bm.speed = (rand()%200 + 100)/100.0f;
    // For some reason have to calculate this outside
    int tempValue = GraphicsManager::getInstance()->window.getSize().x - 20.0f - bm.boundingRect.getSize().x;
    bm.boundingRect.setPosition(rand() % tempValue + 10.0f,
                                -bm.boundingRect.getSize().y);

    // Sets a color based on background colors
    // Between .05 and .95
    float colorVariance = (rand()%90 + 5) / 100.0f;
    sf::Color bgColor = GraphicsManager::getInstance()->backgroundColor;
    sf::Color newColor = sf::Color(bgColor.r - colorVariance * 64, 
                                   bgColor.g - colorVariance * 64,
                                   bgColor.b - colorVariance * 64,
                                   fade.value);
    bm.boundingRect.setFillColor(newColor);
}