#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "world.h" // for the ray ? 

extern float jumpSpeed;
extern float fallingVelocityExponentialFactor;
extern float speed;
extern float noclipSpeed;
extern float playerHeight;
extern float eyeLevelFactor;
extern float sensitivity;

typedef struct {
    Vector3 position;
    float height;
    Vector3 speed;
    float jumpSpeed;
    bool isOnGround;
    bool noclip;
} Player;

void initPlayer(Player *player);
void updatePlayer(Player *player);
bool GetBlockAtRay(World *world, Ray ray, Vector3 *blockPosition,
                   Vector3 *hitPosition, Vector3 *normal);


#endif  // PLAYER_H
