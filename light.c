#include "light.h"
#include "theme.h"

Light light;

void initLight() {
    light.position = (Vector3){0, 4, 0};  // Positioned above the ground at the center
    light.color = CT.accent;
    light.intensity = 1.0f;
}

void updateLight() {
    light.color = CT.accent;
}


