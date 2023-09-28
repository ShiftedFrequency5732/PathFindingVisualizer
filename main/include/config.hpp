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
    constexpr const char* HELP_TEXT = "Keyboard Hotkeys:\nW + Left Mouse - Walls\nN + Left Mouse - Empty Cells\nS + Left Mouse - Start Cell\nE + Left Mouse - End Cell\n1 - Breadth First Search\n2 - Depth First Search\n3 - Dijkstra's Algorithm\n4 - A* Algorithm\nSpace - Run / Stop / Clear\n? - Toggle Help\n\nMouse Right - Move in space\nMouse Wheel - Zoom";

    // Grid related constants.
    constexpr int GRID_SIZE = 150;
    constexpr int GAP_PX = 3;
}
