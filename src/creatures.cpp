#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <ctime>
#include <random>
#include "assets/spritesheet_png.hpp"
#include "creatures.hpp"

Creature::Creature(const sf::Sprite& sprite, 
    std::string_view species, std::string_view sound) : // initializer list
    sprite_(sprite), species_(species), sound_(sound) // makes copies of these values
{
    // this->species = std::string(species);
    // this->sound = std::string(sound);
    // this->sprite = sprite;
}

std::string Creature::Species()
{
    return this->species_;
}

void Creature::Eat()
{

}

void Creature::Move()
{

}

void Creature::Sound()
{
    std::cout << this->sound_ << "\n";
}

void Creature::Sleep()
{

}

bool Creature::MateWith(Creature)
{

    return false;
}

float Creature::Hunger()
{
    return this->hunger;
}

float Creature::Libido()
{
    return this->hunger;
}

std::array<float, 2> Creature::Velocity()
{
    return this->velocity; // default
}

float Creature::Speed()
{
    return (float) std::sqrtf(std::powf(this->velocity[0], 2) + std::powf(this->velocity[1], 2));
}

std::array<float, 2> Creature::Position()
{
    return this->position; // default 
}

std::time_t Creature::TimeBorn()
{
    return this->timeborn;
}

std::time_t Creature::Age()
{
    return this->age;
}

float Creature::Distance(Creature c1, Creature c2)
{
    return std::sqrtf(std::powf(c1.Position()[0] - c2.Position()[0], 2) 
                    + std::powf(c1.Position()[1] - c2.Position()[1], 2));
}

sf::Sprite& Creature::GetSprite()
{
    return this->sprite_;
}

void Creature::SetSpriteOrigin(sf::Vector2f origin)
{
    this->sprite_.setOrigin({static_cast<float>(origin.x), static_cast<float>(origin.y)});
}

void Creature::SetSpritePosition(sf::Vector2f position)
{
    this->sprite_.setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
}

void Creature::SetSpriteScale(sf::Vector2f scale)
{
    this->sprite_.setScale({static_cast<float>(scale.x), static_cast<float>(scale.y)});
}

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
    
    //this->creatures.at(0).Sound();
    this->creatures.at(0).SetSpriteOrigin({sprite_width/2, sprite_height/2});
    this->creatures.at(0).SetSpritePosition({100, 100});
    this->creatures.at(0).SetSpriteScale({4.f, 4.f});

    //this->creatures.at(1).Sound();
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