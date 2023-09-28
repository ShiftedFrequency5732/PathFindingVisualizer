#pragma once

#include "./cell.hpp"
#include "./cell_point.hpp"
#include "../../main/include/config.hpp"

using Constants::GRID_SIZE;

namespace Algorithms {
    class Grid {
    public:
        Grid();

        void SetCellSize(int cell_size);
        void SetWindowSize(int window_width, int window_height);
        void Draw();

        Cell& GetCell(int i, int j);
        CellPoint GetStartCellPoint() const;
        CellPoint GetEndCellPoint() const;

        void MouseZoomAndPan();
        void MouseSetStartOrEndCell();
        void MouseSetWallsOrEmptyCells();

    private:
        CellPoint start_cell, end_cell;

        int window_width, window_height;
        Cell matrix[GRID_SIZE][GRID_SIZE];
        int cell_size;

        Vector2 start_pan;
        Vector2 mouse_prev, mouse_curr;
        Vector2 mouse_prev_wld, mouse_curr_wld;

        Vector2 offset, scale;
        Vector2 ScreenToWorld(Vector2 scr);
        Vector2 WorldToScreen(Vector2 wld);
    };
}

