#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "assets/spritesheet_png.hpp"
#include "creature.hpp"
#include "field.hpp"
#include "constants.hpp"
#include "AssetManager.hpp"
#include "settings.hpp"
#include "framerect.hpp"

Creature::Creature(const Settings& settings, 
    const sf::Texture& sheet, SpeciesRole role,
    sf::Vector2f initial_position,
    sf::Vector2f initial_velocity) : settings_(&settings), sprite_(sheet, frameRect(settings, role, Direction::Side, 0)), 
    role_(role), field_position_(initial_position), velocity_(initial_velocity) /*,  scale_(scale) 
    scale_(sf::Vector2f({this->settings_.scale_factor, this->settings_.scale_factor}))*/
{   
    this->scale_ = sf::Vector2f({this->settings_->scale_factor, this->settings_->scale_factor});
    this->species_ = (role == SpeciesRole::Prey) ? this->settings_->prey_name : this->settings_->predator_name;

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist_frame(0, 3);

    this->frame_ = dist_frame(engine);
    this->SetSpriteOrigin({static_cast<float>(this->settings_->sprite_width/2), static_cast<float>(this->settings_->sprite_height/2)});
    this->SetFieldPosition(this->field_position_);

    this->accel_clock = sf::Clock(); 

    if(role == SpeciesRole::Prey) 
    {
        this->starve_rate_ = 0.f; // prey don't go hungry (yet) 
        this->libido_rate_ = settings.prey_libido_rate;
        this->max_libido_ = settings.prey_libido_max;
        this->libido_threshold_ = settings.prey_libido_threshold;
    } else {
        this->starve_rate_ = 1.0; // 1 per second
        this->libido_rate_ = settings.pred_libido_rate;
        this->max_libido_ = settings.pred_libido_max;
        this->libido_threshold_ = settings.pred_libido_threshold;
    }
}

std::string Creature::Species()
{
    return this->species_;
}

void Creature::Kill(Creature& meal, Field& field)
{
    if (this->fullness_ <= settings_->pred_hunger_threshold)
    {
        meal.alive_ = false;
        this->fullness_ = settings_->pred_hunger_max;
    }
}

// set a vector for Acceleration (units/second^2), provide time step (seconds), called by Move()
void Creature::Accelerate(float dt)
{
    float tick = this->settings_->tick;
    this->time_since_accel += dt;
    bool left_wall_collide = false, 
        right_wall_collide = false, 
        top_wall_collide = false, 
        bottom_wall_collide = false;
    // set up MT RNG
    // std::random_device rd;
    // std::mt19937 engine(rd());
    // accelerate randomly

    
    while(time_since_accel >= tick) // can't guarantee exactly equal, so detect GTEQ and reset
    {
        std::uniform_real_distribution<float> accel_x_dist(-64.f, 64.f);
        std::uniform_real_distribution<float> accel_y_dist(-64.f, 64.f);
        float accel_x = static_cast<float>(accel_x_dist(rng_));
        float accel_y = static_cast<float>(accel_y_dist(rng_));
        this->acceleration_ = sf::Vector2f({accel_x, accel_y}); 
        //std::cout << "velocity: {" << this->velocity_.x << ", " << this->velocity_.y << "}\n";
        //this->time_since_accel -= tick;
        left_wall_collide = this->field_position_.x <= this->settings_->field_extrema.at(0);
        right_wall_collide = this->field_position_.x >= this->settings_->field_extrema.at(1);
        bottom_wall_collide = this->field_position_.y <= this->settings_->field_extrema.at(2);
        top_wall_collide = this->field_position_.y >= this->settings_->field_extrema.at(3);
        if(left_wall_collide || right_wall_collide)
        {
            this->acceleration_.x *= -1;
            this->velocity_.x *= -1;
        }  
        if(bottom_wall_collide || top_wall_collide)
        {
            this->acceleration_.y *= -1;
            this->velocity_.y *= -1;
        }
        this->time_since_accel -= tick;     
    }
    this->velocity_ += this->acceleration_ * dt;
}

void Creature::SetAcceleration(sf::Vector2f acceleration)
{
    this->acceleration_ = acceleration;
}

void Creature::Move(float dt)
{
    this->Accelerate(dt);
    float vmax = this->settings_->vmax;
    if(this->velocity_.length() >= vmax) this->velocity_ = vmax * this->velocity_.normalized();
    this->field_position_ += this->velocity_ * dt;
    this->BounceOffWall();
}

void Creature::Sound()
{
    std::cout << this->sound_ << "\n";
}

void Creature::Sleep()
{

}

void Creature::Mate(Creature& creature1, Creature& creature2, const Settings& settings, Field& field)
{
    if(creature1.Libido() >= creature1.LibidoThreshold() &&
       creature2.Libido() >= creature2.LibidoThreshold())
    {
        SpeciesRole role = creature1.GetSpeciesRole();
        sf::Vector2f birth_position = (creature1.FieldPosition() + creature2.FieldPosition()) * 0.5f;
        const sf::Texture& sheet = field.Assets().getTexture("sheet");
        field.GetCreatures().emplace_back(settings, sheet, role, 
            birth_position,
            sf::Vector2f({0.f, 0.f}));
        creature1.SetLibido(0.f);
        creature2.SetLibido(0.f);
    } else {
        //std::cout << "*sigh* no baby\n";
    }  
}

void Creature::SetLibido(float libido)
{
    this->libido_ = 0.f;
}
// sf::Vector2f Creature::Velocity()
// {
//     return this->velocity_; // default
// }

void Creature::SetVelocity(sf::Vector2f velocity)
{
    this->velocity_ = velocity;
}

// sf::Vector2f Creature::FieldPosition()
// {
//     return this->field_position_; // default 
// }

sf::Time Creature::TimeBorn()
{
    return this->timeborn_;
}

sf::Time Creature::Age()
{
    return this->age_;
}

// float Creature::DistanceSq(Creature& c1, Creature& c2)
// {
//     sf::Vector2f dp = c2.FieldPosition() - c1.FieldPosition();
//     return dp.lengthSquared();
// }

sf::Angle Creature::AngleFromTo(Creature& c1, Creature& c2)
{
    return c1.FieldPosition().angleTo(c2.FieldPosition());
}

void Creature::update(float dt)
{
    this->Accelerate(dt);
    this->Move(dt);
    this->SetFieldPosition(this->field_position_);
    this->fullness_ = std::max(this->fullness_ - this->starve_rate_*dt, 0.f);
    this->libido_ = std::max(this->libido_ + this->libido_rate_*dt, 0.f);
    //float walk_rate = 1*this->Speed()/20;
    float walk_rate = 1.f*this->velocity_.length()/20;
    float total_time_prev = this->total_time_;
    float mod_time_prev = std::fmod(total_time_prev, 1/walk_rate);
    this->total_time_ = std::min(this->total_time_+dt, static_cast<float>(1e9));
    float mod_time = std::fmodf(total_time_, 1/walk_rate);
    if (mod_time <= mod_time_prev) this->frame_++;
    if(this->fullness_ <= 0) this->alive_ = false;
}

sf::Sprite& Creature::GetSprite()
{
    return this->sprite_;
}

SpeciesRole Creature::GetSpeciesRole() const noexcept
{
    return this->role_;
}

void Creature::SetSpriteOrigin(sf::Vector2f origin)
{
    this->sprite_.setOrigin(origin);
}

void Creature::SetSpritePosition(sf::Vector2f position)
{
    // set sprite orientation (direction, face)
    this->face_ = this->velocity_.x >= 0 ? Face::Right : Face::Left; // faces horizontal direction
    if (abs(this->velocity_.x) > abs(this->velocity_.y)) this->direction_ = Direction::Side; // sprite is moving "more" horizontally
    else this->direction_ = this->velocity_.y >= 0 ? Direction::Up : Direction::Down; // otherwise moving vertically, now pick a direction
    
    this->scale_.x = this->settings_->scale_factor * static_cast<int>(this->face_);
    this->SetSpriteScale(this->scale_);
    this->sprite_.setTextureRect(frameRect(*this->settings_, this->role_, this->direction_, this->frame_));
    this->sprite_.setPosition(position);
}

void Creature::SetSpriteScale(sf::Vector2f scale)
{
    // this->sprite_.setScale({static_cast<float>(scale.x), static_cast<float>(scale.y)});
    this->sprite_.setScale(scale);
}

void Creature::SetFieldPosition(sf::Vector2f position)
{
    //this->field_position_ = position;
    sf::Vector2f adjusted_position = Field::FieldToScreenTX(position, this->settings_->screen_extrema, this->settings_->field_extrema);
    SetSpritePosition(adjusted_position);
}

void Creature::BounceOffWall()
{
    const float xmin = this->settings_->field_extrema.at(0);
    const float xmax = this->settings_->field_extrema.at(1);
    const float ymin = this->settings_->field_extrema.at(2);
    const float ymax = this->settings_->field_extrema.at(3);
    // X axis
    if (field_position_.x < xmin) {
        field_position_.x = xmin + (xmin - field_position_.x); // mirror back in
        velocity_.x = std::abs(velocity_.x);                   // head right
    } else if (field_position_.x > xmax) {
        field_position_.x = xmax - (field_position_.x - xmax);
        velocity_.x = -std::abs(velocity_.x);                  // head left
    }

    // Y axis
    if (field_position_.y < ymin) {
        field_position_.y = ymin + (ymin - field_position_.y);
        velocity_.y = std::abs(velocity_.y);                   // head down (or up if your +y is up)
    } else if (field_position_.y > ymax) {
        field_position_.y = ymax - (field_position_.y - ymax);
        velocity_.y = -std::abs(velocity_.y);
    }        
}

void Creature::SetFace(Face face) {
    this->face_ = face;
}