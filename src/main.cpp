#include <iostream>
#include <queue>
#include <stack>

#include "../include/config.hpp"
#include "../include/cell.hpp"

#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"

struct Point { int i; int j; };

void MousePickWalls(Cell grid[GRID_SIZE][GRID_SIZE], int cell_width, int cell_height, int window_width, int window_height);

void MousePickStartEnd(Cell grid[GRID_SIZE][GRID_SIZE], int cell_width, int cell_height, Point &start, Point &end);

bool step_bfs(std::queue<Point> &cells, Cell grid[GRID_SIZE][GRID_SIZE], bool visited[GRID_SIZE][GRID_SIZE], Point trace[GRID_SIZE][GRID_SIZE], bool valid[GRID_SIZE][GRID_SIZE], Point end_cell) {
    if (!cells.empty()) {
        Point cell = cells.front();
        cells.pop();

        if (cell.i == end_cell.i && cell.j == end_cell.j) {
            return true;
        }

        if (visited[cell.i][cell.j]) {
            return false;
        }

        visited[cell.i][cell.j] = true;
        if (grid[cell.i][cell.j].getType() == Cell::CellType::EMPTY) {
            grid[cell.i][cell.j].setFillColor(BLUE);
        }

        if (cell.i - 1 >= 0 && (grid[cell.i - 1][cell.j].getType() == Cell::CellType::EMPTY || grid[cell.i - 1][cell.j].getType() == Cell::CellType::END) && !visited[cell.i - 1][cell.j]) {
            cells.push({ cell.i - 1, cell.j });
            trace[cell.i - 1][cell.j] = cell;
            valid[cell.i - 1][cell.j] = true;
            if (grid[cell.i - 1][cell.j].getType() == Cell::CellType::EMPTY) {
                grid[cell.i - 1][cell.j].setFillColor(YELLOW);
            }
        }

        if (cell.i + 1 < GRID_SIZE && (grid[cell.i + 1][cell.j].getType() == Cell::CellType::EMPTY || grid[cell.i + 1][cell.j].getType() == Cell::CellType::END) && !visited[cell.i + 1][cell.j]) {
            cells.push({ cell.i + 1, cell.j });
            trace[cell.i + 1][cell.j] = cell;
            valid[cell.i + 1][cell.j] = true;
            if (grid[cell.i + 1][cell.j].getType() == Cell::CellType::EMPTY) {
                grid[cell.i + 1][cell.j].setFillColor(YELLOW);
            }
        }

        if (cell.j - 1 >= 0 && (grid[cell.i][cell.j - 1].getType() == Cell::CellType::EMPTY || grid[cell.i][cell.j - 1].getType() == Cell::CellType::END) && !visited[cell.i][cell.j - 1]) {
            cells.push({ cell.i, cell.j - 1 });
            trace[cell.i][cell.j - 1] = cell;
            valid[cell.i][cell.j - 1] = true;
            if (grid[cell.i][cell.j - 1].getType() == Cell::CellType::EMPTY) {
                grid[cell.i][cell.j - 1].setFillColor(YELLOW);
            }
        }

        if (cell.j + 1 < GRID_SIZE && (grid[cell.i][cell.j + 1].getType() == Cell::CellType::EMPTY || grid[cell.i][cell.j + 1].getType() == Cell::CellType::END) && !visited[cell.i][cell.j + 1]) {
            cells.push({ cell.i, cell.j + 1 });
            trace[cell.i][cell.j + 1] = cell;
            valid[cell.i][cell.j + 1] = true;
            if (grid[cell.i][cell.j + 1].getType() == Cell::CellType::EMPTY) {
                grid[cell.i][cell.j + 1].setFillColor(YELLOW);
            }
        }

        return false;
    }

    return false;
}

bool step_dfs(std::stack<Point> &cells, Cell grid[GRID_SIZE][GRID_SIZE], bool visited[GRID_SIZE][GRID_SIZE], Point trace[GRID_SIZE][GRID_SIZE], bool valid[GRID_SIZE][GRID_SIZE], Point end_cell) {
    if (!cells.empty()) {
        Point cell = cells.top();
        cells.pop();

        if (cell.i == end_cell.i && cell.j == end_cell.j) {
            return true;
        }

        if (visited[cell.i][cell.j]) {
            return false;
        }

        visited[cell.i][cell.j] = true;
        if (grid[cell.i][cell.j].getType() == Cell::CellType::EMPTY) {
            grid[cell.i][cell.j].setFillColor(BLUE);
        }

        if (cell.i - 1 >= 0 && (grid[cell.i - 1][cell.j].getType() == Cell::CellType::EMPTY || grid[cell.i - 1][cell.j].getType() == Cell::CellType::END) && !visited[cell.i - 1][cell.j]) {
            cells.push({ cell.i - 1, cell.j });
            trace[cell.i - 1][cell.j] = cell;
            valid[cell.i - 1][cell.j] = true;
            if (grid[cell.i - 1][cell.j].getType() == Cell::CellType::EMPTY) {
                grid[cell.i - 1][cell.j].setFillColor(YELLOW);
            }
        }

        if (cell.i + 1 < GRID_SIZE && (grid[cell.i + 1][cell.j].getType() == Cell::CellType::EMPTY || grid[cell.i + 1][cell.j].getType() == Cell::CellType::END) && !visited[cell.i + 1][cell.j]) {
            cells.push({ cell.i + 1, cell.j });
            trace[cell.i + 1][cell.j] = cell;
            valid[cell.i + 1][cell.j] = true;
            if (grid[cell.i + 1][cell.j].getType() == Cell::CellType::EMPTY) {
                grid[cell.i + 1][cell.j].setFillColor(YELLOW);
            }
        }

        if (cell.j - 1 >= 0 && (grid[cell.i][cell.j - 1].getType() == Cell::CellType::EMPTY || grid[cell.i][cell.j - 1].getType() == Cell::CellType::END) && !visited[cell.i][cell.j - 1]) {
            cells.push({ cell.i, cell.j - 1 });
            trace[cell.i][cell.j - 1] = cell;
            valid[cell.i][cell.j - 1] = true;
            if (grid[cell.i][cell.j - 1].getType() == Cell::CellType::EMPTY) {
                grid[cell.i][cell.j - 1].setFillColor(YELLOW);
            }
        }

        if (cell.j + 1 < GRID_SIZE && (grid[cell.i][cell.j + 1].getType() == Cell::CellType::EMPTY || grid[cell.i][cell.j + 1].getType() == Cell::CellType::END) && !visited[cell.i][cell.j + 1]) {
            cells.push({ cell.i, cell.j + 1 });
            trace[cell.i][cell.j + 1] = cell;
            valid[cell.i][cell.j + 1] = true;
            if (grid[cell.i][cell.j + 1].getType() == Cell::CellType::EMPTY) {
                grid[cell.i][cell.j + 1].setFillColor(YELLOW);
            }
        }

        return false;
    }

    return false;
}

int main() {
    // Initialize the basic window.
    InitWindow(INITIAL_WIDTH, INITIAL_HEIGHT, WINDOW_TITLE);
    //SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    Cell grid[GRID_SIZE][GRID_SIZE];

    Point start_cell = { -1, -1 };
    Point end_cell = { -1, -1 };

    bool run_path_search = false;

    std::queue<Point> cells;
    bool visited[GRID_SIZE][GRID_SIZE] = { false };
    bool valid[GRID_SIZE][GRID_SIZE] = { false };
    Point trace[GRID_SIZE][GRID_SIZE];

    while (!WindowShouldClose()) {
        // Start preparing the frame buffer for drawing.
        BeginDrawing();

        // Clear the window from the previous drawings.
        ClearBackground(DARKGRAY);

        int window_width = GetRenderWidth(), window_height = GetRenderHeight();
        int cell_width = ceil(1.0 * window_width / (GRID_SIZE - 1)), cell_height = ceil(1.0 * window_height / (GRID_SIZE - 1));

        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                DrawRectangle(j * cell_width + MARGIN_PX, i * cell_height + MARGIN_PX, cell_width - MARGIN_PX, cell_height - MARGIN_PX, grid[i][j].getFillColor());
            }
        }

        if (run_path_search) {
            if (step_bfs(cells, grid, visited, trace, valid, end_cell)) {
                Point p = end_cell;
                while (valid[p.i][p.j]) {
                    p = trace[p.i][p.j];
                    if (!(p.i == start_cell.i && p.j == start_cell.j)) {
                        grid[p.i][p.j].setFillColor(ORANGE);
                    }
                }
                run_path_search = false;
            }
        }

        // Send the frame buffer for drawing on the screen.
        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            run_path_search = !run_path_search;
            cells.push(start_cell);
        }

        if (!run_path_search) {
            MousePickWalls(grid, cell_width, cell_height, window_width, window_height);
            MousePickStartEnd(grid, cell_width, cell_height, start_cell, end_cell);
        }
    }

    return 0;
}

void MousePickStartEnd(Cell grid[GRID_SIZE][GRID_SIZE], int cell_width, int cell_height, Point &start, Point &end) {
    if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_E)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 curr = { (float) GetMouseX(), (float) GetMouseY() };
        int new_i = curr.y / cell_height, new_j = curr.x / cell_width;
        if (grid[new_i][new_j].getType() != Cell::CellType::START && grid[new_i][new_j].getType() != Cell::CellType::END) {
            Cell::CellType type = IsKeyDown(KEY_S) ? Cell::CellType::START : Cell::CellType::END;
            Point& ref_point = (type == Cell::CellType::START) ? start : end;

            if (ref_point.i != -1 && ref_point.j != -1) {
                grid[ref_point.i][ref_point.j].setType(Cell::CellType::EMPTY);
            }

            ref_point.i = new_i;
            ref_point.j = new_j;
            grid[ref_point.i][ref_point.j].setType(type);
        }
    }
}

bool in_bounds(Vector2 pos, int x_min, int x_max, int y_min, int y_max) {
    return (pos.x >= x_min && pos.x <= x_max && pos.y >= y_min && pos.y <= y_max);
}

void MousePickWalls(Cell grid[GRID_SIZE][GRID_SIZE], int cell_width, int cell_height, int window_width, int window_height) {
    static Vector2 mouse_prev = { -1, -1 };
    static Vector2 mouse_curr = { -1, -1 };

    if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_N)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        mouse_prev = mouse_curr;
        mouse_curr = { (float) GetMouseX(), (float) GetMouseY() };

        Cell::CellType type = Cell::CellType::WALL;
        if (IsKeyDown(KEY_N)) {
            type = Cell::CellType::EMPTY;
        }

        if (in_bounds(mouse_prev, 0, window_width, 0, window_height) && in_bounds(mouse_curr, 0, window_width, 0, window_height)) {
            float x_distance = mouse_curr.x - mouse_prev.x;
            float y_distance = mouse_curr.y - mouse_prev.y;
            float slope = y_distance / x_distance;

            if (std::isnan(slope)) {
                int new_i = mouse_curr.y / cell_height, new_j = mouse_curr.x / cell_width;
                if (grid[new_i][new_j].getType() != Cell::CellType::START && grid[new_i][new_j].getType() != Cell::CellType::END) {
                    grid[new_i][new_j].setType(type);
                }
            }
            else if (abs(x_distance) > abs(y_distance)) {
                int x_min = std::min(mouse_prev.x, mouse_curr.x), x_max = std::max(mouse_prev.x, mouse_curr.x);
                for (int x = x_min; x <= x_max; ++x) {
                    int y = slope * (x - mouse_prev.x) + mouse_prev.y;
                    int new_i = y / cell_height, new_j = x / cell_width;
                    if (grid[new_i][new_j].getType() != Cell::CellType::START && grid[new_i][new_j].getType() != Cell::CellType::END) {
                        grid[new_i][new_j].setType(type);
                    }
                }
            }
            else {
                int y_min = std::min(mouse_prev.y, mouse_curr.y), y_max = std::max(mouse_prev.y, mouse_curr.y);
                for (int y = y_min; y <= y_max; ++y) {
                    int x = (y - mouse_prev.y) / slope + mouse_prev.x;
                    int new_i = y / cell_height, new_j = x / cell_width;
                    if (grid[new_i][new_j].getType() != Cell::CellType::START && grid[new_i][new_j].getType() != Cell::CellType::END) {
                        grid[new_i][new_j].setType(type);
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
