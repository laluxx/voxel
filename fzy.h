#ifndef FZY_H
#define FZY_H

#include <raylib.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT
} VariableType;

typedef struct {
    const char *name;
    VariableType type;
    void *value;
} FzyItem;

typedef struct {
    FzyItem *items;
    int itemCount;
    int selectedIndex;
    char filterText[32];
    bool showFzy;
    bool topFzy;
} Fzy;

extern Fzy fzy;
extern int fzyItemCount;
extern FzyItem fzyItems[];


void initFzy(FzyItem *items, int itemCount);
void drawFzy();
void handleFzyInput();
void adjustFzyValue(FzyItem item, float delta);


#endif  // FZY_H
