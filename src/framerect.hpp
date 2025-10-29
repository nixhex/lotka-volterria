#pragma once

#include <sfml/Graphics.hpp>
#include <array>
#include "settings.hpp"

constexpr sf::Vector2i poseOffset(const Settings& settings, SpeciesRole role, Direction dir, int frame)
{
    int col = ((role == SpeciesRole::Prey) ? settings.prey_col_offset : settings.predator_col_offset) + frame; 
    int row = ((role == SpeciesRole::Prey) ? settings.prey_row_offset : settings.predator_row_offset) + static_cast<int>(dir);
    return { col*settings.sprite_width, row*settings.sprite_height };
}

constexpr sf::IntRect frameRect(const Settings& settings, SpeciesRole role, Direction dir, int frame)
{
    return { poseOffset(settings, role, dir, frame % 4), { settings.sprite_width, settings.sprite_height } };
}

