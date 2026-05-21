#include "../include/cloth_manager.hpp"

ClothManager::ClothManager(int width, int height, float space, float startX, float startY, float startZ){
    gravityAcceleration = {0.0f, -9.8f, 0.0f};

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            bool pinned = (y == 0);
            clothParticles.push_back(Particle(startX + space*x, startY + space*y, startZ, pinned));
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
        Vec3 direction = deltaPos * (1/currentDistance);
        Vec3 appliedForce = direction * forceMagnitude;

        pA.applyExternalForce(appliedForce * (-1));

        pB.applyExternalForce(appliedForce);


        Vec3 directGrad = direction * (currentDistance - spring.restLength);

        Vec3 deltaPosGrad = pA.posGrad - pB.posGrad;
        float dotProduct = direction.dot(deltaPosGrad);

        Vec3 term1 = direction * dotProduct;
        Vec3 term2 = (deltaPosGrad - term1) * ((currentDistance - spring.restLength)/ currentDistance);
        Vec3 spatialGrad = (term1 + term2) * spring.springConstant;
        Vec3 totalForceGrad = directGrad + spatialGrad;

        pA.applyGradientForce(totalForceGrad * (-1));
        pB.applyGradientForce(totalForceGrad);

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


void ClothManager::resetSimulation(){
    for(auto& particle : clothParticles){
        particle.resetState();
    }
}



