#include "../include/particle.hpp"

Particle::Particle(float startX, float startY, float startZ, bool pinned){
    currentPosition = {startX, startY, startZ};
    previousPosition = {startX, startY, startZ};
    currentAcceleration = {0.0f,0.0f, 0.0f};

    particleMass = 1.0f;
    isPinned = pinned;
}

void Particle::applyExternalForce(Vec3 forceVector){
    if(!isPinned){
        Vec3 acceleration = forceVector * (1.0/particleMass);
        currentAcceleration.x += acceleration.x;
        currentAcceleration.y += acceleration.y;
        currentAcceleration.z += acceleration.z;
    }
}

void Particle::update(float timeStep){
    if(isPinned){
        return;
    }

    float damping = 0.999f;

    Vec3 deltaX = currentPosition - previousPosition;
    previousPosition = currentPosition;


    // Verlet formula
    // currentPosition.x += deltaX.x + currentAcceleration.x*(timeStep*timeStep);
    // currentPosition.y += deltaX.y + currentAcceleration.y*(timeStep*timeStep);
    // currentPosition.z += deltaX.z + currentAcceleration.z*(timeStep*timeStep);

    currentPosition = currentPosition + deltaX * damping + (currentAcceleration*(timeStep*timeStep));

    //testing this out
    currentAcceleration = {0.0f, 0.0f, 0.0f};
}