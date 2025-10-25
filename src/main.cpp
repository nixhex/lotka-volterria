#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "creatures.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Lotka-Volterria");
    window.setFramerateLimit(144);
    try {
        std::vector<sf::Sprite> sprites;
        Field field(sprites, window, 250, 250); // populate sprites vector
        std::cout << "sprites.size() = " << sprites.size() << std::endl;
        
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
            // loop through sprites vector and draw them
            for (const sf::Sprite sprite : sprites) {
                window.draw(sprite);
            }
            window.display();
        }
    } catch (const sf::Exception& e) {
        std::cerr << "SFML error: " << e.what() << "\n"
                  << "Tip: Check working directory and your sub-rect bounds.\n";
        return 1;
    }
}
