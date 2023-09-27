#pragma once

#include <stack>

#include "./cell_point.hpp"
#include "./algorithm.hpp"

namespace Algorithms {
    class DFS : public GraphSearchAlgorithm {
    private:
        std::stack<CellPoint> cells;

    public:
        using GraphSearchAlgorithm::GraphSearchAlgorithm;

        void Prepare();
        void Step();
    };
}

