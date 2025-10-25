#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <ctime>

constexpr int sheep_row         = 21;
constexpr int sheep_col         = 0;
constexpr int sprite_width      = 16;
constexpr int sprite_height     = 16;

constexpr sf::Vector2i SHEEP_POSE_1 {
    sheep_col*sprite_width,
    sheep_row*sprite_height
};

constexpr int wolf_row =  24;
constexpr int wolf_col =   8;
constexpr sf::Vector2i WOLF_POSE_1 {
    wolf_col*sprite_width,
    wolf_row*sprite_height
};

constexpr sf::Vector2i SPRITE_DIMS{sprite_width, sprite_height};
class Creature
{
public:
    Creature();
    std::string Species();
    void Eat();
    void Move();
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

protected:
    std::string species;
    float hunger = 0;
    float libido = 0;
    std::array<float, 2> velocity;
    std::array<float, 2> position;
    std::time_t timeborn;
    std::time_t age;
};

class Field
{
public:
    Field(std::vector<sf::Sprite>*, sf::RenderWindow*, int, int);
    std::vector<Creature> Creatures();
    sf::RenderWindow RenderWindow();
protected:
    time_t last_time;
};