#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>

// sprite pixel width (from spritesheet)
constexpr int sprite_width      = 16;
constexpr int sprite_height     = 16;

// Prey Sprite Base Poses
constexpr int prey_row_offset = 21; // 21: side poses for sheep; +1 for down, +2 for up
constexpr int prey_col_offset = 0; // 0: default position for sheep; cycle +1, +2, +3 for pose change (walking?)

// Predator Sprite Base Positions
constexpr int predator_row_offset = 24; // 24: side poses for wolf; +1 for down, +2 for up
constexpr int predator_col_offset = 8; // 8: default position for wolf; cycle +1, +2, +3 for pose change (walking?)

constexpr float scale_factor = 2.f;

enum class Direction : int { Side = 0, Down = 1, Up = 2 };
enum class Face : int { Left = -1, Right = 1};
enum SpeciesRole { Prey, Predator };

constexpr sf::Vector2i poseOffset(SpeciesRole role, Direction dir, int frame)
{
    int col = ((role == SpeciesRole::Prey) ? prey_col_offset : predator_col_offset) + frame; 
    int row = ((role == SpeciesRole::Prey) ? prey_row_offset : predator_row_offset) + static_cast<int>(dir);
    return { col*sprite_width, row*sprite_height };
}

constexpr sf::IntRect frameRect(SpeciesRole role, Direction dir, int frame)
{
    return { poseOffset(role, dir, frame % 4), { sprite_width, sprite_height } };
}

constexpr std::string_view prey_name = "Sheep";
constexpr std::string_view predator_name = "Wolf";

constexpr std::string_view prey_sound = "Baaah";
constexpr std::string_view predator_sound = "Awoooo";

constexpr sf::Vector2i SPRITE_DIMS{ sprite_width, sprite_height };
