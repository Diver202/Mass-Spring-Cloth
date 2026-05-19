#include "../include/cloth_manager.hpp"

ClothManager::ClothManager(int width, int height, float space, float startX, float startY, float startZ){
    gravity = {0.0f, -9.8f, 0.0f};

    for(int i = 0; i<width; i++){
        for(int j = 0; j<height; j++){
            bool pinned = (j==0);
            clothParticles.push_back(Particle(startX + space*i, startY + space*j, startZ, pinned))
        }
    }

    float stiffness = 100.0f;

    for(int y = 0; y<height; y++){
        for(int x = 0; x<width; x++){
            
        }
    }

}