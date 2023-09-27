#pragma once

#include "../../main/include/config.hpp"
#include "./cell.hpp"
#include "./cell_point.hpp"
#include "./grid.hpp"

class Algorithm {
protected:
    enum class CellState { UNVISITED, TO_VISIT, VISITED };

    Grid* map;

    CellState visited[GRID_SIZE][GRID_SIZE];
    CellPoint trace[GRID_SIZE][GRID_SIZE];

    bool finished;

public:
    Algorithm(Grid* map);

    virtual bool IsDone();
    virtual void GetPath();
    virtual void Reset();

    virtual void Prepare() = 0;
    virtual void Step() = 0;
};

