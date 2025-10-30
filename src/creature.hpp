#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <ctime>
#include <unordered_map>
#include "constants.hpp"
#include "settings.hpp"

class Creature
{
public:
    Creature(const Settings&, const sf::Texture&, SpeciesRole, /* Direction, Face, */ 
        sf::Vector2f initial_position, 
        sf::Vector2f initial_velocity,
        sf::Vector2f scale);
    std::string Species();
    void Eat();
    void Move();
    void Sound();
    void Sleep();
    bool MateWith(Creature);
    void Die();
    float Hunger(); // 0...1
    float Libido(); // 0...1
    sf::Vector2f Velocity(); // keys "X" and "Y"
    void SetVelocity(sf::Vector2f);
    float Speed(); // return absolute of Velocity
    sf::Vector2f FieldPosition();
    std::time_t TimeBorn();
    std::time_t Age();
    static float Distance(Creature, Creature);
    sf::Sprite& GetSprite();
    void SetSpriteOrigin(sf::Vector2f);
    void SetSpritePosition(sf::Vector2f);
    void SetSpriteScale(sf::Vector2f);
    void SetFieldPosition(sf::Vector2f);
    // draw and animate
    void update(float);
    void draw(sf::RenderTarget& rt) const { rt.draw(sprite_); }

protected:
    std::string species_;
    float hunger_ = 0;
    float libido_ = 0;
    //std::array<float, 2> velocity_;
    sf::Vector2f velocity_;
    sf::Vector2f field_position_;
    sf::Vector2f scale_;
    //std::array<float, 2> position_;
    std::time_t timeborn_;
    std::time_t age_;
    std::string sound_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    sf::RenderWindow window_;
    const Settings& settings_;
    SpeciesRole role_;
    bool sprite_mirrored_ = false;
    Direction direction_;
    Face face_;
    int frame_=0;
    float total_time_=0;
};

