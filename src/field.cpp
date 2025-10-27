#include <SFML/Graphics.hpp>
#include <random>
#include "AssetManager.hpp"
#include "creature.hpp" 
#include "field.hpp"
#include "assets/spritesheet_png.hpp"
#include "constants.hpp"
#include "settings.hpp"

Field::Field(const Settings& settings, AssetManager& assets, sf::RenderWindow& window, int numPrey, int numPred) : 
    settings_(settings), assets_(assets), window_(window)
{
    auto window_dimensions = window.getSize();
    unsigned width =  window_dimensions.x;
    unsigned height = window_dimensions.y;
    const auto& sheet = assets.getTexture("sheet");
    creatures_.reserve(numPred + numPrey);

    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_int_distribution<int> dist_x((int) this->settings_.sprite_width/2*this->settings_.scale_factor, 
                                 (int) window_dimensions.x-this->settings_.sprite_width/2*this->settings_.scale_factor);
    std::uniform_int_distribution<int> dist_y((int) this->settings_.sprite_height/2*this->settings_.scale_factor, 
                                 (int) window_dimensions.y-this->settings_.sprite_height/2*this->settings_.scale_factor);
    std::uniform_int_distribution<int> dist_direction(static_cast<int>(Direction::Side), static_cast<int>(Direction::Up));
    std::bernoulli_distribution dist_face(0.5);
    int direction;
    Face face;

    for (int i=0; i<numPrey; i++)
    {
        direction = dist_direction(engine);
        face = dist_face(engine) ? Face::Right : Face::Left;
        this->creatures_.emplace_back(this->settings_, sheet, SpeciesRole::Prey,
            static_cast<Direction>(direction), face, 
            sf::Vector2f{static_cast<float>(dist_x(engine)), static_cast<float>(dist_y(engine))},
            sf::Vector2f{this->settings_.scale_factor, this->settings_.scale_factor}, 0);
    }  

    for (int i=0; i<numPred; i++)
    {
        direction = dist_direction(engine);
        face = dist_face(engine) ? Face::Right : Face::Left;
        this->creatures_.emplace_back(this->settings_, sheet, SpeciesRole::Predator,
            static_cast<Direction>(direction), face, 
            sf::Vector2f{static_cast<float>(dist_x(engine)), static_cast<float>(dist_y(engine))},
            sf::Vector2f{this->settings_.scale_factor, this->settings_.scale_factor}, 0);
    }   
}

std::vector<Creature>& Field::GetCreatures()
{
    return this->creatures_;
}

const Creature& Field::GetCreature(int index)
{
    return this->creatures_.at(index);
}