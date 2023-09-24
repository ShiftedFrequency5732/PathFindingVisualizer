#include "../include/config.hpp"
#include "../include/grid.hpp"

#include "../include/bfs.hpp"
#include "../include/dfs.hpp"
#include "../include/dijkstra.hpp"
#include "../include/astar.hpp"

#include "../include/raylib.h"
#include "../include/raymath.h"

int main() {
    // Initialize the basic window, set the width, the height, the title, the target FPS, and make it resizable.
    InitWindow(INITIAL_WIDTH, INITIAL_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Boolean flag that will indicate whether to show the help text.
    bool show_help = true;

    // Create the grid object.
    Grid grid(GRID_SIZE);
    grid.SetMargin(MARGIN_PX);

    // Objects that will perform the path search.
    BFS bfs_algorithm(&grid);
    DFS dfs_algorithm(&grid);
    Dijkstra dijkstras_algorithm(&grid);
    AStar astar_algorithm(&grid);

    // Pointer to the currently selected algorithm.
    Algorithm* path_finding = &bfs_algorithm;
    bool path_search = false;

    while (!WindowShouldClose()) {
        // Start preparing the frame buffer for drawing, clear the window from the previous drawing.
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Calculate the width & height of the cells, so that they all fill the screen completely.
        // In order to ensure that they all will fill the screen, we will ceil the result, and calculate their size as if we had one row and column less.
        int cell_width = ceil(1.0 * GetRenderWidth() / (GRID_SIZE - 1));
        int cell_height = ceil(1.0 * GetRenderHeight() / (GRID_SIZE - 1));

        if (path_search) {
            // Step the current algorithm, in case it has found the path, draw it, and stop the search.
            if (path_finding->Step()) {
                path_finding->GetPath();
                path_search = false;
            }
        }

        // Update the information on the window size and cell size of the grid in case user resized the window. Draw the grid.
        grid.SetWindowSize(GetRenderWidth(), GetRenderHeight());
        grid.SetCellSize(cell_width, cell_height);
        grid.Draw();

        if (show_help) {
            // Draw the help box.
            Vector2 txt_size = MeasureTextEx(GetFontDefault(), HELP_TEXT, FONT_SIZE, SPACING);
            DrawRectangle(GetRenderWidth() / 2 - txt_size.x / 2 - BG_MARGIN / 2, GetRenderHeight() / 2 - txt_size.y / 2 - BG_MARGIN / 2, txt_size.x + BG_MARGIN, txt_size.y + BG_MARGIN, WHITE);
            DrawTextEx(GetFontDefault(), HELP_TEXT, { GetRenderWidth() / 2 - txt_size.x / 2, GetRenderHeight() / 2 - txt_size.y / 2 }, FONT_SIZE, SPACING, BLACK);
        }

        // Send the frame buffer for drawing on the screen.
        EndDrawing();

        // Handle all the mouse events in the grid.
        grid.HandleMouseEvents();

        if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && IsKeyPressed(KEY_SLASH)) {
            // In case the question mark has been pressed, stop showing the help text if its currently shown, or start showing it again if it isn't shown.
            show_help = !show_help;
        }

        // Pick a path searching algorithm, and reset the previously picked one.
        if (IsKeyPressed(KEY_ONE) && !path_search) {
            path_finding->Reset();
            path_finding = &bfs_algorithm;
        }
        else if (IsKeyPressed(KEY_TWO) && !path_search) {
            path_finding->Reset();
            path_finding = &dfs_algorithm;
        }
        else if (IsKeyPressed(KEY_THREE) && !path_search) {
            path_finding->Reset();
            path_finding = &dijkstras_algorithm;
        }
        else if (IsKeyPressed(KEY_FOUR) && !path_search) {
            path_finding->Reset();
            path_finding = &astar_algorithm;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            if (path_finding->IsDone()) {
                // If we pressed space and the algorithm finished, reset it.
                path_finding->Reset();
                path_search = false;
            }
            else {
                // If we picked a different algorithm to run, prepare it, and start running it.
                path_finding->Prepare();
                path_search = true;
            }
        }
    }

    return 0;
}
