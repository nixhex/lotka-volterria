#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include "constants.hpp"

// template <typename T> struct Square {
//     T x_min;
//     T x_max;
//     T y_min;
//     T y_max;
// };

// typedef struct square {
//     sf::Vector2u top_left;
//     sf::Vector2u bottom_right;
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
    sf::Vector2u mode_size = {960u, 540u};
    std::array<float, 4> screen_extrema; // x_min, x_max, y_min, y_max
    std::array<float, 4> field_extrema; // x_min, x_max, y_min, y_max
    int numprey = numprey_default;
    int numpred = numpred_default;
    float vmax = vmax_default;
    float tick = 0.125f; // update acceleration for each creature
    float pred_hunger_threshold = 8.f; // if predator encounters prey, eats if fullness <= 5
    float pred_libido_threshold = 2.f;
    float prey_libido_threshold = 7.f;
    float pred_hunger_max = 10.f;
    float pred_libido_max = 10.f;
    float prey_libido_max = 10.f;
    float hunger_tick_seconds = hunger_tick_seconds_default;
    float prey_libido_rate = 0.5f;
    float pred_libido_rate = 0.2f;
};