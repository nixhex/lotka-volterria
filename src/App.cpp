#include <vector>
#include "app.hpp"
#include "constants.hpp"
#include "assets/spritesheet_png.hpp"

App::App()
{
    this->window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Lotka-Volterria");
    this->window.setFramerateLimit(144);
    this->assets.requireTextMem("sheet", src_sprites_spritesheet_png, src_sprites_spritesheet_png_len);
    this->fields.push_back(Field(this->settings, this->assets, this->window, 1000, 1000));
}

int App::run()
{
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
        for(Field& field : this->fields) // allow for multiple fields, but can't implement bc no multiple "windows" yet
        {
            for (Creature& creature : field.GetCreatures())
            {
                window.draw(creature.GetSprite());           
            }
        }
        window.display();
    }
    return 0;
}