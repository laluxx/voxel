#include "player.h"
#include "world.h"
#include <float.h>
#include <raymath.h>

// NOTE Why does the player require the world ? 
float jumpSpeed = 26.26f;
float fallingVelocityExponentialFactor = 1.0f;
float sensitivity = 0.0005f;
float speed = 10.0f;
float noclipSpeed = 20.0f;
float playerHeight = 2.0f;
float eyeLevelFactor = 1.0f;

void initPlayer(Player *player) {
    player->position = (Vector3){0.0f, 1.0f, 0.0f};
    player->jumpSpeed = 0.0f;
    player->isOnGround = true;
    player->height = playerHeight;
    player->noclip = false;
}

void updatePlayer(Player *player) {
    if (!player->noclip) {
        if (!player->isOnGround) {
            player->position.y += player->jumpSpeed * GetFrameTime();
            player->jumpSpeed += g * GetFrameTime();

            if (player->jumpSpeed < 0) {
                player->jumpSpeed *= fallingVelocityExponentialFactor;
            }

            if (player->position.y <= groundHeight) {
                player->position.y = groundHeight;
                player->jumpSpeed = 0;
                player->isOnGround = true;
            }
        }
    }
}

bool GetBlockAtRay(World *world, Ray ray, Vector3 *blockPosition, Vector3 *hitPosition, Vector3 *normal) {
    float minDistance = FLT_MAX;
    bool hit = false;

    for (int x = 0; x < world->width; x++) {
        for (int y = 0; y < world->height; y++) {
            for (int z = 0; z < world->depth; z++) {
                Block block = world->blocks[x][y][z];
                if (!block.active) continue;

                BoundingBox box = {
                    .min = Vector3Subtract(block.position, (Vector3){block.size / 2, block.height / 2, block.size / 2}),
                    .max = Vector3Add(block.position, (Vector3){block.size / 2, block.height / 2, block.size / 2})
                };

                RayCollision hitInfo = GetRayCollisionBox(ray, box);
                if (hitInfo.hit && hitInfo.distance < minDistance) {
                    minDistance = hitInfo.distance;
                    *blockPosition = block.position;
                    *hitPosition = hitInfo.point;
                    *normal = hitInfo.normal;
                    hit = true;
                }
            }
        }
    }

    return hit;
}



