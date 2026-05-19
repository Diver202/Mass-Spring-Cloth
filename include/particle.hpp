#pragma once
#include <vector_math.hpp>

class Particle {
public:
    Vector3 currentPosition;
    Vector3 previousPosition;
    Vector3 acceleration;
    
    float particleMass;
    bool isPinned;

    Particle(float startX, float startY, float startZ, bool isPinned);

    void applyExternalForce(Vector3 forceVector);
    void update(float timeStep);
};