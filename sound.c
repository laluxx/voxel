#include "sound.h"
#include "player.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

Sound stoneDigSounds[8];

void initSounds() {
    InitAudioDevice();
    stoneDigSounds[0] = LoadSound("./assets/stonedig1.ogg");
    stoneDigSounds[1] = LoadSound("./assets/stonedig1shift.ogg");
    stoneDigSounds[2] = LoadSound("./assets/stonedig2.ogg");
    stoneDigSounds[3] = LoadSound("./assets/stonedig2shift.ogg");
    stoneDigSounds[4] = LoadSound("./assets/stonedig3.ogg");
    stoneDigSounds[5] = LoadSound("./assets/stonedig3shift.ogg");
    stoneDigSounds[6] = LoadSound("./assets/stonedig4.ogg");
    stoneDigSounds[7] = LoadSound("./assets/stonedig4shift.ogg");
    srand(time(NULL)); // Initialize random seed
}

void playDigSound() {
    int randomIndex = rand() % 8; // Get a random index between 0 and 7
    PlaySound(stoneDigSounds[randomIndex]);
}


float calculateVolume(Vector3 soundPosition, Vector3 listenerPosition) {
    float distance = Vector3Distance(soundPosition, listenerPosition);
    float maxDistance = 50.0f;  // Adjust as needed
    float minVolume = 0.0f;
    float maxVolume = 1.0f;

    float volume = maxVolume * (1.0f - (distance / maxDistance));
    if (volume < minVolume) volume = minVolume;
    return volume;
}

float calculatePanning(Vector3 soundPosition, Vector3 listenerPosition) {
    Vector3 direction = Vector3Subtract(soundPosition, listenerPosition);
    float angle = atan2f(direction.z, direction.x);  // Angle in radians
    float pan = sinf(angle);  // Panning based on the angle

    // Clamp the pan value to [-1, 1]
    if (pan < -1.0f) pan = -1.0f;
    if (pan > 1.0f) pan = 1.0f;
    return pan;
}

void freeSounds() {
    for (int i = 0; i < 8; i++) {
        UnloadSound(stoneDigSounds[i]);
    }
    CloseAudioDevice();
}
