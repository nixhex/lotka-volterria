#pragma once

#include <SFML/Graphics.hpp>
#include <string>

struct Settings {
    int sprite_width = 16, sprite_height = 16;
    int prey_row_offset = 21, prey_col_offset = 0;
    int predator_row_offset = 24, predator_col_offset = 8;
    float scale_factor = 2.f;
    std::string prey_name  = "Sheep";
    std::string predator_name  = "Wolf";
    std::string prey_sound  = "Baaah";
    std::string predator_sound  = "Awoooo";
};