#include <iostream>

#include "../include/config.hpp"

#include "../include/raylib.h"
#include "../include/raymath.h"
#include "../include/rlgl.h"

int main() {
    // Initialize the basic window.
    InitWindow(INITIAL_WIDTH, INITIAL_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while (!WindowShouldClose()) {
        BeginDrawing();

        // Clear the window from the previous drawings.
        ClearBackground(BLANK);

        EndDrawing();
    }

    return 0;
}
