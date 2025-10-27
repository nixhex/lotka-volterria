#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "field.hpp"
#include "constants.hpp"
#include "AssetManager.hpp"
#include "creature.hpp"
#include "settings.hpp"
class App
{
public:
    App();
    int run();
private:
    Settings settings;
    std::vector<Field> fields;
    sf::RenderWindow window;
    AssetManager assets;
    std::vector<sf::Sprite> sprites;
    int sprite_width = settings.sprite_width;
    int sprite_height = settings.sprite_height;
    int prey_row_offset = settings.prey_row_offset;
    int prey_col_offset = settings.prey_col_offset;
    int predator_row_offset = settings.predator_row_offset;
    int predator_col_offset = settings.predator_col_offset;
    float scale_factor = settings.scale_factor;
};