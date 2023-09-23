#include <iostream>

#include "../include/config.hpp"

#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"

enum class CellType { EMPTY = 0, WALL = 1, START = 2, END = 3 };
constexpr Color colors[] = { BLACK, WHITE, GREEN, RED };

struct Point { int i; int j; };

void MousePickWalls(CellType grid[GRID_SIZE][GRID_SIZE], int cell_width, int cell_height, int window_width, int window_height);

void MousePickStartEnd(CellType grid[GRID_SIZE][GRID_SIZE], int cell_width, int cell_height, Point &start, Point &end);

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

        int window_width = GetRenderWidth();
        int window_height = GetRenderHeight();

        int cell_width = ceil(1.0 * window_width / (GRID_SIZE - 1));
        int cell_height = ceil(1.0 * window_height / (GRID_SIZE - 1));

        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                DrawRectangle(j * cell_width + MARGIN_PX, i * cell_height + MARGIN_PX, cell_width - MARGIN_PX, cell_height - MARGIN_PX, colors[(int)grid[i][j]]);
            }
        }

        // Send the frame buffer for drawing on the screen.
        EndDrawing();

        MousePickWalls(grid, cell_width, cell_height, window_width, window_height);
        MousePickStartEnd(grid, cell_width, cell_height, start_cell, end_cell);
    }

    return 0;
}

void MousePickStartEnd(CellType grid[GRID_SIZE][GRID_SIZE], int cell_width, int cell_height, Point &start, Point &end) {
    if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_E)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 curr = { (float) GetMouseX(), (float) GetMouseY() };
        int new_i = curr.y / cell_height, new_j = curr.x / cell_width;

        if (grid[new_i][new_j] != CellType::START && grid[new_i][new_j] != CellType::END) {
            CellType type = IsKeyDown(KEY_S) ? CellType::START : CellType::END;
            Point& ref_point = IsKeyDown(KEY_S) ? start : end;

            if (ref_point.i != -1 && ref_point.j != -1) {
                grid[ref_point.i][ref_point.j] = CellType::EMPTY;
            }

            ref_point.i = new_i;
            ref_point.j = new_j;
            grid[ref_point.i][ref_point.j] = type;
        }
    }
}

bool in_bounds(Vector2 pos, int x_min, int x_max, int y_min, int y_max) {
    return (pos.x >= x_min && pos.x <= x_max && pos.y >= y_min && pos.y <= y_max);
}

void MousePickWalls(CellType grid[GRID_SIZE][GRID_SIZE], int cell_width, int cell_height, int window_width, int window_height) {
    static Vector2 mouse_prev = { -1, -1 };
    static Vector2 mouse_curr = { -1, -1 };

    if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_N)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        mouse_prev = mouse_curr;
        mouse_curr = { (float) GetMouseX(), (float) GetMouseY() };

        CellType type = CellType::WALL;
        if (IsKeyDown(KEY_N)) {
            type = CellType::EMPTY;
        }

        if (in_bounds(mouse_prev, 0, window_width, 0, window_height) && in_bounds(mouse_curr, 0, window_width, 0, window_height)) {
            float x_distance = mouse_curr.x - mouse_prev.x;
            float y_distance = mouse_curr.y - mouse_prev.y;
            float slope = y_distance / x_distance;

            if (std::isnan(slope)) {
                int new_i = mouse_curr.y / cell_height, new_j = mouse_curr.x / cell_width;
                if (grid[new_i][new_j] != CellType::START && grid[new_i][new_j] != CellType::END) {
                    grid[(int) mouse_curr.y / cell_height][(int) mouse_curr.x / cell_width] = type;
                }
            }
            else if (abs(x_distance) > abs(y_distance)) {
                int x_min = std::min(mouse_prev.x, mouse_curr.x);
                int x_max = std::max(mouse_prev.x, mouse_curr.x);
                for (int x = x_min; x <= x_max; ++x) {
                    int y = slope * (x - mouse_prev.x) + mouse_prev.y;
                    int new_i = y / cell_height, new_j = x / cell_width;
                    if (grid[new_i][new_j] != CellType::START && grid[new_i][new_j] != CellType::END) {
                        grid[y / cell_height][x / cell_width] = type;
                    }
                }
            }
            else {
                int y_min = std::min(mouse_prev.y, mouse_curr.y);
                int y_max = std::max(mouse_prev.y, mouse_curr.y);
                for (int y = y_min; y <= y_max; ++y) {
                    int x = (y - mouse_prev.y) / slope + mouse_prev.x;
                    int new_i = y / cell_height, new_j = x / cell_width;
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
