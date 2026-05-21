#include <iostream>
#include <algorithm>
#include "raylib.h"
#include "../include/cloth_manager.hpp"
#include "../include/optimizer.hpp"

int main() {
    int gridWidth = 20;
    int gridHeight = 20;
    float space = 1.0f;

    ClothManager cloth(gridWidth, gridHeight, space, 0.0f, 0.0f, 0.0f);

    float targetAltitude = -30.0f; 
    int epochs = 150;
    float learningRate = 0.0000001f;
    int stepsToSettle = 400;

    std::cout << "Starting Gradient Descent..." << std::endl;
    Optimizer::runGradientDescent(cloth, targetAltitude, epochs, learningRate, stepsToSettle, gridWidth, gridHeight);
    std::cout << "Optimization Complete! Opening Visualizer..." << std::endl;

    InitWindow(1920, 1080, "Mass Spring Cloth");
    SetTargetFPS(60);

    // Calculate the physical dimensions of the cloth in world space
    float totalClothWidth = (gridWidth - 1) * space;
    float totalClothHeight = (gridHeight - 1) * space;

    // Find the center point
    float targetCenterX = totalClothWidth / 2.0f;
    float targetCenterY = -totalClothHeight / 2.0f; 

    // Calculate how far back the camera needs to be on the Z-axis
    // Multiplying the largest dimension by 1.5 leaves a nice margin around the edges
    float maxDimension = std::max(totalClothWidth, totalClothHeight);
    float cameraDistanceZ = maxDimension * 1.5f;

    Camera3D camera = { 0 };
    camera.position = (Vector3){ targetCenterX, targetCenterY, cameraDistanceZ };
    camera.target = (Vector3){ targetCenterX, targetCenterY, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float timeStep = 0.016f;
    int subSteps = 10;
    float subTimeStep = timeStep / subSteps;

    while (!WindowShouldClose()) {
        for(int i = 0; i < subSteps; i++) {
            cloth.simulateStep(subTimeStep);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        for (const auto& spring : cloth.clothSprings) {
            Vec3 pA = cloth.clothParticles[spring.indexA].currentPosition;
            Vec3 pB = cloth.clothParticles[spring.indexB].currentPosition;

            Color lineColor = BLACK;
            if (spring.restLength > space * 1.1f && spring.restLength < space * 1.5f) {
                lineColor = RED;
            } else if (spring.restLength > space * 1.9f) {
                lineColor = GREEN;
            }

            Vector3 rA = { pA.x, pA.y, pA.z };
            Vector3 rB = { pB.x, pB.y, pB.z };
            DrawLine3D(rA, rB, lineColor);
        }

        for (const auto& particle : cloth.clothParticles) {
            Vector3 pos = { particle.currentPosition.x, particle.currentPosition.y, particle.currentPosition.z };
            DrawSphere(pos, 0.1f, BLUE);
        }

        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}