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
    std::cout << R"(prey = )" << this->settings.numprey << R"(
pred = )" << this->settings.numpred << R"(
sf = )" << this->settings.scale_factor << R"(
width = )" << this->settings.mode_size.x << R"(
height = )" << this->settings.mode_size.y << R"(
)";
    this->settings.field_extrema = { 
        0.f, 960.f, 
        0.f, 540.f
    }; // xmin, xmax, ymin, ymax
    
    float x_min_screen = this->settings.sprite_width/2*this->settings.scale_factor;
    float x_max_screen = this->settings.mode_size.x - this->settings.sprite_width/2*this->settings.scale_factor;
    float y_min_screen = this->settings.sprite_height/2*this->settings.scale_factor;
    float y_max_screen = this->settings.mode_size.y - this->settings.sprite_height/2*this->settings.scale_factor;

    this->settings.screen_extrema = {
        x_min_screen, x_max_screen, 
        y_min_screen, y_max_screen
    };

    this->window = sf::RenderWindow(sf::VideoMode(this->settings.mode_size), "Lotka-Volterria", sf::Style::None);
    this->window.setFramerateLimit(144);
    this->assets.requireTextMem("sheet", src_sprites_spritesheet_png, src_sprites_spritesheet_png_len);
    this->fields.push_back(Field(this->settings, this->assets, this->window, this->global_clock));

    this->settings.vmax = 400.f;
}

int App::run()
{
    sf::Clock clock;
    sf::Clock global_clock;
    float accumulated_sec=0.f;
    const float TICK = 0.25f;
    std::cout << "Time, Prey, Predator\n";
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        float deltaTimeSec= dt.asSeconds();
        accumulated_sec += deltaTimeSec;
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
            field.CheckInteractions();
            for (Creature& creature : field.GetCreatures())
            {
                //std::cout << "Role: " << creature.GetSpeciesRole() << std::endl;
                creature.update(deltaTimeSec);
                window.draw(creature.GetSprite());           
            }
            // --- run 1 Hz logic exactly once per elapsed second ---
            while (accumulated_sec >= 0.25) {      // catch up if >1 second passed
                accumulated_sec -= 0.25;           // keep remainder
                // === your once-per-second work goes here ===
                //std::cout << "tick: " << global_clock.getElapsedTime().asSeconds() << std::endl;
                //std::cout << 1/deltaTimeSec << " Hz\n";
                // e.g., age counters, resource regen, logging, etc.
                auto num_prey = field.Count(SpeciesRole::Prey);
                auto num_pred = field.Count(SpeciesRole::Predator);
                std::cout << field.GetClock().getElapsedTime().asSeconds() 
                          << ", " << num_prey << ", " << num_pred << "\n";
            }
        }
            // --- run 1 Hz logic exactly once per elapsed second ---
        // while (accumulated_sec >= TICK) {      // catch up if >1 second passed
        //     accumulated_sec -= TICK;           // keep remainder
        //     // === your once-per-second work goes here ===
        //     //std::cout << "tick: " << global_clock.getElapsedTime().asSeconds() << std::endl;
        //     //std::cout << 1/deltaTimeSec << " Hz\n";
        //     // e.g., age counters, resource regen, logging, etc.
        // }
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
    settings.mode_size.x = inputs.find("width") != inputs.end() ? std::stoi(inputs["width"]) : 1920u;
    settings.mode_size.y = inputs.find("height") != inputs.end() ? std::stoi(inputs["height"]) : 1080u;
    settings.tick = inputs.find("tick") != inputs.end() ? std::stof(inputs["tick"]) : 0.25;
    settings.pred_hunger_threshold = inputs.find("predhunger") != inputs.end() ? std::stof(inputs["predhunger"]) : 5.f;
}