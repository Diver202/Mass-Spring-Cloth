#include "../include/particle.hpp"

Particle::Particle(float startX, float startY, float startZ, bool pinned){
    initialPosition = {startX, startY, startZ};
    currentPosition = {startX, startY, startZ};
    previousPosition = {startX, startY, startZ};
    currentAcceleration = {0.0f,0.0f, 0.0f};

    posGrad = {0.0f, 0.0f, 0.0f};
    prevPosGrad = {0.0f, 0.0f, 0.0f};
    accGrad = {0.0f, 0.0f, 0.0f};

    particleMass = 1.0f;
    isPinned = pinned;
}

void Particle::resetState(){
    currentPosition = initialPosition;
    previousPosition = initialPosition;

    currentAcceleration = {0.0f, 0.0f, 0.0f};


    posGrad = {0.0f, 0.0f, 0.0f};
    prevPosGrad = {0.0f, 0.0f, 0.0f};
    accGrad = {0.0f, 0.0f, 0.0f};
};

void Particle::applyExternalForce(Vec3 forceVector){
    if(!isPinned){
        Vec3 acceleration = forceVector * (1.0/particleMass);
        currentAcceleration.x += acceleration.x;
        currentAcceleration.y += acceleration.y;
        currentAcceleration.z += acceleration.z;
    }
}

void Particle::applyGradientForce(Vec3 gradVector){
    if(!isPinned){
        Vec3 accGradient = gradVector * (1/particleMass);
        accGrad.x += accGradient.x;
        accGrad.y += accGradient.y;
        accGrad.z += accGradient.z;
    }
}

void Particle::update(float timeStep){
    if(isPinned){
        return;
    }

    float damping = 0.999f;

    Vec3 deltaX = currentPosition - previousPosition;
    previousPosition = currentPosition;
    currentPosition = currentPosition + deltaX * damping + (currentAcceleration*(timeStep*timeStep));
    currentAcceleration = {0.0f, 0.0f, 0.0f};


    Vec3 deltaGrad = posGrad - prevPosGrad;
    prevPosGrad = posGrad;
    posGrad = posGrad + deltaGrad * damping + (accGrad * (timeStep * timeStep));
    accGrad = {0.0f, 0.0f, 0.0f};
}