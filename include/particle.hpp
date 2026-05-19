#pragma once
#include <vector_math.hpp>

class Particle {
public:
    Vector2 position;
    Vector2 velocity;
    float lifetime;

    Particle(const Vector2& pos, const Vector2& vel, float life)
        : position(pos), velocity(vel), lifetime(life) {}

    void update(float deltaTime) {
        position = position + velocity * deltaTime;
        lifetime -= deltaTime;
    }

    bool isAlive() const {
        return lifetime > 0;
    }
};