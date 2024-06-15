#include "theme.h"
#include <string.h>
#include <stdio.h>

int currentThemeIndex = 0;
Theme themes[8];

Color hexToColor(const char* hexStr) {
    if (hexStr[0] == '#' && strlen(hexStr) == 7) {
        int r, g, b;
        sscanf(hexStr + 1, "%02x%02x%02x", &r, &g, &b);
        return (Color){ r, g, b, 255 };
    }
    return BLACK; // Default if the format is wrong
}

void initThemes() {
    themes[0] = (Theme) {
        .name               = "Nature",
        .background         = hexToColor("#070707"),
        .cursor             = hexToColor("#658B5F"),
        .text               = hexToColor("#C0ACD1"),
        .minibuffer         = hexToColor("#090909"),
        .modeline           = hexToColor("#050505"),
        .accent             = hexToColor("#658B5F"),
    };

    themes[1] = (Theme) {
        .name = "Gum",
        .background         = hexToColor("#14171E"),
        .cursor             = hexToColor("#D6A0D1"),
        .text               = hexToColor("#D4D4D6"),
        .minibuffer         = hexToColor("#14171E"),
        .modeline           = hexToColor("#191D26"),
        .accent             = hexToColor("#9587DE"),
    };

    themes[2] = (Theme) {
        .name = "Tokyonight",
        .background         = hexToColor("#1A1B26"),
        .cursor             = hexToColor("#7AA2F7"),
        .text               = hexToColor("#A9B1D6"),
        .minibuffer         = hexToColor("#1A1B26"),
        .modeline           = hexToColor("#161620"),
        .accent             = hexToColor("#7AA2F7"),
    };

    themes[3] = (Theme) {
        .name = "Catppuccin",
        .background         = hexToColor("#1E1E2E"),
        .cursor             = hexToColor("#B4BEFE"),
        .text               = hexToColor("#CDD6F4"),
        .minibuffer         = hexToColor("#1E1E2E"),
        .modeline           = hexToColor("#181825"),
        .accent             = hexToColor("#B4BEFE"),
    };

    themes[4] = (Theme) {
        .name = "Doom-one",
        .background         = hexToColor("#282C34"),
        .cursor             = hexToColor("#51AFEF"),
        .text               = hexToColor("#BBC2CF"),
        .minibuffer         = hexToColor("#21242B"),
        .modeline           = hexToColor("#1D2026"),
        .accent             = hexToColor("#51AFEF"),
    };

    themes[5] = (Theme) {
        .name = "City-lights",
        .background         = hexToColor("#1D252C"),
        .cursor             = hexToColor("#51AFEF"),
        .text               = hexToColor("#A0B3C5"),
        .minibuffer         = hexToColor("#181E24"),
        .modeline           = hexToColor("#181F25"),
        .accent             = hexToColor("#5EC4FF"),
    };

    themes[6] = (Theme) {
        .name = "Molokai",
        .background         = hexToColor("#1C1E1F"),
        .cursor             = hexToColor("#FB2874"),
        .text               = hexToColor("#D6D6D4"),
        .minibuffer         = hexToColor("#222323"),
        .modeline           = hexToColor("#2D2E2E"),
        .accent             = hexToColor("#B6E63E"),
    };

    themes[7] = (Theme) {
        .name = "Sunset",
        .background         = hexToColor("#0C0D12"),
        .cursor             = hexToColor("#D9A173"),
        .text               = hexToColor("#CCCCC5"),
        .minibuffer         = hexToColor("#0C0D12"),
        .modeline           = hexToColor("#08090C"),
        .accent             = hexToColor("#D9A173"),
    };

}

void nextTheme() {
    currentThemeIndex++;
    if (currentThemeIndex >= sizeof(themes) / sizeof(Theme)) {
        currentThemeIndex = 0;
    }
}

void previousTheme() {
    currentThemeIndex--;
    if (currentThemeIndex < 0) {
        currentThemeIndex = sizeof(themes) / sizeof(Theme) - 1;
    }
}

// TODO This should use fzy
void loadTheme(const char* themeName) {
    for (int i = 0; i < sizeof(themes) / sizeof(Theme); i++) {
        if (strcmp(themes[i].name, themeName) == 0) {
            currentThemeIndex = i;
            return;
        }
    }
    // Optionally, handle the case where the theme is not found
    printf("Theme '%s' not found.\n", themeName);
}
