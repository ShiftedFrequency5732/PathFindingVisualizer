#pragma once

#include "../../main/include/config.hpp"
#include "./grid.hpp"

namespace Algorithms {
    using Constants::GRID_SIZE;

    class GraphSearchAlgorithm {
    protected:
        enum class CellState { UNVISITED, TO_VISIT, VISITED };

        Grid& map;

        CellState states[GRID_SIZE][GRID_SIZE];
        CellPoint trace[GRID_SIZE][GRID_SIZE];

        bool finished;

    public:
        GraphSearchAlgorithm(Grid& map);

        virtual bool IsDone() const;
        virtual void GetPath() const;
        virtual void Reset();

        virtual void Prepare() = 0;
        virtual void Step() = 0;
    };
}
