#pragma once

#include "../../main/include/config.hpp"

#include "./cell_point.hpp"
#include "./cell.hpp"

using Constants::GRID_SIZE;

namespace Algorithms {
    class Grid {
    public:
        Grid();

        void SetCellSize(int cell_size);
        void Draw();

        Cell& GetCell(int i, int j);
        CellPoint GetStartCellPoint() const;
        CellPoint GetEndCellPoint() const;

        void MouseSetStartOrEndCell();
        void MouseSetWallsOrEmptyCells();

        void MouseZoomAndPan();
        void ResetZoomAndPan();

        float GetGridSize() const;

    private:
        CellPoint start_cell, end_cell;
        Cell matrix[GRID_SIZE][GRID_SIZE];
        int cell_size;

        Vector2 mouse_prev, mouse_curr;

        Vector2 start_pan;
        Vector2 offset, scale;

        Vector2 ScreenToWorld(Vector2 scr);
        Vector2 WorldToScreen(Vector2 wld);
    };
}

