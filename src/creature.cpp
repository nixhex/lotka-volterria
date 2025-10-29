#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "assets/spritesheet_png.hpp"
#include "creature.hpp"
#include "field.hpp"
#include "constants.hpp"
#include "AssetManager.hpp"
#include "settings.hpp"
#include "framerect.hpp"

Creature::Creature(const Settings& settings, const sf::Texture& sheet, SpeciesRole role, Direction dir, Face face,
        sf::Vector2f field_position, 
        sf::Vector2f scale,
        int frame) : settings_(settings), sprite_(sheet, frameRect(settings, role, dir, frame)), 
        role_(role), face_(face), direction_(dir), frame_(frame % 3), field_position_(field_position)
{
    this->species_ = (role == SpeciesRole::Prey) ? this->settings_.prey_name : this->settings_.predator_name;
    this->SetSpriteScale({((float)this->face_)*static_cast<float>(scale.x), static_cast<float>(scale.y)});
    this->SetSpriteOrigin({static_cast<float>(this->settings_.sprite_width/2), static_cast<float>(this->settings_.sprite_height/2)});
    //this->SetFieldPosition({static_cast<float>(field_position.x), static_cast<float>(field_position.y)});
    this->SetFieldPosition(field_position);
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
    return this->hunger_;
}

float Creature::Libido()
{
    return this->libido_;
}

std::array<float, 2> Creature::Velocity()
{
    return this->velocity_; // default
}

float Creature::Speed()
{
    return (float) std::sqrtf(std::powf(this->velocity_[0], 2) + std::powf(this->velocity_[1], 2));
}

std::array<float, 2> Creature::Position()
{
    return this->position_; // default 
}

std::time_t Creature::TimeBorn()
{
    return this->timeborn_;
}

std::time_t Creature::Age()
{
    return this->age_;
}

float Creature::Distance(Creature c1, Creature c2)
{
    return std::sqrtf(std::powf(c1.Position()[0] - c2.Position()[0], 2) 
                    + std::powf(c1.Position()[1] - c2.Position()[1], 2));
}

void Creature::update(float dt)
{
    std::cout << "updating with time dt: " << dt << std::endl;
}

sf::Sprite& Creature::GetSprite()
{
    return this->sprite_;
}

void Creature::SetSpriteOrigin(sf::Vector2f origin)
{
    //this->sprite_.setOrigin({static_cast<float>(origin.x), static_cast<float>(origin.y)});
    this->sprite_.setOrigin(origin);
}

void Creature::SetSpritePosition(sf::Vector2f position)
{
//    this->sprite_.setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
    this->sprite_.setPosition(position);
}

void Creature::SetSpriteScale(sf::Vector2f scale)
{
    // this->sprite_.setScale({static_cast<float>(scale.x), static_cast<float>(scale.y)});
    this->sprite_.setScale(scale);
}

void Creature::SetFieldPosition(sf::Vector2f position)
{
    this->field_position_ = position;
    sf::Vector2f adjusted_position = Field::FieldToScreenTX(position, this->settings_.screen_extrema, this->settings_.field_extrema);
    SetSpritePosition(adjusted_position);
}