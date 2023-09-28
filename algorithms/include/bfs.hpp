#pragma once

#include <queue>

#include "./cell_point.hpp"
#include "./algorithm.hpp"

namespace Algorithms {
    class BFS : public GraphSearchAlgorithm {
    private:
        std::queue<CellPoint> cells;

    public:
        using GraphSearchAlgorithm::GraphSearchAlgorithm;

        void Prepare();
        void Step();
    };
}
