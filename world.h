#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>

extern float g;
extern float blockSize;
extern float blockHeight;
extern int lightIntesityFactor;

#define worldWidth 60
#define worldHeight 60
#define worldDepth 60
#define groundSize 30
#define groundHeight 0.0f

// TODO Add a color to the block
typedef struct {
    Vector3 position;
    float size;
    float height;
    bool active;
} Block;

typedef struct {
    Block blocks[worldWidth][worldHeight][worldDepth];  // NOTE 3D array
    int width;
    int height;
    int depth;
} World;

void initWorld(World *world);
void drawWorld(World *world);


#endif  // WORLD_H
