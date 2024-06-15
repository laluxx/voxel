#include <string.h>
#include "fzy.h"
#include "font.h"
#include "theme.h"
#include <stdio.h>
#include "player.h"
#include "world.h"
#include "camera.h"
#include "grid.h"

// TODO Handle bool variable
// TODO Docstring
// TODO Hadle data structures and draw cool trees

FzyItem fzyItems[] = {
    {"Gravity", TYPE_FLOAT, &g},
    {"Jump Speed", TYPE_FLOAT, &jumpSpeed},
    {"Falling Factor", TYPE_FLOAT, &fallingVelocityExponentialFactor},
    {"Max Pitch Angle", TYPE_FLOAT, &maxPitchAngle},
    {"Min Pitch Angle", TYPE_FLOAT, &minPitchAngle},
    {"Camera Distance", TYPE_FLOAT, &cameraDistance},
    {"Target Distance", TYPE_FLOAT, &targetDistance},
    {"Block Size", TYPE_FLOAT, &blockSize},
    {"Block Height", TYPE_FLOAT, &blockHeight},
    {"Speed", TYPE_FLOAT, &speed},
    {"Sensitivity", TYPE_FLOAT, &sensitivity},
    {"Player Height", TYPE_FLOAT, &playerHeight},
    {"Eye", TYPE_FLOAT, &eyeLevelFactor},
    {"LightFactor", TYPE_INT, &lightIntesityFactor},
};

Fzy fzy;

void initFzy(FzyItem *items, int itemCount) {
    fzy.items = items;
    fzy.itemCount = itemCount;
    fzy.selectedIndex = 0;
    memset(fzy.filterText, 0, sizeof(fzy.filterText));
    fzy.showFzy = false;
    fzy.topFzy = true;
}

int fzyItemCount = sizeof(fzyItems) / sizeof(FzyItem);

void drawFzy() {
    if (fzy.showFzy) {
        clearGrid(&cellGrid);

        // Draw filter text
        for (int i = 0; i < (int)strlen(fzy.filterText); i++) {
            setCell(&cellGrid, 0, i, fzy.filterText[i], CT.text, CT.minibuffer);
        }

        // Draw menu items
        int startRow = 2;
        int leftPadding = 1;
        for (int i = 0; i < fzy.itemCount; i++) {
            if (!strstr(fzy.items[i].name, fzy.filterText)) continue;

            Color bgColor = (i == fzy.selectedIndex) ? CT.accent : CT.modeline;
            Color textColor = (i == fzy.selectedIndex) ? CT.modeline : CT.text;
            const char *name = fzy.items[i].name;
            char valueStr[32];

            if (fzy.items[i].type == TYPE_INT) {
                sprintf(valueStr, "%d", *(int *)fzy.items[i].value);
            } else if (fzy.items[i].type == TYPE_FLOAT) {
                sprintf(valueStr, "%.3f", *(float *)fzy.items[i].value);
            }

            // Set name and value in grid
            for (int j = 0; j < (int)strlen(name); j++) {
                setCell(&cellGrid, startRow + i, leftPadding + j, name[j], textColor, bgColor);
            }
            for (int j = 0; j < (int)strlen(valueStr); j++) {
                setCell(&cellGrid, startRow + i, leftPadding + 20 + j, valueStr[j], textColor, bgColor); // Adjust position as needed
            }
        }

        // Draw the grid
        drawGrid(&cellGrid, jetb);
    }
}

void adjustFzyValue(FzyItem item, float delta) {
    if (item.type == TYPE_INT) {
        *(int *)item.value += (int)delta;
    } else if (item.type == TYPE_FLOAT) {
        *(float *)item.value += delta;
    }
}

void handleFzyInput() {
    if (!fzy.showFzy) return;

    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (strlen(fzy.filterText) < 31)) {
            int len = strlen(fzy.filterText);
            fzy.filterText[len] = (char)key;
            fzy.filterText[len + 1] = '\0';
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && strlen(fzy.filterText) > 0) {
        fzy.filterText[strlen(fzy.filterText) - 1] = '\0';
    }

    if (IsKeyPressed(KEY_BACKSPACE) && IsKeyDown(KEY_LEFT_CONTROL)) {
        memset(fzy.filterText, 0, sizeof(fzy.filterText));
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        fzy.showFzy = !fzy.showFzy;
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_N)) {
        fzy.selectedIndex = (fzy.selectedIndex + 1) % fzy.itemCount;
        while (!strstr(fzy.items[fzy.selectedIndex].name, fzy.filterText)) {
            fzy.selectedIndex = (fzy.selectedIndex + 1) % fzy.itemCount;
        }
    } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_P)) {
        fzy.selectedIndex--;
        if (fzy.selectedIndex < 0) fzy.selectedIndex = fzy.itemCount - 1;
        while (!strstr(fzy.items[fzy.selectedIndex].name, fzy.filterText)) {
            fzy.selectedIndex--;
            if (fzy.selectedIndex < 0) fzy.selectedIndex = fzy.itemCount - 1;
        }
    }

    if ((IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F)) || IsKeyPressed(KEY_RIGHT)) {
        adjustFzyValue(fzy.items[fzy.selectedIndex], 0.1f);
    } else if ((IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B)) || IsKeyPressed(KEY_LEFT)) {
        adjustFzyValue(fzy.items[fzy.selectedIndex], -0.1f);
    }
}




/* // TODO Show variable type */
/* // TODO Ability to modify structs */
/* // TODO icons using font */

/* // TODO IMPORTANT Divide the 2D screen in cells, */
/* // TODO better font rendering in raylib */

/* #include <string.h> */
/* #include "fzy.h" */
/* #include "font.h" */
/* #include "theme.h" */
/* #include <stdio.h> */
/* #include "player.h" */
/* #include "world.h" */
/* #include "camera.h" */


/* FzyItem fzyItems[] = { */
/*     {"Gravity", TYPE_FLOAT, &g}, */
/*     {"Jump Speed", TYPE_FLOAT, &jumpSpeed}, */
/*     {"Falling Factor", TYPE_FLOAT, &fallingVelocityExponentialFactor}, */
/*     {"Max Pitch Angle", TYPE_FLOAT, &maxPitchAngle}, */
/*     {"Min Pitch Angle", TYPE_FLOAT, &minPitchAngle}, */
/*     {"Camera Distance", TYPE_FLOAT, &cameraDistance}, */
/*     {"Target Distance", TYPE_FLOAT, &targetDistance}, */
/*     {"Block Size", TYPE_FLOAT, &blockSize}, */
/*     {"Block Height", TYPE_FLOAT, &blockHeight}, */
/*     {"Speed", TYPE_FLOAT, &speed}, */
/*     {"Sensitivity", TYPE_FLOAT, &sensitivity}, */
/*     {"Player Height", TYPE_FLOAT, &playerHeight}, */
/*     {"Eye", TYPE_FLOAT, &eyeLevelFactor} */
/* }; */

/* Fzy fzy; */

/* void initFzy(FzyItem *items, int itemCount) { */
/*     fzy.items = items; */
/*     fzy.itemCount = itemCount; */
/*     fzy.selectedIndex = 0; */
/*     memset(fzy.filterText, 0, sizeof(fzy.filterText)); */
/*     fzy.showFzy = false; */
/*     fzy.topFzy = true; */
/* } */

/* int fzyItemCount = sizeof(fzyItems) / sizeof(FzyItem); */

/* void drawFzy() { */
/*     if (fzy.showFzy) { */
/*         int menuWidth = GetScreenWidth(); */
/*         int menuHeight = 40 + fzy.itemCount * (fontSize + 6);  // Adjusted for padding */
/*         int menuX = 0; */
/*         int menuY = fzy.topFzy ? 0 : GetScreenHeight() - menuHeight; */

/*         DrawRectangle(menuX, menuY, menuWidth, menuHeight, Fade(CT.modeline, 0.8f)); */
/*         DrawRectangle(menuX, menuY, menuWidth, 31, CT.minibuffer);  // Input area height */

/*         int leftPadding = 10; */
/*         int verticalPadding = (31 - fontSize) / 2; */

/*         DrawTextEx(jetb, fzy.filterText, (Vector2){menuX + leftPadding, menuY + verticalPadding}, fontSize, 2, CT.text); */

/*         menuY += 31; */

/*         for (int i = 0; i < fzy.itemCount; i++) { */
/*             if (!strstr(fzy.items[i].name, fzy.filterText)) continue; */

/*             Color color = (i == fzy.selectedIndex) ? CT.accent : CT.text; */
/*             const char *name = fzy.items[i].name; */
/*             char valueStr[32]; */

/*             if (fzy.items[i].type == TYPE_INT) { */
/*                 sprintf(valueStr, "%d", *(int *)fzy.items[i].value); */
/*             } else if (fzy.items[i].type == TYPE_FLOAT) { */
/*                 sprintf(valueStr, "%.3f", *(float *)fzy.items[i].value); */
/*             } */

/*             verticalPadding = (20 + fontSize) / 2 - fontSize / 2; */

/*             DrawTextEx(jetb, name, (Vector2){menuX + leftPadding, menuY + verticalPadding}, fontSize, 2, color); */
/*             DrawTextEx(jetb, valueStr, (Vector2){menuX + 200, menuY + verticalPadding}, fontSize, 2, color); */

/*             menuY += fontSize + 6; */
/*         } */
/*     } */
/* } */

/* void adjustFzyValue(FzyItem item, float delta) { */
/*     if (item.type == TYPE_INT) { */
/*         *(int *)item.value += (int)delta; */
/*     } else if (item.type == TYPE_FLOAT) { */
/*         *(float *)item.value += delta; */
/*     } */
/* } */

/* void handleFzyInput() { */
/*     if (!fzy.showFzy) return; */

/*     int key = GetCharPressed(); */
/*     while (key > 0) { */
/*         if ((key >= 32) && (key <= 125) && (strlen(fzy.filterText) < 31)) { */
/*             int len = strlen(fzy.filterText); */
/*             fzy.filterText[len] = (char)key; */
/*             fzy.filterText[len + 1] = '\0'; */
/*         } */
/*         key = GetCharPressed(); */
/*     } */

/*     if (IsKeyPressed(KEY_BACKSPACE) && strlen(fzy.filterText) > 0) { */
/*         fzy.filterText[strlen(fzy.filterText) - 1] = '\0'; */
/*     } */

/*     if (IsKeyPressed(KEY_BACKSPACE) && IsKeyDown(KEY_LEFT_CONTROL)) { */
/*         memset(fzy.filterText, 0, sizeof(fzy.filterText)); */
/*     } */

/*     if (IsKeyPressed(KEY_ESCAPE)) { */
/*         fzy.showFzy = !fzy.showFzy; */
/*     } */

/*     if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_N)) { */
/*         fzy.selectedIndex = (fzy.selectedIndex + 1) % fzy.itemCount; */
/*         while (!strstr(fzy.items[fzy.selectedIndex].name, fzy.filterText)) { */
/*             fzy.selectedIndex = (fzy.selectedIndex + 1) % fzy.itemCount; */
/*         } */
/*     } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_P)) { */
/*         fzy.selectedIndex--; */
/*         if (fzy.selectedIndex < 0) fzy.selectedIndex = fzy.itemCount - 1; */
/*         while (!strstr(fzy.items[fzy.selectedIndex].name, fzy.filterText)) { */
/*             fzy.selectedIndex--; */
/*             if (fzy.selectedIndex < 0) fzy.selectedIndex = fzy.itemCount - 1; */
/*         } */
/*     } */

/*     if ((IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F)) || IsKeyPressed(KEY_RIGHT)) { */
/*         adjustFzyValue(fzy.items[fzy.selectedIndex], 0.1f); */
/*     } else if ((IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_B)) || IsKeyPressed(KEY_LEFT)) { */
/*         adjustFzyValue(fzy.items[fzy.selectedIndex], -0.1f); */
/*     } */
/* } */
