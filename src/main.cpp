#include <iostream>

#include "../include/config.hpp"
#include "../include/cell.hpp"
#include "../include/cell_point.hpp"
#include "../include/grid.hpp"
#include "../include/bfs.hpp"

#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"


int main() {
    // Initialize the basic window, set the width, the height, the title, the target FPS, and make it resizable.
    InitWindow(INITIAL_WIDTH, INITIAL_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Create the grid object.
    Grid grid(GRID_SIZE);
    grid.SetMargin(MARGIN_PX);

    BFS b(&grid);

    bool path_search = false;

    while (!WindowShouldClose()) {
        // Start preparing the frame buffer for drawing, clear the window from the previous drawing.
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Calculate the width & height of the cells, so that they all fill the screen completely.
        // In order to ensure that they all will fill the screen, we will ceil the result, and calculate their size as if we had one row and column less.
        int cell_width = ceil(1.0 * GetRenderWidth() / (GRID_SIZE - 1));
        int cell_height = ceil(1.0 * GetRenderHeight() / (GRID_SIZE - 1));

        if(path_search) {
            if(!b.Step()) {
                b.GetPath();
                path_search = false;
            }
        }

        // Update the information on the window size and cell size of the grid in case user resized the window. Draw the grid.
        grid.SetWindowSize(GetRenderWidth(), GetRenderHeight());
        grid.SetCellSize(cell_width, cell_height);
        grid.Draw();

        // Send the frame buffer for drawing on the screen.
        EndDrawing();

        // Handle all the mouse events in the grid.
        grid.HandleMouseEvents();


        if(IsKeyPressed(KEY_SPACE)) {
            path_search = !path_search;
            b.Prepare();
        }
    }

    return 0;
}
