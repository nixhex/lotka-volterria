#include <SFML/Graphics.hpp>
#include "field.hpp"
#include "assets/spritesheet_png.hpp"

Field::Field(sf::RenderWindow& window, int numPrey, int numPred)
{
    std::cout << "field initiated" << std::endl;
    auto window_dimensions = window.getSize();
    unsigned width =  window_dimensions.x;
    unsigned height = window_dimensions.y;
    //this->preyTexture.setSmooth(true);
    //this->predatorTexture.setSmooth(true);
    if(!this->preyTexture.loadFromMemory(src_sprites_spritesheet_png,
        src_sprites_spritesheet_png_len, false,
        sf::IntRect(PREY_POSE_1, SPRITE_DIMS))) std::cout << "prey texture not loaded" << std::endl;
    Creature creature1(sf::Sprite(this->preyTexture), prey_name, prey_sound);
    this->creatures.push_back(creature1);

    if(!this->predatorTexture.loadFromMemory(src_sprites_spritesheet_png,
        src_sprites_spritesheet_png_len, false,
        sf::IntRect(PREDATOR_POSE_1, SPRITE_DIMS))) std::cout << "predator texture not loaded" << std::endl;
    Creature creature2(sf::Sprite(this->predatorTexture), predator_name, predator_sound);
    this->creatures.push_back(creature2);
    
    this->creatures.at(0).SetSpriteOrigin({sprite_width/2, sprite_height/2});
    this->creatures.at(0).SetSpritePosition({100, 100});
    this->creatures.at(0).SetSpriteScale({4.f, 4.f});

    this->creatures.at(1).SetSpriteOrigin({sprite_width/2, sprite_height/2});
    this->creatures.at(1).SetSpritePosition({200, 100});
    this->creatures.at(1).SetSpriteScale({-4.f, 4.f});
}

std::vector<Creature>& Field::GetCreatures()
{
    return this->creatures;
}

const Creature& Field::GetCreature(int index)
{
    return this->creatures.at(index);
}