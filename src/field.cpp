#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "AssetManager.hpp"
#include "creature.hpp" 
#include "field.hpp"
#include "assets/spritesheet_png.hpp"
#include "constants.hpp"

Field::Field(AssetManager& assets, sf::RenderWindow& window, int numPrey, int numPred) : 
    assets_(assets), window_(window)
{
    auto window_dimensions = window.getSize();
    unsigned width =  window_dimensions.x;
    unsigned height = window_dimensions.y;
    const auto& sheet = assets.getTexture("sheet");
    creatures_.reserve(numPred + numPrey);

    this->creatures_.emplace_back(sheet, SpeciesRole::Prey, 
        Direction::Side, Face::Right, sf::Vector2f{100, 100}, sf::Vector2f{4.f, 4.f}, 0);
    this->creatures_.emplace_back(sheet, SpeciesRole::Predator, 
        Direction::Side, Face::Left, sf::Vector2f{250, 100}, sf::Vector2f{4.f, 4.f}, 0);
}

std::vector<Creature>& Field::GetCreatures()
{
    return this->creatures_;
}

const Creature& Field::GetCreature(int index)
{
    return this->creatures_.at(index);
}