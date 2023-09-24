#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "../include/config.hpp"
#include "../include/cell.hpp"
#include "../include/point.hpp"
#include "../include/grid.hpp"

#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"

// bool step_bfs(std::queue<Point> &cells, Cell grid[GRID_SIZE][GRID_SIZE], bool visited[GRID_SIZE][GRID_SIZE], Point trace[GRID_SIZE][GRID_SIZE], bool valid[GRID_SIZE][GRID_SIZE], Point end_cell) {
//     if (!cells.empty()) {
//         Point cell = cells.front();
//         cells.pop();
// 
//         if (cell.i == end_cell.i && cell.j == end_cell.j) {
//             return true;
//         }
// 
//         if (visited[cell.i][cell.j]) {
//             return false;
//         }
// 
//         visited[cell.i][cell.j] = true;
//         if (grid[cell.i][cell.j].GetType() == Cell::CellType::EMPTY) {
//             grid[cell.i][cell.j].SetFillColor(BLUE);
//         }
// 
//         if (cell.i - 1 >= 0 && (grid[cell.i - 1][cell.j].GetType() == Cell::CellType::EMPTY || grid[cell.i - 1][cell.j].GetType() == Cell::CellType::END) && !visited[cell.i - 1][cell.j]) {
//             cells.push({ cell.i - 1, cell.j });
//             trace[cell.i - 1][cell.j] = cell;
//             valid[cell.i - 1][cell.j] = true;
//             if (grid[cell.i - 1][cell.j].GetType() == Cell::CellType::EMPTY) {
//                 grid[cell.i - 1][cell.j].SetFillColor(YELLOW);
//             }
//         }
// 
//         if (cell.i + 1 < GRID_SIZE && (grid[cell.i + 1][cell.j].GetType() == Cell::CellType::EMPTY || grid[cell.i + 1][cell.j].GetType() == Cell::CellType::END) && !visited[cell.i + 1][cell.j]) {
//             cells.push({ cell.i + 1, cell.j });
//             trace[cell.i + 1][cell.j] = cell;
//             valid[cell.i + 1][cell.j] = true;
//             if (grid[cell.i + 1][cell.j].GetType() == Cell::CellType::EMPTY) {
//                 grid[cell.i + 1][cell.j].SetFillColor(YELLOW);
//             }
//         }
// 
//         if (cell.j - 1 >= 0 && (grid[cell.i][cell.j - 1].GetType() == Cell::CellType::EMPTY || grid[cell.i][cell.j - 1].GetType() == Cell::CellType::END) && !visited[cell.i][cell.j - 1]) {
//             cells.push({ cell.i, cell.j - 1 });
//             trace[cell.i][cell.j - 1] = cell;
//             valid[cell.i][cell.j - 1] = true;
//             if (grid[cell.i][cell.j - 1].GetType() == Cell::CellType::EMPTY) {
//                 grid[cell.i][cell.j - 1].SetFillColor(YELLOW);
//             }
//         }
// 
//         if (cell.j + 1 < GRID_SIZE && (grid[cell.i][cell.j + 1].GetType() == Cell::CellType::EMPTY || grid[cell.i][cell.j + 1].GetType() == Cell::CellType::END) && !visited[cell.i][cell.j + 1]) {
//             cells.push({ cell.i, cell.j + 1 });
//             trace[cell.i][cell.j + 1] = cell;
//             valid[cell.i][cell.j + 1] = true;
//             if (grid[cell.i][cell.j + 1].GetType() == Cell::CellType::EMPTY) {
//                 grid[cell.i][cell.j + 1].SetFillColor(YELLOW);
//             }
//         }
// 
//         return false;
//     }
// 
//     return false;
// }
// 
// bool step_dfs(std::stack<Point> &cells, Cell grid[GRID_SIZE][GRID_SIZE], bool visited[GRID_SIZE][GRID_SIZE], Point trace[GRID_SIZE][GRID_SIZE], bool valid[GRID_SIZE][GRID_SIZE], Point end_cell) {
//     if (!cells.empty()) {
//         Point cell = cells.top();
//         cells.pop();
// 
//         if (cell.i == end_cell.i && cell.j == end_cell.j) {
//             return true;
//         }
// 
//         if (visited[cell.i][cell.j]) {
//             return false;
//         }
// 
//         visited[cell.i][cell.j] = true;
//         if (grid[cell.i][cell.j].GetType() == Cell::CellType::EMPTY) {
//             grid[cell.i][cell.j].SetFillColor(BLUE);
//         }
// 
//         if (cell.i - 1 >= 0 && (grid[cell.i - 1][cell.j].GetType() == Cell::CellType::EMPTY || grid[cell.i - 1][cell.j].GetType() == Cell::CellType::END) && !visited[cell.i - 1][cell.j]) {
//             cells.push({ cell.i - 1, cell.j });
//             trace[cell.i - 1][cell.j] = cell;
//             valid[cell.i - 1][cell.j] = true;
//             if (grid[cell.i - 1][cell.j].GetType() == Cell::CellType::EMPTY) {
//                 grid[cell.i - 1][cell.j].SetFillColor(YELLOW);
//             }
//         }
// 
//         if (cell.i + 1 < GRID_SIZE && (grid[cell.i + 1][cell.j].GetType() == Cell::CellType::EMPTY || grid[cell.i + 1][cell.j].GetType() == Cell::CellType::END) && !visited[cell.i + 1][cell.j]) {
//             cells.push({ cell.i + 1, cell.j });
//             trace[cell.i + 1][cell.j] = cell;
//             valid[cell.i + 1][cell.j] = true;
//             if (grid[cell.i + 1][cell.j].GetType() == Cell::CellType::EMPTY) {
//                 grid[cell.i + 1][cell.j].SetFillColor(YELLOW);
//             }
//         }
// 
//         if (cell.j - 1 >= 0 && (grid[cell.i][cell.j - 1].GetType() == Cell::CellType::EMPTY || grid[cell.i][cell.j - 1].GetType() == Cell::CellType::END) && !visited[cell.i][cell.j - 1]) {
//             cells.push({ cell.i, cell.j - 1 });
//             trace[cell.i][cell.j - 1] = cell;
//             valid[cell.i][cell.j - 1] = true;
//             if (grid[cell.i][cell.j - 1].GetType() == Cell::CellType::EMPTY) {
//                 grid[cell.i][cell.j - 1].SetFillColor(YELLOW);
//             }
//         }
// 
//         if (cell.j + 1 < GRID_SIZE && (grid[cell.i][cell.j + 1].GetType() == Cell::CellType::EMPTY || grid[cell.i][cell.j + 1].GetType() == Cell::CellType::END) && !visited[cell.i][cell.j + 1]) {
//             cells.push({ cell.i, cell.j + 1 });
//             trace[cell.i][cell.j + 1] = cell;
//             valid[cell.i][cell.j + 1] = true;
//             if (grid[cell.i][cell.j + 1].GetType() == Cell::CellType::EMPTY) {
//                 grid[cell.i][cell.j + 1].SetFillColor(YELLOW);
//             }
//         }
// 
//         return false;
//     }
// 
//     return false;
// }
// 
// class Compare {
// public:
//     bool operator()(std::pair<int, Point> a, std::pair<int, Point> b){
//         if(a.first > b.first) {
//             return true;
//         } 
//         return false;
//     }
// };
// 
// bool step_dijkstra(std::priority_queue<std::pair<int, Point>, std::vector<std::pair<int, Point>>, Compare> &cells, Cell grid[GRID_SIZE][GRID_SIZE], bool visited[GRID_SIZE][GRID_SIZE], Point trace[GRID_SIZE][GRID_SIZE], bool valid[GRID_SIZE][GRID_SIZE], int distance[GRID_SIZE][GRID_SIZE], Point end_cell) {
//     if (!cells.empty()) {
//         Point cell = cells.top().second;
//         cells.pop();
// 
//         if (cell.i == end_cell.i && cell.j == end_cell.j) {
//             return true;
//         }
// 
//         if (visited[cell.i][cell.j]) {
//             return false;
//         }
// 
//         visited[cell.i][cell.j] = true;
//         if (grid[cell.i][cell.j].GetType() == Cell::CellType::EMPTY) {
//             grid[cell.i][cell.j].SetFillColor(BLUE);
//         }
// 
//         if (cell.i - 1 >= 0 && (grid[cell.i - 1][cell.j].GetType() == Cell::CellType::EMPTY || grid[cell.i - 1][cell.j].GetType() == Cell::CellType::END) && !visited[cell.i - 1][cell.j]) {
//             if (distance[cell.i - 1][cell.j] > distance[cell.i][cell.j] + 1) {
//                 distance[cell.i - 1][cell.j] = distance[cell.i][cell.j] + 1;
//                 cells.push({distance[cell.i - 1][cell.j], { cell.i - 1, cell.j }});
//                 trace[cell.i - 1][cell.j] = cell;
//                 valid[cell.i - 1][cell.j] = true;
//                 if (grid[cell.i - 1][cell.j].GetType() == Cell::CellType::EMPTY) {
//                     grid[cell.i - 1][cell.j].SetFillColor(YELLOW);
//                 }
//             }
//         }
// 
//         if (cell.i + 1 < GRID_SIZE && (grid[cell.i + 1][cell.j].GetType() == Cell::CellType::EMPTY || grid[cell.i + 1][cell.j].GetType() == Cell::CellType::END) && !visited[cell.i + 1][cell.j]) {
//             if (distance[cell.i + 1][cell.j] > distance[cell.i][cell.j] + 1) {
//                 distance[cell.i + 1][cell.j] = distance[cell.i][cell.j] + 1;
//                 cells.push({ distance[cell.i + 1][cell.j], { cell.i + 1, cell.j } });
//                 trace[cell.i + 1][cell.j] = cell;
//                 valid[cell.i + 1][cell.j] = true;
//                 if (grid[cell.i + 1][cell.j].GetType() == Cell::CellType::EMPTY) {
//                     grid[cell.i + 1][cell.j].SetFillColor(YELLOW);
//                 }
//             }
//         }
// 
//         if (cell.j - 1 >= 0 && (grid[cell.i][cell.j - 1].GetType() == Cell::CellType::EMPTY || grid[cell.i][cell.j - 1].GetType() == Cell::CellType::END) && !visited[cell.i][cell.j - 1]) {
//             if (distance[cell.i][cell.j - 1] > distance[cell.i][cell.j] + 1) {
//                 distance[cell.i][cell.j - 1] = distance[cell.i][cell.j] + 1;
//                 cells.push({ distance[cell.i][cell.j - 1], { cell.i, cell.j - 1 }});
//                 trace[cell.i][cell.j - 1] = cell;
//                 valid[cell.i][cell.j - 1] = true;
//                 if (grid[cell.i][cell.j - 1].GetType() == Cell::CellType::EMPTY) {
//                     grid[cell.i][cell.j - 1].SetFillColor(YELLOW);
//                 }
//             }
//         }
// 
//         if (cell.j + 1 < GRID_SIZE && (grid[cell.i][cell.j + 1].GetType() == Cell::CellType::EMPTY || grid[cell.i][cell.j + 1].GetType() == Cell::CellType::END) && !visited[cell.i][cell.j + 1]) {
//             if (distance[cell.i][cell.j + 1] > distance[cell.i][cell.j] + 1) {
//                 distance[cell.i][cell.j + 1] = distance[cell.i][cell.j] + 1;
//                 cells.push({ distance[cell.i][cell.j + 1], { cell.i, cell.j + 1 } });
//                 trace[cell.i][cell.j + 1] = cell;
//                 valid[cell.i][cell.j + 1] = true;
//                 if (grid[cell.i][cell.j + 1].GetType() == Cell::CellType::EMPTY) {
//                     grid[cell.i][cell.j + 1].SetFillColor(YELLOW);
//                 }
//             }
//         }
// 
//         return false;
//     }
//     else {
//         return true;
//     }
// }

int main() {
    // Initialize the basic window, set the width, height, title, target FPS, and make it resizable.
    InitWindow(INITIAL_WIDTH, INITIAL_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Create grid object.
    Grid grid(GRID_SIZE);
    grid.SetGridMargin(MARGIN_PX);

    while (!WindowShouldClose()) {
        // Start preparing the frame buffer for drawing, clear the window from the previous drawing.
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Calculate the width & height of the cells, so that they all fill the screen completely.
        // In order to ensure that they all will fill the screen, we will ceil the result, and calculate their size as if we had one row and column less.
        int cell_width = ceil(1.0 * GetRenderWidth() / (GRID_SIZE - 1));
        int cell_height = ceil(1.0 * GetRenderHeight() / (GRID_SIZE - 1));

        // Update the information on the window size and cell size of the grid in case user resized the window. Draw the grid.
        grid.SetWindowSize(GetRenderWidth(), GetRenderHeight());
        grid.SetCellSize(cell_width, cell_height);
        grid.DrawGrid();

        // Send the frame buffer for drawing on the screen.
        EndDrawing();

        // Handle all the mouse events in the grid.
        grid.HandleMouseEvents();
    }

    return 0;
}
