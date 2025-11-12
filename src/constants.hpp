#pragma once

#include <SFML/Graphics.hpp>
#include <string>

enum class Direction : int { Side = 0, Down = 1, Up = 2 };
enum class Face : int { Left = -1, Right = 1};
enum SpeciesRole { Prey, Predator };

constexpr int sprite_width_default = 16;
constexpr int sprite_height_default = 16;
constexpr int prey_row_offset_default = 21; 
constexpr int prey_col_offset_default = 0;
constexpr int predator_row_offset_default = 24;
constexpr int predator_col_offset_default = 8;
constexpr float scale_factor_default = 2.0f;
constexpr std::string_view prey_name_default  = "Sheep";
constexpr std::string_view predator_name_default  = "Wolf";
constexpr std::string_view prey_sound_default  = "Baaah";
constexpr std::string_view predator_sound_default  = "Awoooo";
constexpr int numprey_default = 100;
constexpr int numpred_default = 10;
constexpr float vmax_default = 400.f;
constexpr float hunger_tick_seconds_default = 0.5f;


// constexpr sf::Vector2i poseOffset(const Settings& settings, SpeciesRole role, Direction dir, int frame)
// {
//     int col = ((role == SpeciesRole::Prey) ? settings.prey_col_offset : settings.predator_col_offset) + frame; 
//     int row = ((role == SpeciesRole::Prey) ? settings.prey_row_offset : settings.predator_row_offset) + static_cast<int>(dir);
//     return { col*settings.sprite_width, row*settings.sprite_height };
// }

// constexpr sf::IntRect frameRect(const Settings& settings, SpeciesRole role, Direction dir, int frame)
// {
//     return { poseOffset(settings, role, dir, frame % 4), { settings.sprite_width, settings.sprite_height } };
// }
