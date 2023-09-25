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

    // Boolean flag that will indicate whether to show the help text or not.
    bool show_help = true;

    // Create the grid object.
    Grid map;

    // Objects that will perform the path search.
    BFS bfs_algorithm(&map);
    DFS dfs_algorithm(&map);
    Dijkstra dijkstras_algorithm(&map);
    AStar astar_algorithm(&map);

    // Pointer to the currently selected algorithm.
    Algorithm* path_finding_algorithm = &bfs_algorithm;

    // Boolean flag that will indicate whether to perform the path search or not in the game loop.
    bool path_search = false;

    while (!WindowShouldClose()) {
        // Start preparing the frame buffer for drawing.
        BeginDrawing();

        // Clear the screen from the previous drawing.
        ClearBackground(DARKGRAY);

        if (path_search && !path_finding_algorithm->IsDone()) {
            // Step the current path searching algorithm, in case it has found the path, draw it, and stop the search.
            if (path_finding_algorithm->Step()) {
                path_finding_algorithm->GetPath();
            }
        }

        // Calculate the width & height of the cells, so that they all fill the screen completely.
        // In order to ensure that they all will fill the screen, we will ceil the result, and calculate their size as if we had one row and column less.
        int cell_width = ceil(1.0 * GetRenderWidth() / (GRID_SIZE - 1));
        int cell_height = ceil(1.0 * GetRenderHeight() / (GRID_SIZE - 1));

        // Update the information on the window size and cell size of the grid in case the user resized the window. Draw the grid.
        map.SetWindowSize(GetRenderWidth(), GetRenderHeight());
        map.SetCellSize(cell_width, cell_height);
        map.Draw();

        if (show_help) {
            // Draw the help box on the center of the screen, based on the text size.
            Vector2 txt_size = MeasureTextEx(GetFontDefault(), HELP_TEXT, FONT_SIZE, SPACING);
            DrawRectangle(GetRenderWidth() / 2 - txt_size.x / 2 - BG_MARGIN / 2, GetRenderHeight() / 2 - txt_size.y / 2 - BG_MARGIN / 2, txt_size.x + BG_MARGIN, txt_size.y + BG_MARGIN, WHITE);
            DrawTextEx(GetFontDefault(), HELP_TEXT, { GetRenderWidth() / 2 - txt_size.x / 2, GetRenderHeight() / 2 - txt_size.y / 2 }, FONT_SIZE, SPACING, BLACK);
        }

        // Send the frame buffer for drawing on the screen.
        EndDrawing();

        if (!path_search) {
            // Handle all the mouse events in the grid, only if the search isn't running.
            map.HandleMouseEvents();
        }

        if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && IsKeyPressed(KEY_SLASH)) {
            // In case the question mark has been pressed, stop showing the help text if its currently shown, or start showing it again if it isn't shown.
            show_help = !show_help;
        }

        // Pick a path searching algorithm, and reset the previously picked one.
        if (IsKeyPressed(KEY_ONE) && !path_search) {
            path_finding_algorithm->Reset();
            path_finding_algorithm = &bfs_algorithm;
        }
        else if (IsKeyPressed(KEY_TWO) && !path_search) {
            path_finding_algorithm->Reset();
            path_finding_algorithm = &dfs_algorithm;
        }
        else if (IsKeyPressed(KEY_THREE) && !path_search) {
            path_finding_algorithm->Reset();
            path_finding_algorithm = &dijkstras_algorithm;
        }
        else if (IsKeyPressed(KEY_FOUR) && !path_search) {
            path_finding_algorithm->Reset();
            path_finding_algorithm = &astar_algorithm;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            if (path_search && !path_finding_algorithm->IsDone() || path_finding_algorithm->IsDone()) {
                // If we pressed space and the algorithm finished, or if the algorithm is running, reset it.
                path_finding_algorithm->Reset();
                path_search = false;
            }
            else if (map.GetStartCellPoint().IsValid() && map.GetEndCellPoint().IsValid()) {
                // If we picked a different algorithm to run, prepare it, and start running it, only if the user has placed the starting and ending cell.
                path_finding_algorithm->Prepare();
                path_search = true;
            }
        }
    }

    return 0;
}

