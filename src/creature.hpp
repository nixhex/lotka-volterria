#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <ctime>

constexpr std::string_view prey_name = "Sheep";
constexpr std::string_view predator_name = "Wolf";

constexpr std::string_view prey_sound = "Baaah";
constexpr std::string_view predator_sound = "Awooooo";

constexpr int prey_row         = 21; // 21 for sheep facing side
constexpr int prey_col         = 0; // 0-7 for sheep
constexpr int sprite_width      = 16;
constexpr int sprite_height     = 16;

constexpr sf::Vector2i PREY_POSE_1 {
    prey_col*sprite_width,
    prey_row*sprite_height
};

constexpr int predator_row =  24; // 24 for wolves facing side
constexpr int predator_col =   4; // 8-11 for brown/white wolves
constexpr sf::Vector2i PREDATOR_POSE_1 {
    predator_col*sprite_width,
    predator_row*sprite_height
};

constexpr sf::Vector2i SPRITE_DIMS{sprite_width, sprite_height};

class Creature
{
public:
    Creature(const sf::Sprite&, std::string_view, std::string_view);
    std::string Species();
    void Eat();
    void Move();
    void Sound();
    void Sleep();
    bool MateWith(Creature);
    void Die();
    float Hunger(); // 0...1
    float Libido(); // 0...1
    std::array<float, 2> Velocity(); // keys "X" and "Y"
    float Speed(); // return absolute of Velocity
    std::array<float, 2> Position();
    std::time_t TimeBorn();
    std::time_t Age();
    static float Distance(Creature, Creature);
    sf::Sprite& GetSprite();
    void SetSpriteOrigin(sf::Vector2f);
    void SetSpritePosition(sf::Vector2f);
    void SetSpriteScale(sf::Vector2f);

    protected:
    std::string species_;
    float hunger = 0;
    float libido = 0;
    std::array<float, 2> velocity;
    std::array<float, 2> position;
    std::time_t timeborn;
    std::time_t age;
    std::string sound_;
    sf::Sprite sprite_;
};

