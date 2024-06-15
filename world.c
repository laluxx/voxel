#include "world.h"
#include <raymath.h>
#include "light.h"

float g = -9.807f;
float blockSize = 1.0f;
float blockHeight = 1.0f;

int lightIntesityFactor = 1;

void drawBlock(Block cube, Light light) {
    // Calculate distance to light
    float distance = Vector3Distance(light.position, cube.position);
    float attenuation = 1.0f / (1.0f + 0.1f * distance * distance);  // Simplified attenuation

    // Calculate final color based on light intensity and attenuation
    Color cubeColor = ColorFromNormalized((Vector4){
        light.color.r * attenuation * light.intensity* lightIntesityFactor / 255.0f,
        light.color.g * attenuation * light.intensity * lightIntesityFactor / 255.0f,
        light.color.b * attenuation * light.intensity * lightIntesityFactor / 255.0f,
        1.0f  // α value
    });

    DrawCube(cube.position, cube.size, cube.height, cube.size, cubeColor);
    DrawCubeWires(cube.position, cube.size, cube.height, cube.size, BLACK);
}

void initWorld(World *world) {
    world->width = worldWidth;
    world->height = worldHeight;
    world->depth = worldDepth;
    
    for (int x = 0; x < world->width; x++) {
        for (int y = 0; y < world->height; y++) {
            for (int z = 0; z < world->depth; z++) {
                world->blocks[x][y][z].position = (Vector3){x * blockSize - groundSize, y * blockHeight, z * blockSize - groundSize};
                world->blocks[x][y][z].size = blockSize;
                world->blocks[x][y][z].height = blockHeight;
                // Set the block to active only if it's at the ground level
                world->blocks[x][y][z].active = (y == 0);
            }
        }
    }
}

void drawWorld(World *world) {
    for (int x = 0; x < world->width; x++) {
        for (int y = 0; y < world->height; y++) {
            for (int z = 0; z < world->depth; z++) {
                Block cube = world->blocks[x][y][z];
                
                if (cube.active) {
                    drawBlock(cube, light);
                }
            }
        }
    }
}


