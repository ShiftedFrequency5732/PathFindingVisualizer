#pragma once

#include "../include/cell.hpp"
#include "../include/point.hpp"

class Grid {
public:
    Grid(int grid_size);

    void SetMargin(int margin);
    void SetCellSize(int cell_width, int cell_height);
    void SetWindowSize(int window_width, int window_height);

    int getSize();

    Point GetStartCell();
    Point GetEndCell();
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

    Point start_cell, end_cell;
    Vector2 mouse_prev, mouse_curr;

    void MousePickStartOrEndCell();
    void MouseDrawWallOrEmptyCells();
};

