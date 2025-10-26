#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <ctime>
#include "constants.hpp"

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

