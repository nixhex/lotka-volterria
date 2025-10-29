#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include "settings.hpp"
#include "app.hpp"
#include "constants.hpp"
#include "assets/spritesheet_png.hpp"

App::App(int argc, char** argv)
{
    //int numprey=200, numpred=20; // default prey and predator counts
    //Settings settings;
    std::unordered_map<std::string_view, std::string> inputs;

    this->ParseConsoleInput(this->settings, inputs, argc, argv);
    std::cout << "prey = " << this->settings.numprey << std::endl;
    std::cout << "pred = " << this->settings.numpred << std::endl;
    std::cout << "sf   = " << this->settings.scale_factor << std::endl;

    this->settings.field_extrema = { 
        0.f, 1000.f, 
        0.f, 1000.f
    }; // xmin, xmax, ymin, ymax
    
    float x_min_screen = this->settings.sprite_width/2*this->settings.scale_factor;
    float x_max_screen = this->settings.mode_size.x - this->settings.sprite_width/2*this->settings.scale_factor;
    float y_min_screen = this->settings.sprite_height/2*this->settings.scale_factor;
    float y_max_screen = this->settings.mode_size.y - this->settings.sprite_height/2*this->settings.scale_factor;

    this->settings.screen_extrema = {
        x_min_screen, x_max_screen, 
        y_min_screen, y_max_screen
    };

    this->window = sf::RenderWindow(sf::VideoMode(this->settings.mode_size), "Lotka-Volterria");
    this->window.setFramerateLimit(144);
    this->assets.requireTextMem("sheet", src_sprites_spritesheet_png, src_sprites_spritesheet_png_len);
    this->fields.push_back(Field(this->settings, this->assets, this->window));
}

int App::run()
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        for(Field& field : this->fields) // allow for multiple fields, but can't implement bc no multiple "windows" yet
        {
            for (Creature& creature : field.GetCreatures())
            {
                window.draw(creature.GetSprite());           
            }
        }
        window.display();
    }
    return 0;
}

void App::ParseConsoleInput(Settings& settings, std::unordered_map<std::string_view, std::string>& inputs, 
    int argc, char** argv)
{
    inputs.reserve(argc);
    for (int i=0; i<argc-1; i+=2)
    {
        // assign every other 
        char* key = argv[i+1];
        char* val = argv[i+2];
        inputs[key] = std::string(val);
    }
    settings.numprey = inputs.find("prey") != inputs.end() ? std::stoi(inputs["prey"]) : numprey_default;
    settings.numpred = inputs.find("pred") != inputs.end() ? std::stoi(inputs["pred"]) : numpred_default;
    settings.scale_factor = inputs.find("sf") != inputs.end() ? std::stof(inputs["sf"]) : scale_factor_default;
}