#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

int main()
{
/*
    sf::RenderWindow window;
    window.create(sf::VideoMode::getDesktopMode(),
                  "Text test");

    sf::Font font;
    font.loadFromFile("Roboto-Regular.ttf");

    std::vector<sf::Text> sampleTexts;
    
    for(int i = 1; i < 11; i++)
    {
        sf::Text sample("Currently playing in offline mode, please login to track your stats",
                        font,
                        16);
        sample.setPosition(0, 60*i);
        sample.setColor(sf::Color::White);
        sampleTexts.push_back(sample);
    }

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        for(auto& text : sampleTexts)
            window.draw(text);
        
        window.display();
    }
*/

	Game game;

	while (game.isRunning)
		// Lets Game handle everything
		game.run();

	return 0;
}