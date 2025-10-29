#include <SFML/Graphics.hpp>
#include <random>
#include "AssetManager.hpp"
#include "creature.hpp" 
#include "field.hpp"
#include "assets/spritesheet_png.hpp"
#include "constants.hpp"
#include "settings.hpp"

Field::Field(const Settings& settings, AssetManager& assets, sf::RenderWindow& window) : 
    settings_(settings), assets_(assets), window_(window)
{
    auto window_dimensions = window.getSize();
    unsigned width =  window_dimensions.x;
    unsigned height = window_dimensions.y;
    int numPrey = settings.numprey;
    int numPred = settings.numpred;

    const auto& sheet = assets.getTexture("sheet");
    creatures_.reserve(numPrey + numPred);

    std::random_device rd;
    std::mt19937 engine(rd());
    // float left_bound = this->settings_.sprite_width/2*this->settings_.scale_factor;
    // float right_bound = window_dimensions.x-this->settings_.sprite_width/2*this->settings_.scale_factor;
    // float upper_bound = this->settings_.sprite_height/2*this->settings_.scale_factor;
    // float lower_bound = window_dimensions.y-this->settings_.sprite_height/2*this->settings_.scale_factor;
    // this->ScreenExtrema = {left_bound, right_bound, upper_bound, lower_bound};
    // this->FieldExtrema = {0.f, 1000.f, 0.f, 1000.f};

    // make these field dimensions now
    float field_x_min = this->settings_.field_extrema[0];
    float field_x_max = this->settings_.field_extrema[1];
    float field_y_min = this->settings_.field_extrema[2];
    float field_y_max = this->settings_.field_extrema[3];
    std::cout << "field_x_min: " << field_x_min << "\n";
    std::cout << "field_x_max: " << field_x_max << "\n";
    std::cout << "field_y_min: " << field_y_min << "\n";
    std::cout << "field_y_max: " << field_y_max << "\n";

    float midfield_x = (field_x_min + field_x_max)/2;
    float midfield_y = (field_y_min + field_y_max)/2;
    
    // horizontal quarterway points
    float u_prey_x = (field_x_min + midfield_x)/2;  
    float u_pred_x = (field_x_max + midfield_x)/2;
    float u_y = midfield_y;

    
    // standard deviations (right now using 6.6 sigma over half interval)
    float std_dev_x = (field_x_max - u_prey_x)/13.2; // whole x bell curve fits within half field and wall
    float std_dev_y = (field_y_max  - midfield_y)/6.6;


    //std::uniform_int_distribution<int> dist_x(left_bound, right_bound);    
    //std::uniform_int_distribution<int> dist_y(upper_bound, lower_bound);
    std::normal_distribution<float> dist_x_prey(u_prey_x, std_dev_x);
    std::normal_distribution<float> dist_x_pred(u_pred_x, std_dev_x);
    std::normal_distribution<float> dist_y(u_y, std_dev_y);

    // direction and mirroring
    std::uniform_int_distribution<int> dist_direction(static_cast<int>(Direction::Side), static_cast<int>(Direction::Up));
    std::bernoulli_distribution dist_face(0.5);
    
    int direction;
    Face face;

    // for (int i=0; i<numPrey; i++)
    // {
    //     direction = dist_direction(engine);
    //     face = dist_face(engine) ? Face::Right : Face::Left;
    //     this->creatures_.emplace_back(this->settings_, sheet, SpeciesRole::Prey,
    //         static_cast<Direction>(direction), face, 
    //         sf::Vector2f{static_cast<float>(dist_x_prey(engine)), static_cast<float>(dist_y(engine))},
    //         sf::Vector2f{this->settings_.scale_factor, this->settings_.scale_factor}, 0);
    // }  

    // for (int i=0; i<numPred; i++)
    // {
    //     direction = dist_direction(engine);
    //     face = dist_face(engine) ? Face::Right : Face::Left;
    //     this->creatures_.emplace_back(this->settings_, sheet, SpeciesRole::Predator,
    //         static_cast<Direction>(direction), face, 
    //         sf::Vector2f{static_cast<float>(dist_x_pred(engine)), static_cast<float>(dist_y(engine))},
    //         sf::Vector2f{this->settings_.scale_factor, this->settings_.scale_factor}, 0);
    // }   

    this->creatures_.emplace_back(this->settings_, sheet, SpeciesRole::Prey,
    static_cast<Direction>(Direction::Side), Face::Right, 
    sf::Vector2f{750, 750},
    sf::Vector2f{this->settings_.scale_factor, this->settings_.scale_factor}, 0);
}

std::vector<Creature>& Field::GetCreatures()
{
    return this->creatures_;
}

const Creature& Field::GetCreature(int index)
{
    return this->creatures_.at(index);
}

sf::Vector2f Field::FieldToScreenTX(sf::Vector2f field_point, std::array<float, 4> screen_extrema, std::array<float, 4> field_extrema)
{
    sf::Vector2f p_result;
    // X transform
    float X_max = screen_extrema[1]; float X_min = screen_extrema[0];
    float x_max = field_extrema[1]; float x_min = field_extrema[0];
    auto m = (X_max - X_min) / (x_max - x_min);
    auto b = X_max - m*x_max;
    p_result.x = m*field_point.x + b;

    // Y transform
    float Y_max = screen_extrema[3]; float Y_min = screen_extrema[2];
    float y_max = field_extrema[3]; float y_min = field_extrema[2];
    m = (Y_min - Y_max) / (y_max - y_min);
    std::cout << "m: " << m << std::endl;
    b = Y_min - m*y_max;
    std::cout << "b: " << b << std::endl;
    p_result.y = m*field_point.y + b;
    
    return p_result;
}