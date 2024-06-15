#ifndef GRID_H
#define GRID_H

#include <raylib.h>

typedef struct {
    char character;
    Color fgColor;
    Color bgColor;
    bool hasCharacter;
} Cell;

typedef struct {
    int rows;
    int cols;
    int cellWidth;
    int cellHeight;
    Cell **cells;
} Grid;

extern Grid cellGrid;
extern bool showGrid;
extern int verticalSpacing;
extern int horizontalSpacing;
extern float textScale;
extern float cellScale;

void initGrid(Grid *grid, int rows, int cols, int cellWidth, int cellHeight);
void drawGrid(const Grid *grid, Font font);
void setCell(Grid *grid, int row, int col, char character, Color fgColor, Color bgColor);
void clearGrid(Grid *grid);
void freeGrid(Grid *grid);
void setCellBackgroundColor(Grid *grid, int row, int col, Color bgColor);
void setCellForegroundColor(Grid *grid, int row, int col, Color fgColor);
void setCellCharacter(Grid *grid, int row, int col, char character);
char getCellCharacter(const Grid *grid, int row, int col);
Color getCellBackgroundColor(const Grid *grid, int row, int col);
Color getCellForegroundColor(const Grid *grid, int row, int col);

#endif // GRID_H
