#ifndef THEME_H
#define THEME_H

#include "raylib.h"

typedef struct {
    char* name;
    Color background;
    Color modeline;
    Color accent;
    Color minibuffer;
    Color timeline;
    Color cursor;
    Color text;
} Theme;

extern Theme themes[];
extern int currentThemeIndex;

#define CT (themes[currentThemeIndex])

Color hexToColor(const char* hexStr);
void initThemes();
void nextTheme();
void previousTheme();
void loadTheme(const char* themeName);

#endif
