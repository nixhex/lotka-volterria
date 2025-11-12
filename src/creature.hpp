#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <unordered_map>
#include <random>
#include "constants.hpp"
#include "settings.hpp"

class Field;

class Creature
{
public:
    Creature(
        const Settings&, 
        const sf::Texture&, 
        SpeciesRole, 
        sf::Vector2f initial_position, 
        sf::Vector2f initial_velocity);
    Creature(const Settings&, const sf::Texture&, SpeciesRole);

    // allow moving (needed by vector erase etc.)
    Creature(Creature&&) noexcept = default;
    Creature& operator=(Creature&&) noexcept = default;
    
    // forbid copying
    Creature(const Creature&) = delete;
    Creature& operator=(const Creature&) = delete;
    
    std::string Species();
    void Eat();
    void Accelerate(float);
    void SetAcceleration(sf::Vector2f);
    void Move(float);
    void Sound();
    void Sleep();
    static void Mate(Creature&, Creature&, const Settings&, Field&);
    void Die();
    float Fullness() noexcept { return fullness_; };
    float Libido() noexcept { return libido_; };
    float LibidoRate() noexcept { return libido_rate_; }
    float MaxLibido() noexcept { return max_libido_; };
    void SetLibido(float);
    float LibidoThreshold() noexcept { return libido_threshold_; };
    sf::Vector2f Velocity() noexcept { return velocity_; };
    void SetVelocity(sf::Vector2f);
    sf::Vector2f FieldPosition() noexcept { return field_position_; };
    sf::Time TimeBorn();
    sf::Time Age();
    static float DistanceSq(Creature& c1, Creature& c2) noexcept {
        sf::Vector2f dp = c2.FieldPosition() - c1.FieldPosition();
        return dp.lengthSquared();
    };
    sf::Angle AngleFromTo(Creature&, Creature&);
    sf::Sprite& GetSprite();
    SpeciesRole GetSpeciesRole() const noexcept;
    void SetSpriteOrigin(sf::Vector2f);
    void SetSpritePosition(sf::Vector2f);
    void SetSpriteScale(sf::Vector2f);
    void SetFieldPosition(sf::Vector2f);
    void BounceOffWall();
    void SetFace(Face);
    // draw and animate
    void update(float);
    void draw(sf::RenderTarget& rt) const { rt.draw(sprite_); }
    //static void Kill(Creature&, Creature&);
    bool IsAlive() const noexcept { return this->alive_; }
    //void Kill() noexcept { this->alive_ = false; };
    void Kill(Creature&, Field&); // takes in the meal as the arg, replenishes fullness to max
    //sf::Texture Texture() noexcept { return this->texture_; };
protected:
    std::string species_;
    float fullness_ = 10.f; // max 10.f
    float libido_ = 0.f; // max 10.f
    //std::array<float, 2> velocity_;
    sf::Vector2f acceleration_ = {0.f, 0.f};
    sf::Vector2f velocity_ = {0.f, 0.f};
    sf::Vector2f field_position_ = {0.f, 0.f};
    sf::Vector2f scale_ = {1.f, 1.f};
    //std::array<float, 2> position_;
    sf::Time timeborn_;
    sf::Time age_;
    sf::Time time_move_start_;
    std::string sound_;
    //sf::Texture texture_;
    sf::Sprite sprite_;
    const Settings* settings_ = nullptr; // non-owning pointer
    SpeciesRole role_;
    bool sprite_mirrored_ = false;
    Direction direction_;
    Face face_;
    int frame_=0;
    float total_time_=0.f;
    sf::Clock accel_clock;
    float time_since_accel = 0.f;
    std::mt19937 rng_{ std::random_device{}() }; // seed RNG once instead of every tick
    bool alive_ = true;
    float starve_rate_ = 1.f; // one unit of hunger per second 
    float libido_rate_ = 1.f; // one unit of libido per second
    float max_libido_ = 10.f;
    float libido_threshold_ = 3.f; // must be above this to mate
};

