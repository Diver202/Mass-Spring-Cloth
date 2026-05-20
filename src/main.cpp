#include <iostream>
#include "raylib.h"
#include "../include/cloth_manager.hpp"

int main() {
    InitWindow(800, 600, "Mass Spring Cloth");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 15.0f };
    camera.target = (Vector3){ 5.0f, -5.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float space = 1.0f;
    ClothManager cloth(10, 10, space, 0.0f, 0.0f, 0.0f);
    float timeStep = 0.016f;

    while (!WindowShouldClose()) {
        cloth.simulateStep(timeStep);
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