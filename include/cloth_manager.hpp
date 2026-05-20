#pragma once

#include <vector>
#include "particle.hpp"
#include "spring.hpp"

class ClothManager{
    public:
        std::vector<Particle> clothParticles;
        std::vector<Spring> clothSprings;
        Vec3 gravityAcceleration;

        ClothManager(int width, int height, float space, float startX, float startY, float startZ);

        void applySpringForces();
        void simulateStep(float timeStep);
};

