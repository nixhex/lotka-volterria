#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

constexpr int sheep_row         = 21;
constexpr int sheep_right_col   = 0;
constexpr int sprite_width      = 16;
constexpr int sprite_height     = 16;

constexpr sf::Vector2i SHEEP_POSE_1{
    sheep_right_col*sprite_width,
    sheep_row*sprite_height
};

constexpr int wolf_row =  24;
constexpr int wolf_col =   0;
constexpr sf::Vector2i WOLF_POSE_1{
    wolf_col*sprite_width,
    wolf_row*sprite_height
};

constexpr sf::Vector2i SPRITE_DIMS{sprite_width, sprite_height};

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Lotka-Volterria");
    window.setFramerateLimit(144);
    //sf::Texture sheep("src/sprites/spritesheet.png", false, sf::IntRect({0,22*16}, {16,16}));
    try {
        //sf::Texture sheep("src/sprites/sheep_white.png");
        sf::Texture sheep("src/sprites/spritesheet.png", false, 
            sf::IntRect(SHEEP_POSE_1, SPRITE_DIMS));
        sf::Sprite sheepSprite(sheep);
        sf::Texture wolf("src/sprites/spritesheet.png", false,
            sf::IntRect(WOLF_POSE_1, SPRITE_DIMS));
        sf::Sprite wolfSprite(wolf);

        sheepSprite.setOrigin({sprite_width/2, sprite_height/2});
        sheepSprite.setPosition({100.f, 100.f});
        sheepSprite.setScale({4.f, 4.f});

        wolfSprite.setOrigin({sprite_width/2, sprite_height/2});
        wolfSprite.setPosition({200.f, 100.f});
        wolfSprite.setScale({-4.f, 4.f});

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
            // draw everything here
            // window.draw(...);

            window.draw(sheepSprite);
            window.draw(wolfSprite);
            window.display();
        }
    } catch (const sf::Exception& e) {
        std::cerr << "SFML error: " << e.what() << "\n"
                  << "Tip: Check working directory and your sub-rect bounds.\n";
        return 1;
    }
}
