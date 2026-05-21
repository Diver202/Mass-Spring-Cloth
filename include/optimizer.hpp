#pragma once
#include "cloth_manager.hpp"

class Optimizer{
    public:
    static void runGradientDescent(ClothManager& cloth,
                                    float targetY,
                                    int epochs,
                                    float lr,
                                    int simulationSteps,
                                    int gridWidth,
                                    int gridHeight);
};