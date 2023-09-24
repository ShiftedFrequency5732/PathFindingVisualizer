#pragma once

#include "../include/cell.hpp"
#include "../include/cell_point.hpp"

class Grid {
public:
    Grid(int grid_size);

    int GetSize();

    void SetMargin(int margin);
    void SetCellSize(int cell_width, int cell_height);
    void SetWindowSize(int window_width, int window_height);

    CellPoint GetStartCellPoint();
    CellPoint GetEndCellPoint();
    Cell& GetCell(int i, int j);

    void HandleMouseEvents();
    void Draw();

    virtual ~Grid();

private:
    int grid_size;
    Cell** matrix;

    int margin;
    int cell_width, cell_height;
    int window_width, window_height;

    CellPoint start_cell, end_cell;
    Vector2 mouse_prev, mouse_curr;

    void MousePickStartOrEndCell();
    void MouseDrawWallOrEmptyCells();
};

