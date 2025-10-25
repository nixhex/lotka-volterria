#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <ctime>
#include <random>
#include "assets/spritesheet_png.hpp"
#include "creatures.hpp"

Creature::Creature()
{

}

std::string Creature::Species()
{
    return this->species;
}

void Creature::Eat()
{

}

void Creature::Move()
{

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

Field::Field(std::vector<sf::Sprite>& sprites, sf::RenderWindow& window, int numPrey, int numPred)
{
    auto window_dimensions = window.getSize();
    unsigned width =  window_dimensions.x;
    unsigned height = window_dimensions.y;
    preyTexture.loadFromMemory(src_sprites_spritesheet_png,
        src_sprites_spritesheet_png_len, false,
        sf::IntRect(PREY_POSE_1, SPRITE_DIMS));
    sf::Sprite preySprite(preyTexture);
    
    predatorTexture.loadFromMemory(src_sprites_spritesheet_png,
        src_sprites_spritesheet_png_len, false,
        sf::IntRect(PREDATOR_POSE_1, SPRITE_DIMS));
    sf::Sprite predatorSprite(predatorTexture);
    sprites.push_back(preySprite);
    sprites.push_back(predatorSprite);

    sprites.at(0).setOrigin({sprite_width/2, sprite_height/2});
    sprites.at(0).setPosition({100.f, 100.f});
    sprites.at(0).setScale({4.f, 4.f});

    sprites.at(1).setOrigin({sprite_width/2, sprite_height/2});
    sprites.at(1).setPosition({200.f, 100.f});
    sprites.at(1).setScale({-4.f, 4.f});
}