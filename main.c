#include "font.h"
#include "grid.h"
#include "raylib.h"
#include "raymath.h"
#include "sound.h"
#include "theme.h"
#include "player.h"
#include "world.h"
#include "camera.h"
#include "fzy.h"
#include "light.h"
#include "grid.h"
#include "sound.h"
#include <stdio.h>

// TODO IMPORTANT C jit using llvm
// TODO 3D block placing sound effect 
// TODO skybox
// TODO block selection highlight
// TODO frustum culling
// TODO fix camera
// TODO Greedy mesh
// TODO Apply texture to blocks
// TODO init blocks
// TODO Animate block deletion
// TODO animate block insertion
// TODO Increment variables int he menu using lerp functions

int sw = 1920;
int sh = 1080;

void init(Player *player, Camera *camera, World *world);
void handleInput(Player *player, Camera *camera, World *world);
void handleKeys(Player *player, Camera *camera);
void handleMouse(Camera *camera, World *world);
void drawCrosshair();
void draw(Camera *camera, World *world);

void initShadersAndTextures(RenderTexture2D *target, Shader *blurShader, int *blurLoc);
void updateBlurAmount(Player *player, Shader blurShader, int blurLoc);

bool showEditor = false;
bool quit = false;
Player player = {0};
Camera camera = {0};

int main(void) {
    World world = {0};

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(144);
    InitWindow(sw, sh, "Voxel Game - Raylib");
    SetExitKey(0);
    DisableCursor();

    initThemes();
    init(&player, &camera, &world);

    while (quit == false) {
        updateLight();
        handleInput(&player, &camera, &world);
        updatePlayer(&player);
        updateCameraPosition(&camera, &player);
        draw(&camera, &world);
        /* playDigSound3D((Vector3){0.0, 0.0, 5.0}, &player); */
    }

    CloseWindow();
    freeSounds();
    freeGrid(&cellGrid);
    return 0;
}

void init(Player *player, Camera *camera, World *world) {
    initSounds();
    int rows = GetScreenHeight() / fontSize;
    int cols = GetScreenWidth() / fontSize;
    initGrid(&cellGrid, rows, cols, fontSize, fontSize);
    

    initFzy(fzyItems, fzyItemCount);
    initFonts();
    initWorld(world);
    initPlayer(player);
    initCamera(player, camera);
    initLight();
}

void handleKeys(Player *player, Camera *camera) {

    // TODO moveme
    if (IsKeyPressed(KEY_V)) {
        fzy.showFzy = !fzy.showFzy;
    }
    
    if (IsKeyPressed(KEY_Q)) {
        quit = true;
    }


    if (IsKeyPressed(KEY_TAB)) {
        player->noclip = !player->noclip;
        showEditor = !showEditor;
    }

    float moveSpeed = player->noclip ? noclipSpeed * GetFrameTime() : speed * GetFrameTime();

    Vector3 forward = Vector3Normalize(Vector3Subtract(camera->target, camera->position));
    Vector3 right = Vector3CrossProduct(forward, camera->up);
    right = Vector3Normalize(right);

    if (player->noclip) {
        // Noclip movement
        if (IsKeyDown(KEY_W)) player->position = Vector3Add(player->position, Vector3Scale(forward, moveSpeed));
        if (IsKeyDown(KEY_S)) player->position = Vector3Subtract(player->position, Vector3Scale(forward, moveSpeed));
        if (IsKeyDown(KEY_A)) player->position = Vector3Subtract(player->position, Vector3Scale(right, moveSpeed));
        if (IsKeyDown(KEY_D)) player->position = Vector3Add(player->position, Vector3Scale(right, moveSpeed));
        if (IsKeyDown(KEY_SPACE)) player->position.y += moveSpeed;
        if (IsKeyDown(KEY_LEFT_SHIFT)) player->position.y -= moveSpeed;
        /* printf("Player Position X:%f Y:%f Z:%f\n", player->position.x, player->position.y, player->position.z); */
    } else {
        // Regular movement
        forward.y = 0.0f; // Keep movement on the horizontal plane when not in noclip
        forward = Vector3Normalize(forward);

        if (IsKeyDown(KEY_W)) player->position = Vector3Add(player->position, Vector3Scale(forward, moveSpeed));
        if (IsKeyDown(KEY_S)) player->position = Vector3Subtract(player->position, Vector3Scale(forward, moveSpeed));
        if (IsKeyDown(KEY_A)) player->position = Vector3Subtract(player->position, Vector3Scale(right, moveSpeed));
        if (IsKeyDown(KEY_D)) player->position = Vector3Add(player->position, Vector3Scale(right, moveSpeed));

        if (IsKeyPressed(KEY_SPACE) && player->isOnGround) {
            player->jumpSpeed = jumpSpeed;
            player->isOnGround = false;
        }
        /* printf("Player Position X:%f Y:%f Z:%f\n", player->position.x, player->position.y, player->position.z); */
    }
}


void handleMouse(Camera *camera, World *world) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        Ray ray = {camera->position, Vector3Normalize(Vector3Subtract(camera->target, camera->position))};

        Vector3 blockPosition, hitPosition, normal;

        if (GetBlockAtRay(world, ray, &blockPosition, &hitPosition, &normal)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int x = (int)(blockPosition.x + groundSize);
                int y = (int)blockPosition.y;
                int z = (int)(blockPosition.z + groundSize);

                if (x >= 0 && x < world->width && y >= 0 && y < world->height && z >= 0 && z < world->depth) {
                    world->blocks[x][y][z].active = false;
                }

                playDigSound();
                printf("Block position X:%f Y:%f Z:%f\n", blockPosition.x, blockPosition.y, blockPosition.z);
                
                
            } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                Vector3 newBlockPosition = Vector3Add(blockPosition, normal);
                int x = (int)(newBlockPosition.x + groundSize);
                int y = (int)newBlockPosition.y;
                int z = (int)(newBlockPosition.z + groundSize);

                if (x >= 0 && x < world->width && y >= 0 && y < world->height && z >= 0 && z < world->depth) {
                    world->blocks[x][y][z].active = true;
                }
            }
        }
    }
}

void handleInput(Player *player, Camera *camera, World *world) {
    if (IsKeyPressed(KEY_EQUAL) && IsKeyDown(KEY_LEFT_CONTROL)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            cellScale += 0.5f;                    
        } else {
            verticalSpacing++;
        }
    }

    if (IsKeyPressed(KEY_MINUS) && IsKeyDown(KEY_LEFT_CONTROL)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            cellScale -= 0.5f;                    
        } else {
            verticalSpacing--;
        }
    }

    if (IsKeyPressed(KEY_EQUAL) && IsKeyDown(KEY_LEFT_ALT)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            textScale += 0.1f;
        } else {
            horizontalSpacing++;            
        }
    }
    
    if (IsKeyPressed(KEY_MINUS) && IsKeyDown(KEY_LEFT_ALT)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            textScale -= 0.1f;
        } else {
            horizontalSpacing--;            
        }
    }


    if (IsKeyPressed(KEY_RIGHT_BRACKET) && IsKeyDown(KEY_LEFT_ALT)) {nextTheme();}
    if (IsKeyPressed(KEY_LEFT_BRACKET) && IsKeyDown(KEY_LEFT_ALT)) {previousTheme();}

    if (IsKeyPressed(KEY_G) && IsKeyDown(KEY_LEFT_CONTROL)) {
        showGrid = !showGrid;
    }

    if (fzy.showFzy) {
        handleFzyInput();
    } else {
        handleKeys(player, camera);
        handleMouse(camera, world);
    }
}

void drawCrosshair() {
    int centerX = sw / 2;
    int centerY = sh / 2;
    int crosshairSize = 10;

    DrawLine(centerX - crosshairSize, centerY, centerX + crosshairSize, centerY, CT.accent);
    DrawLine(centerX, centerY - crosshairSize, centerX, centerY + crosshairSize, CT.accent);
}

void draw(Camera *camera, World *world) {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(*camera);
    drawWorld(world);
    EndMode3D();
    drawCrosshair();
    DrawFPS(10, 10);
    drawFzy();
    

    EndDrawing();
}
