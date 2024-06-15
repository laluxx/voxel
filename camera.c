#include "camera.h"
#include <raymath.h>

float maxPitchAngle = PI / 2.0f - 0.1f;
float minPitchAngle = -PI / 2.0f + 0.1f;
float cameraDistance = 5.0f;
float targetDistance = 10.0f;

void initCamera(Player *player, Camera *camera) {
    // Initialize camera
    camera->position = (Vector3){
        player->position.x,
        player->position.y + player->height * eyeLevelFactor,  // Adjust camera height to eye level
        player->position.z + cameraDistance
    };
    camera->target = Vector3Add(camera->position, (Vector3){0.0f, 0.0f, -1.0f});
    camera->up = (Vector3){0.0f, 1.0f, 0.0f};
    camera->fovy = 45.0f;
    camera->projection = CAMERA_PERSPECTIVE;
}

void updateCameraPosition(Camera *camera, Player *player) {
    static float angleYaw = 0.0f;
    static float anglePitch = 0.0f;

    // Update camera based on mouse movement
    Vector2 mouseDelta = GetMouseDelta();
    float sens = sensitivity;
    angleYaw += sens * -mouseDelta.x;
    anglePitch += sens * -mouseDelta.y;
    if (anglePitch > maxPitchAngle) anglePitch = maxPitchAngle;
    if (anglePitch < minPitchAngle) anglePitch = minPitchAngle;

    // Calculate direction vector
    Vector3 direction = Vector3Normalize((Vector3){
        cos(anglePitch) * sin(angleYaw),
        sin(anglePitch),
        cos(anglePitch) * cos(angleYaw)
    });

    // Update camera position
    camera->position = (Vector3){
        player->position.x,
        player->position.y + player->height * eyeLevelFactor,  // Eye level
        player->position.z
    };
    camera->target = Vector3Add(camera->position, direction);
}

