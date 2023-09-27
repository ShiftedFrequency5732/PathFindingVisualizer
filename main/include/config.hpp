#pragma once

namespace Constants {
    // Window related constants.
    constexpr int INITIAL_WIDTH = 800;
    constexpr int INITIAL_HEIGHT = 800;
    constexpr const char* WINDOW_TITLE = "Path Finding Visualizer";

    // Help related constants.
    constexpr int SPACING = 1;
    constexpr int FONT_SIZE = 40;
    constexpr int BG_MARGIN = 25;
    constexpr const char* HELP_TEXT = "W + Left Mouse Button - Walls\nN + Left Mouse Button - Empty Cells\nS + Left Mouse Button - Start Cell\nE + Left Mouse Button - End Cell\n1 - Breadth First Search\n2 - Depth First Search\n3 - Dijkstra's Algorithm\n4 - A* Algorithm\nSpace - Run / Stop / Clear\n? - Toggle Help";

    // Grid related constants.
    constexpr int GRID_SIZE = 50;
    constexpr int MARGIN_PX = 1;
}

