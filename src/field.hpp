#pragma once

#include <SFML/Graphics.hpp>
#include "creature.hpp"
#include "AssetManager.hpp"
#include "settings.hpp"
#include <vector>

template <typename T> struct Extrema {
    T x_min;
    T x_max;
    T y_min;
    T y_max;
};

// template <typename T> struct Point {
//     T x;
//     T y;
// };

class Field
{
public:
    Field(const Settings&, AssetManager&, sf::RenderWindow&);
    std::vector<Creature>& Creatures();
    sf::RenderWindow RenderWindow();
    std::vector<Creature>& GetCreatures();
    const Creature& GetCreature(int);
    static sf::Vector2f FieldToScreenTX(sf::Vector2f, std::array<float, 4>, std::array<float, 4>);
protected:
    sf::Texture preyTexture, predatorTexture; // make as members of object so they don't dissappear
    time_t last_time;
    const Settings& settings_;
    std::vector<Creature> creatures_;
    const AssetManager& assets_;
    const sf::RenderWindow& window_;
    // sf::Vector2i field_dimensions_;
    // Extrema<float> FieldExtrema;
    // Extrema<float> ScreenExtrema;
};