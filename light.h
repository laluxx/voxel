#ifndef LIGHT_H
#define LIGHT_H

#include <raylib.h>

typedef struct {
    Vector3 position;
    Color color;
    float intensity;
} Light;

extern Light light;
void initLight();
void updateLight();


#endif  // LIGHT_H
