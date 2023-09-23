#include <iostream>

#include "../include/config.hpp"

#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"

enum class CellType { EMPTY = 0, WALL = 1, START = 2, END = 3 };
constexpr Color colors[] = { BLACK, WHITE, GREEN, RED };

void MousePickWalls(CellType grid[GRID_SIZE][GRID_SIZE]);

struct Point {
    int i;
    int j;
};

void MousePickStartEnd(CellType grid[GRID_SIZE][GRID_SIZE], Point &start, Point &end);

int main() {
    // Initialize the basic window.
    InitWindow(INITIAL_WIDTH, INITIAL_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    CellType grid[GRID_SIZE][GRID_SIZE] = { CellType::EMPTY };

    Point start_cell = { -1, -1 };
    Point end_cell = { -1, -1 };

    while (!WindowShouldClose()) {
        // Start preparing the frame buffer for drawing.
        BeginDrawing();

        // Clear the window from the previous drawings.
        ClearBackground(DARKGRAY);

        int cell_width = ceil(1.0 * GetRenderWidth() / (GRID_SIZE - 1));
        int cell_height = ceil(1.0 * GetRenderHeight() / (GRID_SIZE - 1));

        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                DrawRectangle(j * cell_width + MARGIN_PX, i * cell_height + MARGIN_PX, cell_width - MARGIN_PX, cell_height - MARGIN_PX, colors[(int)grid[i][j]]);
            }
        }

        // Send the frame buffer for drawing on the screen.
        EndDrawing();

        MousePickWalls(grid);
        MousePickStartEnd(grid, start_cell, end_cell);
    }

    return 0;
}

void MousePickStartEnd(CellType grid[GRID_SIZE][GRID_SIZE], Point &start, Point &end) {
    if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_E)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 curr = { (float) GetMouseX(), (float) GetMouseY() };
        int cell_width = ceil(1.0 * GetRenderWidth() / (GRID_SIZE - 1));
        int cell_height = ceil(1.0 * GetRenderHeight() / (GRID_SIZE - 1));
        int new_i = curr.y / cell_height;
        int new_j = curr.x / cell_width;
        if(grid[new_i][new_j] != CellType::START && grid[new_i][new_j] != CellType::END) {
            CellType type = IsKeyDown(KEY_S) ? CellType::START : CellType::END;
            Point& ref_point = IsKeyDown(KEY_S) ? start : end;

            if(ref_point.i != -1 && ref_point.j != -1) {
                grid[ref_point.i][ref_point.j] = CellType::EMPTY;
            }
            ref_point.i = curr.y / cell_height;
            ref_point.j = curr.x / cell_width;
            grid[ref_point.i][ref_point.j] = type;
        }
    }
}

void MousePickWalls(CellType grid[GRID_SIZE][GRID_SIZE]) {
    static Vector2 mouse_prev = { -1, -1 };
    static Vector2 mouse_curr = { -1, -1 };

    int cell_width = ceil(1.0 * GetRenderWidth() / (GRID_SIZE - 1));
    int cell_height = ceil(1.0 * GetRenderHeight() / (GRID_SIZE - 1));

    if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_N)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        CellType type = CellType::WALL;
        if (IsKeyDown(KEY_N)) {
            type = CellType::EMPTY; 
        }
        mouse_prev = mouse_curr;
        mouse_curr = { (float) GetMouseX(), (float) GetMouseY() };

        int window_width = GetRenderWidth();
        int window_height = GetRenderHeight();

        if (mouse_prev.x >= 0 && mouse_prev.y >= 0 && mouse_prev.x <= window_width && mouse_prev.y <= window_height &&
            mouse_curr.x >= 0 && mouse_curr.y >= 0 && mouse_curr.x <= window_width && mouse_curr.y <= window_height) {
            float x_distance = mouse_curr.x - mouse_prev.x;
            float y_distance = mouse_curr.y - mouse_prev.y;
            float slope = y_distance / x_distance;

            if (std::isnan(slope)) {
                int new_i = mouse_curr.y / cell_height;
                int new_j = mouse_curr.x / cell_width;
                if (grid[new_i][new_j] != CellType::START && grid[new_i][new_j] != CellType::END) {
                    grid[(int) mouse_curr.y / cell_height][(int) mouse_curr.x / cell_width] = type;
                }
            }
            else if (abs(x_distance) > abs(y_distance)) {
                int x_min = std::min(mouse_prev.x, mouse_curr.x);
                int x_max = std::max(mouse_prev.x, mouse_curr.x);
                for(int x = x_min; x <= x_max; ++x) {
                    int y = slope * (x - mouse_prev.x) + mouse_prev.y;
                    int new_i = y / cell_height;
                    int new_j = x / cell_width;
                    if (grid[new_i][new_j] != CellType::START && grid[new_i][new_j] != CellType::END) {
                        grid[y / cell_height][x / cell_width] = type;
                    }
                }
            }
            else {
                int y_min = std::min(mouse_prev.y, mouse_curr.y);
                int y_max = std::max(mouse_prev.y, mouse_curr.y);
                for(int y = y_min; y <= y_max; ++y) {
                    int x = (y - mouse_prev.y) / slope + mouse_prev.x;
                    int new_i = y / cell_height;
                    int new_j = x / cell_width;
                    if (grid[new_i][new_j] != CellType::START && grid[new_i][new_j] != CellType::END) {
                        grid[y / cell_height][x / cell_width] = type;
                    }
                }
            }
        }
    }
    else {
        mouse_prev = { -1, -1 };
        mouse_curr = { -1, -1 };
    }
}
