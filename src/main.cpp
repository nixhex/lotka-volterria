#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "creature.hpp"
#include "field.hpp"
#include "AssetManager.hpp"
#include "assets/spritesheet_png.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Lotka-Volterria");
    AssetManager assets;
    // add spritesheet from memory to asset manager
    assets.requireTextMem("sheet", src_sprites_spritesheet_png, src_sprites_spritesheet_png_len);
    window.setFramerateLimit(144);
    try {
        std::vector<sf::Sprite> sprites;
        Field field(assets, window, 250, 250); // create a field - pass it the asset manager and window for max information
        
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
