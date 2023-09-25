#pragma once

#include "./cell.hpp"
#include "./cell_point.hpp"
#include "./config.hpp"

class Grid {
public:
    Grid();

    void SetCellSize(int cell_width, int cell_height);
    void SetWindowSize(int window_width, int window_height);

    Cell& GetCell(int i, int j);
    CellPoint GetStartCellPoint() const;
    CellPoint GetEndCellPoint() const;

    void HandleMouseEvents();
    void Draw();

private:
    Cell matrix[GRID_SIZE][GRID_SIZE];

    int margin;
    int cell_width, cell_height;
    int window_width, window_height;

    CellPoint start_cell, end_cell;

    Vector2 mouse_prev, mouse_curr;
    void MousePickStartOrEndCell();
    void MouseDrawWallOrEmptyCells();
};

