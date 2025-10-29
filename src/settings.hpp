#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include "constants.hpp"

// template <typename T> struct Extrema {
//     T x_min;
//     T x_max;
//     T y_min;
//     T y_max;
// };

struct Settings {
    int sprite_width = sprite_width_default, sprite_height = sprite_height_default;
    int prey_row_offset = prey_row_offset_default, prey_col_offset = prey_col_offset_default;
    int predator_row_offset = predator_row_offset_default, predator_col_offset = predator_col_offset_default;
    float scale_factor = scale_factor_default;
    std::string prey_name  = "Sheep";
    std::string predator_name  = "Wolf";
    std::string prey_sound  = "Baaah";
    std::string predator_sound  = "Awoooo";
    // unsigned int screen_width = 1920;
    // unsigned int screen_height = 1080;
    sf::Vector2u mode_size = {1920u, 1080u};
    std::array<float, 4> screen_extrema; // x_min, x_max, y_min, y_max
    std::array<float, 4> field_extrema; // x_min, x_max, y_min, y_max
    int numprey = numprey_default;
    int numpred = numpred_default;
};