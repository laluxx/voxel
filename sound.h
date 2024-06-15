#ifndef SOUND_H
#define SOUND_H

#include <raylib.h>
#include "player.h"

extern Sound stoneDigSounds[8];

void initSounds();
void playDigSound3D(Vector3 soundPosition, Player *player);
void playDigSound();
void freeSounds();

float calculateVolume(Vector3 soundPosition, Vector3 listenerPosition);
float calculatePanning(Vector3 soundPosition, Vector3 listenerPosition);


#endif // SOUND_H
