#include "grid.h"
#include <stdlib.h>
#include "theme.h"

// TODO Cursor
Grid cellGrid;
bool showGrid = false;
int verticalSpacing = 0;
int horizontalSpacing = 0;
float textScale = 1.0f;
float cellScale = 1.0f;

void initGrid(Grid *grid, int rows, int cols, int cellWidth, int cellHeight) {
    grid->rows = rows;
    grid->cols = cols;
    grid->cellWidth = cellWidth + horizontalSpacing;   // Adjust cell width with horizontal spacing
    grid->cellHeight = cellHeight + verticalSpacing;   // Adjust cell height with vertical spacing

    grid->cells = (Cell **)malloc(rows * sizeof(Cell *));
    for (int i = 0; i < rows; i++) {
        grid->cells[i] = (Cell *)malloc(cols * sizeof(Cell));
        for (int j = 0; j < cols; j++) {
            grid->cells[i][j].character = ' ';
            grid->cells[i][j].fgColor = WHITE;
            grid->cells[i][j].bgColor = (Color){0, 0, 0, 0};  // transparent α
            grid->cells[i][j].hasCharacter = false;
        }
    }
}

void drawGrid(const Grid *grid, Font font) {
    for (int row = 0; row < grid->rows; row++) {
        for (int col = 0; col < grid->cols; col++) {
            Cell cell = grid->cells[row][col];
            int x = col * (grid->cellWidth + horizontalSpacing) * cellScale;
            int y = row * (grid->cellHeight + verticalSpacing) * cellScale;
            int cellWidthScaled = grid->cellWidth * cellScale;
            int cellHeightScaled = grid->cellHeight * cellScale;

            // Draw background only if it is not transparent
            if (cell.bgColor.a > 0) {
                DrawRectangle(x, y, cellWidthScaled, cellHeightScaled, cell.bgColor);
            }

            // Draw character centered in cell
            if (cell.hasCharacter) {
                char character[2] = {cell.character, '\0'};
                int scaledCellHeight = cellHeightScaled * textScale;
                int textWidth = MeasureTextEx(font, character, scaledCellHeight, 0).x;
                int textHeight = MeasureTextEx(font, character, scaledCellHeight, 0).y;
                DrawTextEx(font, character, (Vector2){x + (cellWidthScaled - textWidth) / 2.0f, y + (cellHeightScaled - textHeight) / 2.0f}, scaledCellHeight, 0, cell.fgColor);
            }

            if (showGrid) {
                DrawRectangleLines(x, y, cellWidthScaled, cellHeightScaled, CT.minibuffer);
            }
        }
    }
}

void setCell(Grid *grid, int row, int col, char character, Color fgColor, Color bgColor) {
    if (row >= 0 && row < grid->rows && col >= 0 && col < grid->cols) {
        grid->cells[row][col].character = character;
        grid->cells[row][col].fgColor = fgColor;
        grid->cells[row][col].bgColor = bgColor;
        grid->cells[row][col].hasCharacter = (character != ' ');
    }
}

void clearGrid(Grid *grid) {
    for (int row = 0; row < grid->rows; row++) {
        for (int col = 0; col < grid->cols; col++) {
            grid->cells[row][col].character = ' ';
            grid->cells[row][col].fgColor = WHITE;
            grid->cells[row][col].bgColor = (Color){0, 0, 0, 0};  // Set default background to transparent
            grid->cells[row][col].hasCharacter = false;
        }
    }
}

void freeGrid(Grid *grid) {
    for (int i = 0; i < grid->rows; i++) {
        free(grid->cells[i]);
    }
    free(grid->cells);
}

void setCellBackgroundColor(Grid *grid, int row, int col, Color bgColor) {
    if (row >= 0 && row < grid->rows && col >= 0 && col < grid->cols) {
        grid->cells[row][col].bgColor = bgColor;
    }
}

void setCellForegroundColor(Grid *grid, int row, int col, Color fgColor) {
    if (row >= 0 && row < grid->rows && col >= 0 && col < grid->cols) {
        grid->cells[row][col].fgColor = fgColor;
    }
}

void setCellCharacter(Grid *grid, int row, int col, char character) {
    if (row >= 0 && row < grid->rows && col >= 0 && col < grid->cols) {
        grid->cells[row][col].character = character;
        grid->cells[row][col].hasCharacter = (character != ' ');
    }
}

char getCellCharacter(const Grid *grid, int row, int col) {
    if (row >= 0 && row < grid->rows && col >= 0 && col < grid->cols) {
        return grid->cells[row][col].character;
    }
    return ' ';
}

Color getCellBackgroundColor(const Grid *grid, int row, int col) {
    if (row >= 0 && row < grid->rows && col >= 0 && col < grid->cols) {
        return grid->cells[row][col].bgColor;
    }
    return BLACK;
}

Color getCellForegroundColor(const Grid *grid, int row, int col) {
    if (row >= 0 && row < grid->rows && col >= 0 && col < grid->cols) {
        return grid->cells[row][col].fgColor;
    }
    return WHITE;
}
