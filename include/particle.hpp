#pragma once
#include "vector_math.hpp"

class Particle {
public:
    Vec3 currentPosition;
    Vec3 previousPosition;
    Vec3 currentAcceleration;
    
    float particleMass;
    bool isPinned;

    Particle(float startX, float startY, float startZ, bool pinned);

    void applyExternalForce(Vec3 forceVector);
    void update(float timeStep);
};