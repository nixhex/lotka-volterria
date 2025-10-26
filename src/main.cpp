#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "creature.hpp"
#include "field.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Lotka-Volterria");
    window.setFramerateLimit(144);
    try {
        std::vector<sf::Sprite> sprites;
        Field field(window, 250, 250); // populate field
        
        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }

            window.clear();
            for (Creature& creature : field.GetCreatures())
            {
                window.draw(creature.GetSprite());           
            }

            window.display();
        }
    } catch (const sf::Exception& e) {
        std::cerr << "SFML error: " << e.what() << "\n"
                  << "Tip: Check working directory and your sub-rect bounds.\n";
        return 1;
    }
}
