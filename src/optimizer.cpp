#include "../include/optimizer.hpp"
#include <iostream>

void Optimizer::runGradientDescent(ClothManager& cloth,
                                    float targetY,
                                    int epochs,
                                    float lr,
                                    int simulationSteps,
                                    int gridWidth,
                                    int gridHeight){

    int bottomIndex = (gridHeight - 1) * gridWidth + gridWidth/2;

    float timeStep = 0.016f;

    for(int epoch = 0; epoch<epochs; epoch++){
        cloth.resetSimulation();

        for(int i = 0; i< simulationSteps; i++){
            cloth.simulateStep(timeStep);
        }

        Particle& targetParticle = cloth.clothParticles[bottomIndex];
        float currentY = targetParticle.currentPosition.y;
        float dyDk = targetParticle.posGrad.y;

        float loss = (currentY - targetY) * (currentY - targetY)/2;
        float lossGradient = (currentY - targetY) * dyDk;

        float currentK = cloth.clothSprings[0].springConstant;
        currentK = currentK - (lr * lossGradient);

        if(currentK < 10){
            currentK = 10;
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

