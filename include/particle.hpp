#pragma once
#include "vector_math.hpp"

class Particle {
public:

    //position and accelration
    Vec3 currentPosition;
    Vec3 previousPosition;
    Vec3 initialPosition;
    Vec3 currentAcceleration;


    // For gradient tracking 
    Vec3 posGrad;
    Vec3 prevPosGrad;
    Vec3 accGrad;
    
    float particleMass;
    bool isPinned;

    Particle(float startX, float startY, float startZ, bool pinned);

    void applyExternalForce(Vec3 forceVector);
    void applyGradientForce(Vec3 gradVector);
    void update(float timeStep);
    void resetState();
};