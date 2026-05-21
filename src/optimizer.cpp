#include "../include/optimizer.hpp"
#include <iostream>

void Optimizer::runGradientDescent(ClothManager& cloth,
                                    float targetY,
                                    int epochs,
                                    float learningRate,
                                    int simulationSteps,
                                    int gridWidth,
                                    int gridHeight){

    int bottomIndex = (gridHeight - 1) * gridWidth + gridWidth/2;

    int subSteps = 10;
    float timeStep = 0.016f / subSteps;
    int totalSteps = simulationSteps * subSteps;

    for(int epoch = 0; epoch < epochs; epoch++){
        cloth.resetSimulation();

        for(int i = 0; i < totalSteps; i++){
            cloth.simulateStep(timeStep);
        }

        Particle& targetParticle = cloth.clothParticles[bottomIndex];
        float currentY = targetParticle.currentPosition.y;
        float dyDk = targetParticle.posGrad.y;

        float loss = (currentY - targetY) * (currentY - targetY)/2.0f;
        float lossGradient = (currentY - targetY) * dyDk;

        // --- GRADIENT CLIPPING ---
        // Prevents chaotic spikes from breaking the optimization
        float maxGradientLimit = 500.0f; 
        if (lossGradient > maxGradientLimit) {
            lossGradient = maxGradientLimit;
        } else if (lossGradient < -maxGradientLimit) {
            lossGradient = -maxGradientLimit;
        }

        float currentK = cloth.clothSprings[0].springConstant;
        currentK = currentK - (learningRate * lossGradient);

        if(currentK < 10.0f){
            currentK = 10.0f;
        }

        for(auto& spring: cloth.clothSprings){
            spring.springConstant = currentK;
        }
        
        std::cout << "Epoch: " << epoch 
                  << " | Stiffness: " << currentK 
                  << " | Current Y: " << currentY 
                  << " | Loss: " << loss << std::endl;
    }

    cloth.resetSimulation();
}