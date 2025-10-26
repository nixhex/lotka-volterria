#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <ctime>
#include <random>
#include "assets/spritesheet_png.hpp"
#include "creature.hpp"
#include "field.hpp"
#include "constants.hpp"

Creature::Creature(const sf::Sprite& sprite, 
    std::string_view species, std::string_view sound) : // initializer list
    sprite_(sprite), species_(species), sound_(sound) // makes copies of these values
{
    
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