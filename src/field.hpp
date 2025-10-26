#pragma once

#include <SFML/Graphics.hpp>
#include "creature.hpp"
#include <vector>

class Field
{
public:
    Field(sf::RenderWindow&, int, int);
    std::vector<Creature>& Creatures();
    sf::RenderWindow RenderWindow();
    std::vector<Creature>& GetCreatures();
    const Creature& GetCreature(int);

protected:
    sf::Texture preyTexture, predatorTexture; // make as members of object so they don't dissappear
    time_t last_time;
    std::vector<Creature> creatures;
};