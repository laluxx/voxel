#include "font.h"
#include <raylib.h>
#include <stddef.h>

Font jetb;
int fontSize = 19;

void initFonts() {
    int loadSize = fontSize;

    const char *fontPath = "./assets/jetb.ttf";

    jetb = LoadFontEx(fontPath, loadSize, NULL, 0);

    if (jetb.texture.id == 0) {
        TraceLog(LOG_WARNING, "Failed to load jetb font!");
    } else {
        SetTextureFilter(jetb.texture, TEXTURE_FILTER_BILINEAR);
        TraceLog(LOG_INFO, "Font loaded successfully, and filter set for smoothing.");
    }
}
