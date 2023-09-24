#pragma once

#include "../include/cell.hpp"
#include "../include/cell_point.hpp"
#include "../include/grid.hpp"

class Algorithm {
protected:
    enum class CellState { UNVISITED, PROCESSING, VISITED };

    Grid* grid;
    CellState** visited;
    CellPoint** trace;

    bool finished;

public:
    Algorithm(Grid* grid);

    virtual bool IsDone();
    virtual void GetPath();
    virtual void ResetGrid();

    virtual bool Step() = 0;

    virtual ~Algorithm();
};