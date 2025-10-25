#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "creatures.hpp"
//#include "assets/spritesheet_png.hpp"

// constexpr int sheep_row         = 21;
// constexpr int sheep_col         = 0;
// constexpr int sprite_width      = 16;
// constexpr int sprite_height     = 16;

// constexpr sf::Vector2i SHEEP_POSE_1 {
//     sheep_col*sprite_width,
//     sheep_row*sprite_height
// };

// constexpr int wolf_row =  24;
// constexpr int wolf_col =   8;
// constexpr sf::Vector2i WOLF_POSE_1 {
//     wolf_col*sprite_width,
//     wolf_row*sprite_height
// };

// constexpr sf::Vector2i SPRITE_DIMS{sprite_width, sprite_height};

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Lotka-Volterria");
    window.setFramerateLimit(144);
    try {
        sf::Texture sheep, wolf;
        std::vector<sf::Sprite> sprites;
        Field field(&sprites, &window, 250, 250);
        std::cout << "sprites.size() = " << sprites.size() << std::endl;
        // load sprites from src_sprites_spritesheet_png,
        // generated w/ cmd: xxd -i src\sprites\spritesheet.png 
        // | Out-File -Encoding ascii -NoNewline src\assets\spritesheet_png.hpp 
        // if(!sheep.loadFromMemory(src_sprites_spritesheet_png,
        //     src_sprites_spritesheet_png_len, false,
        //     sf::IntRect(SHEEP_POSE_1, SPRITE_DIMS))) return 1;
        // sf::Sprite sheepSprite(sheep);
        
        // if(!wolf.loadFromMemory(src_sprites_spritesheet_png,
        //     src_sprites_spritesheet_png_len, false,
        //     sf::IntRect(WOLF_POSE_1, SPRITE_DIMS))) return 1;
        // sf::Sprite wolfSprite(wolf);
        // sprites.push_back(sheepSprite);
        // sprites.push_back(wolfSprite);

        // sprites.at(0).setOrigin({sprite_width/2, sprite_height/2});
        // sprites.at(0).setPosition({100.f, 100.f});
        // sprites.at(0).setScale({4.f, 4.f});

        // sprites.at(1).setOrigin({sprite_width/2, sprite_height/2});
        // sprites.at(1).setPosition({200.f, 100.f});
        // sprites.at(1).setScale({-4.f, 4.f});

        //wolfSprite.rotate(sf::degrees(180));
        
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
            for (sf::Sprite sprite : sprites) {
                std::cout << "drawing a sprite" << std::endl;
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
