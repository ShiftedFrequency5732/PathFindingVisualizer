#pragma once

#include "../../main/include/config.hpp"
#include "./cell.hpp"
#include "./cell_point.hpp"
#include "./grid.hpp"

using Constants::GRID_SIZE;

namespace Algorithms {
    class GraphSearchAlgorithm {
    protected:
        enum class CellState { UNVISITED, TO_VISIT, VISITED };

        Grid* map;

        CellState visited[GRID_SIZE][GRID_SIZE];
        CellPoint trace[GRID_SIZE][GRID_SIZE];

        bool finished;

    public:
        GraphSearchAlgorithm(Grid* map);

        virtual bool IsDone();
        virtual void GetPath();
        virtual void Reset();

        virtual void Prepare() = 0;
        virtual void Step() = 0;
    };
}

