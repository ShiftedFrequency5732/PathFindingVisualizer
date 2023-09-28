#include "../include/config.hpp"

#include "../../raylib/include/raylib.h"
#include "../../raylib/include/raymath.h"

#include "../../algorithms/include/grid.hpp"
#include "../../algorithms/include/bfs.hpp"
#include "../../algorithms/include/dfs.hpp"
#include "../../algorithms/include/dijkstra.hpp"
#include "../../algorithms/include/astar.hpp"

using Constants::INITIAL_WIDTH;
using Constants::INITIAL_HEIGHT;
using Constants::WINDOW_TITLE;

using Constants::BG_MARGIN;
using Constants::HELP_TEXT;
using Constants::FONT_SIZE;
using Constants::SPACING;

using Constants::GRID_SIZE;

int main() {
    // Initialize the basic window, set the width, the height, the title, the target FPS, and make it resizable.
    InitWindow(INITIAL_WIDTH, INITIAL_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Boolean flag that indicates whether to show the help text or not.
    bool show_help = true;

    // The grid object that holds all the cells.
    Algorithms::Grid map;

    // Calculate the cell size, we want to see 1/8th of all the cells, and set the initial zoom & location at the center.
    int cell_size = ceil(1.0 * std::max(GetRenderWidth(), GetRenderHeight()) / GRID_SIZE * 8);
    map.SetCellSize(cell_size);
    map.ResetZoomAndPan();

    // Algorithms that will perform the path search.
    Algorithms::BFS bfs_algorithm(map);
    Algorithms::DFS dfs_algorithm(map);
    Algorithms::Dijkstra dijkstras_algorithm(map);
    Algorithms::AStar astar_algorithm(map);

    // Pointer to the currently selected algorithm, and flag that indicates whether to perform search, and if path has been found or not.
    Algorithms::GraphSearchAlgorithm* path_finding_algorithm = &bfs_algorithm;
    bool path_search = false, path_found = false;

    while (!WindowShouldClose()) {
        // Start preparing the frame buffer for drawing, and clear the screen from the previous drawing.
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (path_search && !path_found) {
            // Step the current path searching algorithm in case it isn't done, otherwise draw the path and finish.
            if (!path_finding_algorithm->IsDone()) {
                path_finding_algorithm->Step();
            }
            else {
                path_finding_algorithm->GetPath();
                path_found = true;
            }
        }

        // Update the information on the cell size of the grid in case the user resized the window. Draw the grid.
        cell_size = ceil(1.0 * std::max(GetRenderWidth(), GetRenderHeight()) / GRID_SIZE * 8);
        map.SetCellSize(cell_size);
        map.Draw();

        if (show_help) {
            // Draw the help box on the center of the screen (take half of A and half of B and subtract them, simple as that), based on the text size.
            Vector2 txt_size = MeasureTextEx(GetFontDefault(), HELP_TEXT, FONT_SIZE, SPACING);
            Vector2 upper_left = { GetRenderWidth() / 2 - txt_size.x / 2, GetRenderHeight() / 2 - txt_size.y / 2 };
            DrawRectangle(upper_left.x - BG_MARGIN / 2, upper_left.y - BG_MARGIN / 2, txt_size.x + BG_MARGIN, txt_size.y + BG_MARGIN, WHITE);
            DrawTextEx(GetFontDefault(), HELP_TEXT, upper_left, FONT_SIZE, SPACING, BLACK);
        }

        // Send the frame buffer for drawing on the screen.
        EndDrawing();

        if (!path_search) {
            // In case no algorithm is running, allow the user to set the walls / empty cells or starting and ending node.
            map.MouseSetWallsOrEmptyCells();
            map.MouseSetStartOrEndCell();
        }

        if (!show_help) {
            // Allow user to perform the zooming & panning, only in case the help isn't shown.
            map.MouseZoomAndPan();
        }

        if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && IsKeyPressed(KEY_SLASH)) {
            // In case the question mark has been pressed, toggle the help.
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
            if ((path_search && !path_finding_algorithm->IsDone()) || path_finding_algorithm->IsDone()) {
                // If we pressed space and the algorithm finished, or if the algorithm is running, reset it.
                path_finding_algorithm->Reset();
                path_search = false;
            }
            else if (map.GetStartCellPoint().IsValid() && map.GetEndCellPoint().IsValid()) {
                // If we picked a different algorithm to run, prepare it, and start running it, only if the user has placed the starting and the ending cell.
                path_finding_algorithm->Prepare();
                path_search = true;
            }
            path_found = false;
            show_help = false;
        }

        if (IsKeyPressed(KEY_R)) {
            // If the user has pressed R, center him on the screen and reset the scale.
            map.ResetZoomAndPan();
        }
    }

    return 0;
}
