#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>
#include "assets/spritesheet_png.hpp"
#include "creature.hpp"
#include "field.hpp"
#include "constants.hpp"
#include "AssetManager.hpp"
#include "settings.hpp"
#include "framerect.hpp"

Creature::Creature(const Settings& settings, const sf::Texture& sheet, SpeciesRole role,
        sf::Vector2f initial_position,
        sf::Vector2f initial_velocity, 
        sf::Vector2f scale) : settings_(settings), sprite_(sheet, frameRect(settings, role, Direction::Side, 0)), 
        role_(role), /*frame_(frame % 3),*/ field_position_(initial_position), velocity_(initial_velocity), scale_(scale)
{
    this->species_ = (role == SpeciesRole::Prey) ? this->settings_.prey_name : this->settings_.predator_name;
    
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist_frame(0, 3);

    this->frame_ = dist_frame(engine);
    this->SetSpriteOrigin({static_cast<float>(this->settings_.sprite_width/2), static_cast<float>(this->settings_.sprite_height/2)});
    this->SetFieldPosition(this->field_position_);
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

sf::Vector2f Creature::Velocity()
{
    return this->velocity_; // default
}

void Creature::SetVelocity(sf::Vector2f velocity)
{
    this->velocity_ = velocity;
}

float Creature::Speed()
{
    return (float) std::sqrtf(std::powf(this->velocity_.x, 2) + std::powf(this->velocity_.y, 2));
}

sf::Vector2f Creature::FieldPosition()
{
    return this->field_position_; // default 
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
    return std::sqrtf(std::powf(c1.FieldPosition().x - c2.FieldPosition().x, 2) 
                    + std::powf(c1.FieldPosition().y - c2.FieldPosition().y, 2));
}

void Creature::update(float dt)
{
    float dx = this->velocity_.x*dt;
    float dy = this->velocity_.y*dt;
    float walk_rate = 4;
    float total_time_prev = this->total_time_;
    float mod_time_prev = std::fmod(total_time_prev, 1/walk_rate);
    this->total_time_ = std::min(this->total_time_+dt, static_cast<float>(1e9));
    float mod_time = std::fmodf(total_time_, 1/walk_rate);
    if (mod_time <= mod_time_prev) this->frame_++;
    this->SetFieldPosition({this->field_position_.x + dx, this->field_position_.y + dy});
}

sf::Sprite& Creature::GetSprite()
{
    return this->sprite_;
}

void Creature::SetSpriteOrigin(sf::Vector2f origin)
{
    this->sprite_.setOrigin(origin);
}

void Creature::SetSpritePosition(sf::Vector2f position)
{
    // set sprite orientation (direction, face)
    this->face_ = this->velocity_.x >= 0 ? Face::Right : Face::Left; // faces horizontal direction
    if (abs(this->velocity_.x) > abs(this->velocity_.y)) this->direction_ = Direction::Side; // sprite is moving "more" horizontally
    else this->direction_ = this->velocity_.y >= 0 ? Direction::Up : Direction::Down; // otherwise moving vertically, now pick a direction
    
    this->scale_.x = settings_.scale_factor * static_cast<int>(this->face_);
    this->SetSpriteScale(this->scale_);
    this->sprite_.setTextureRect(frameRect(this->settings_, this->role_, this->direction_, this->frame_));
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