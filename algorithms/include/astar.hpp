#pragma once

#include "./cell_point.hpp"
#include "./algorithm.hpp"
#include "./distance_priority_queue.hpp"

namespace Algorithms {
    class AStar : public GraphSearchAlgorithm {
    private:
        DistanceQueue cells;
        int gValue[GRID_SIZE][GRID_SIZE];

    public:
        static constexpr int MAX_DISTANCE = 10000;

        using GraphSearchAlgorithm::GraphSearchAlgorithm;

        void Prepare();
        void Step();
    };
}
