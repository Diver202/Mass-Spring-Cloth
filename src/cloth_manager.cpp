#include "../include/cloth_manager.hpp"

ClothManager::ClothManager(int width, int height, float space, float startX, float startY, float startZ){
    gravityAcceleration = {0.0f, -9.8f, 0.0f};

    for(int i = 0; i<width; i++){
        for(int j = 0; j<height; j++){
            bool pinned = (j==0);
            clothParticles.push_back(Particle(startX + space*i, startY + space*j, startZ, pinned));
        }
    }

    float stiffness = 100.0f;

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int currentIndex = y * width + x;

            if(x < width - 1) {
                clothSprings.push_back(Spring(currentIndex, currentIndex + 1, space, stiffness));
            }
            if(y < height - 1) {
                clothSprings.push_back(Spring(currentIndex, currentIndex + width, space, stiffness));
            }

            float shearSpace = space * 1.414f; 
            if(x < width - 1 && y < height - 1) {
                clothSprings.push_back(Spring(currentIndex, currentIndex + width + 1, shearSpace, stiffness));
            }
            if(x > 0 && y < height - 1) {
                clothSprings.push_back(Spring(currentIndex, currentIndex + width - 1, shearSpace, stiffness));
            }

            float bendSpace = space * 2.0f;
            if(x < width - 2) {
                clothSprings.push_back(Spring(currentIndex, currentIndex + 2, bendSpace, stiffness));
            }
            if(y < height - 2) {
                clothSprings.push_back(Spring(currentIndex, currentIndex + width * 2, bendSpace, stiffness));
            }
        }
    }

}

void ClothManager::applySpringForces(){
    for(const auto& spring:clothSprings){
        Particle& pA = clothParticles[spring.indexA];
        Particle& pB = clothParticles[spring.indexB];

        Vec3 deltaPos = pA.currentPosition - pB.currentPosition;
        float currentDistance = deltaPos.magnitude();


        if(currentDistance == 0){
            continue;
        }

        float forceMagnitude = spring.springConstant * (currentDistance - spring.restLength);

        Vec3 appliedForce = deltaPos * (1/currentDistance) * forceMagnitude;

        pA.applyExternalForce(appliedForce * (-1));

        pB.applyExternalForce(appliedForce);



    }
}


void ClothManager:: simulateStep(float timeStep){
    for(auto& particle: clothParticles){
        particle.applyExternalForce(gravityAcceleration * particle.particleMass);
    }

    applySpringForces();

    for(auto& particle: clothParticles){
        particle.update(timeStep);
    }
}



