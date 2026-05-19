#include <../include/particle.hpp>

Particle::Particle(float startX, float startY, float startZ, bool pinned){
    currentPosition = {startX, startY, startZ};
    previousPosition = {startX, startY, startZ};
    acceleration = {0.0f,0.0f, 0.0f};

    particleMass = 1.0f;
    isPinned = pinned;
}