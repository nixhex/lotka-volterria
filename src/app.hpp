#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "field.hpp"
#include "constants.hpp"
#include "AssetManager.hpp"
#include "creature.hpp"

class App
{
public:
    App();
private:
    std::vector<Field> fields;
    AssetManager assets;
};