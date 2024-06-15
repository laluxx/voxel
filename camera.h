#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>
#include "player.h"

extern float maxPitchAngle;
extern float minPitchAngle;
extern float cameraDistance;
extern float targetDistance;

void initCamera(Player *player, Camera *camera);
void updateCameraPosition(Camera *camera, Player *player);

#endif  // CAMERA_H



