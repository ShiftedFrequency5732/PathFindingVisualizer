#pragma once

#include "../include/config.hpp"
#include "../include/cell.hpp"
#include "../include/cell_point.hpp"
#include "../include/grid.hpp"

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

    // This method, should return true, if the path has been found or if the algorithm finished running.
    virtual bool Step() = 0;
};

