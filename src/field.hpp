#pragma once

#include <SFML/Graphics.hpp>
#include "creature.hpp"
#include "AssetManager.hpp"
#include "settings.hpp"
#include "field.hpp"
#include <vector>

template <typename T> struct Extrema {
    T x_min;
    T x_max;
    T y_min;
    T y_max;
};

class Field
{
public:
    Field(const Settings&, AssetManager&, sf::RenderWindow&, sf::Clock&);
    const AssetManager& Assets() const noexcept { return assets_; }
    std::vector<Creature>& Creatures();
    sf::RenderWindow RenderWindow();
    std::vector<Creature>& GetCreatures();
    const Creature& GetCreature(int);
    static sf::Vector2f FieldToScreenTX(sf::Vector2f, std::array<float, 4>, std::array<float, 4>);
    template<class Engine, class Dist>
    void PopulateRandom(Engine&, Dist&&, Dist&&, Dist&&, Dist&&, Dist&&, Dist&&, 
        SpeciesRole role, int, sf::Texture);
    void CheckInteractions();
    void IncrementPopulation(SpeciesRole);
    void DecrementPopulation(SpeciesRole);
    std::size_t Count(SpeciesRole) const noexcept;
    const sf::Clock GetClock() const noexcept { return field_clock_; };
protected:
    sf::Texture preyTexture, predatorTexture; // make as members of object so they don't dissappear
    time_t last_time;
    const Settings& settings_;
    std::vector<Creature> creatures_;
    const AssetManager& assets_;
    const sf::RenderWindow& window_;
    unsigned int prey_count = 0;
    unsigned int pred_count = 0;
    const sf::Clock field_clock_;
};