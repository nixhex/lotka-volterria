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
    Creature(const Settings&, const sf::Texture&, SpeciesRole, Direction, Face, 
        sf::Vector2f position, 
        sf::Vector2f scale, 
        int frame);
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
    // draw and animate
    void update(float);
    void draw(sf::RenderTarget& rt) const { rt.draw(sprite_); }

protected:
    std::string species_;
    float hunger_ = 0;
    float libido_ = 0;
    std::array<float, 2> velocity_;
    std::array<float, 2> position_;
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
    int frame_;
};

