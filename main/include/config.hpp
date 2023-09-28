#pragma once

namespace Constants {
    // Window related constants.
    constexpr int INITIAL_WIDTH = 1000;
    constexpr int INITIAL_HEIGHT = 1000;
    constexpr const char* WINDOW_TITLE = "Path Finding Visualizer - By JV";

    // Help related constants.
    constexpr int SPACING = 1;
    constexpr int FONT_SIZE = 40;
    constexpr int BG_MARGIN = 25;
    constexpr const char* HELP_TEXT = "W + Left Mouse - Wall Cells\nN + Left Mouse - Empty Cells\nS + Left Mouse - Start Cell\nE + Left Mouse - End Cell\n1 - Breadth First Search\n2 - Depth First Search\n3 - Dijkstra's Algorithm\n4 - A* Algorithm\nSpace - Run / Stop / Clear\n? - Toggle Help\nCtrl + Mouse Left - Move In Space\nCtrl + Mouse Wheel - Zoom\nR - Reset Zoom & Location";

    // Grid related constants.
    constexpr int GAP_PX = 5;
    constexpr int GRID_SIZE = 150;

    // Zoom & Panning related constants.
    constexpr float ZOOM = 0.10f;
    constexpr float ZOOM_LOWER_BOUND = 0.01f;
    constexpr float ZOOM_UPPER_BOUND = 5.0f;
}
