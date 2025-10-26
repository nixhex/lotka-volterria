#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "creature.hpp"
#include "AssetManager.hpp"
#include <vector>

class Field
{
public:
    Field(AssetManager&, sf::RenderWindow&, int, int);
    std::vector<Creature>& Creatures();
    sf::RenderWindow RenderWindow();
    std::vector<Creature>& GetCreatures();
    const Creature& GetCreature(int);

protected:
    sf::Texture preyTexture, predatorTexture; // make as members of object so they don't dissappear
    time_t last_time;
    std::vector<Creature> creatures_;
    const AssetManager& assets_;
    const sf::RenderWindow& window_;
};