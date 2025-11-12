#include <SFML/Graphics.hpp>
#include <random>
//#include <utility>
#include <algorithm>
#include "AssetManager.hpp"
#include "creature.hpp" 
#include "field.hpp"
#include "assets/spritesheet_png.hpp"
#include "constants.hpp"
#include "settings.hpp"

Field::Field(const Settings& settings, AssetManager& assets, sf::RenderWindow& window, sf::Clock& clock) : 
    settings_(settings), assets_(assets), window_(window), field_clock_(clock)
{
    std::cout << "field constructor called\n";
    auto window_dimensions = window.getSize();
    unsigned width =  window_dimensions.x;
    unsigned height = window_dimensions.y;
    int numPrey = settings.numprey;
    int numPred = settings.numpred;

    const auto& sheet = assets.getTexture("sheet");
    creatures_.reserve(numPrey + numPred);

    std::random_device rd;
    std::mt19937 engine(rd());

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

    std::uniform_real_distribution<float> x_orig_dist(this->settings_.field_extrema[0], this->settings_.field_extrema[1]);
    std::uniform_real_distribution<float> y_orig_dist(this->settings_.field_extrema[2], this->settings_.field_extrema[3]);
    std::uniform_real_distribution<float> x_vel_prey_dist(-200.f, 200.f);
    std::uniform_real_distribution<float> y_vel_prey_dist(-200.f, 200.f);
    std::uniform_real_distribution<float> x_accel_prey_dist(-64.f, 64.f);
    std::uniform_real_distribution<float> y_accel_prey_dist(-64.f, 64.f);
    std::uniform_real_distribution<float> x_vel_pred_dist(-200.f, 200.f);
    std::uniform_real_distribution<float> y_vel_pred_dist(-200.f, 200.f);
    std::uniform_real_distribution<float> x_accel_pred_dist(-64.f, 64.f);
    std::uniform_real_distribution<float> y_accel_pred_dist(-64.f, 64.f);
    for(int i=0; i<numPrey; i++)
    {
        float x_orig  = x_orig_dist(engine);
        float y_orig  = y_orig_dist(engine);
        float x_vel   = x_vel_prey_dist(engine);
        float y_vel   = y_vel_prey_dist(engine); 
        float x_accel = x_accel_prey_dist(engine);
        float y_accel = y_accel_prey_dist(engine);
        this->creatures_.emplace_back(this->settings_, sheet, SpeciesRole::Prey,
            sf::Vector2f({x_orig, y_orig}), sf::Vector2f({x_vel, y_vel}));
        this->creatures_.at(0).SetAcceleration({x_accel, y_accel});
        this->prey_count++;
    }
    for(int i=0; i<numPred; i++)
    {
        float x_orig  = x_orig_dist(engine);
        float y_orig  = y_orig_dist(engine);
        float x_vel   = x_vel_pred_dist(engine);
        float y_vel   = y_vel_pred_dist(engine); 
        float x_accel = x_accel_pred_dist(engine);
        float y_accel = y_accel_pred_dist(engine);
        this->creatures_.emplace_back(this->settings_, sheet, SpeciesRole::Predator,
            sf::Vector2f({x_orig, y_orig}), sf::Vector2f({x_vel, y_vel}));
        // this->creatures_.emplace_back(this->settings_, sheet, SpeciesRole::Predator,
        //     sf::Vector2f({u_pred_x, u_y}), sf::Vector2f({-100.f, 0.f}));
        this->creatures_.at(0).SetAcceleration({x_accel, y_accel});
        // this->creatures_.at(1).SetAcceleration({0.f, 0.f});
        this->pred_count++;
    }
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
    b = Y_min - m*y_max;
    p_result.y = m*field_point.y + b;
    
    return p_result;
}

void Field::IncrementPopulation(SpeciesRole role)
{
    if(role == SpeciesRole::Prey) this->prey_count++;
    else this->pred_count++;
}

void Field::DecrementPopulation(SpeciesRole role)
{
    if(role == SpeciesRole::Prey) this->prey_count--;
    else this->pred_count--;
}

void Field::CheckInteractions()
{
    for(int i=0; i < this->creatures_.size(); ++i)
    {
        for(int j=i+1; j < this->creatures_.size(); ++j)
        {
            // check proximity
            float distance_sq = Creature::DistanceSq(this->creatures_[i], this->creatures_[j]);
            if(distance_sq <= 2500.f)
            {
                bool killI = this->creatures_[i].GetSpeciesRole() == SpeciesRole::Prey
                          && this->creatures_[j].GetSpeciesRole() == SpeciesRole::Predator;
                bool killJ = this->creatures_[i].GetSpeciesRole() == SpeciesRole::Predator
                          && this->creatures_[j].GetSpeciesRole() == SpeciesRole::Prey;
                if(killI)
                {
                    this->creatures_[j].Kill(this->creatures_[i], *this);
                    this->prey_count--;
                    // other stuff?
                } else if(killJ) 
                {
                    this->creatures_[i].Kill(this->creatures_[j], *this);
                    this->prey_count--;
                } else
                {
                    Creature::Mate(this->creatures_[i], this->creatures_[j], this->settings_, *this);
                    if (this->creatures_[i].GetSpeciesRole() == SpeciesRole::Prey) this->prey_count++;
                    else this->pred_count++;
                }
                // std::cout << this->field_clock_.getElapsedTime().asSeconds() << ", "
                //           << this->prey_count << ", " << this->pred_count << std::endl;
            }
        }
    }

    // sweep and remove
    creatures_.erase(std::remove_if(creatures_.begin(), creatures_.end(),
        [](const Creature& c){ return !(c.IsAlive()); }),
        creatures_.end());
}

template<class Engine, class Dist>
void Field::PopulateRandom(Engine& eng, Dist&& dist_pos_x, Dist&& dist_pos_y, 
    Dist&& dist_vel_x, Dist&& dist_vel_y, Dist&& dist_accel_x, Dist&& dist_accel_y, 
    SpeciesRole role, int qty, sf::Texture sheet)
{
    auto x = dist(eng);
    for (int i=0; i<qty; i++)
    {
        this->creatures_.emplace_back();
    }
}

std::size_t Field::Count(SpeciesRole role) const noexcept {
    return std::count_if(creatures_.begin(), creatures_.end(),
        [role](const Creature& c) {
            return c.IsAlive() && c.GetSpeciesRole() == role;
        });
}

template<class F>
void for_each_pair(std::vector<Creature>& cs, F&& f) // f is a function pointer (verify this)
{
    const std::size_t n = cs.size();
    for (std::size_t i=0; i<n; ++i)
    {
        for (std::size_t j=i+1; i<n; ++j)
        {
            f(cs[i], cs[j]); // handle function once
        }
    }
}

// usage
// for_each_pair(creatures, [](Creature& a, Creature& b){
//     collide(a, b);                  // update BOTH a and b inside here
// });