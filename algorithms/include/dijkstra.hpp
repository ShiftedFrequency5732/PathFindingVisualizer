#pragma once

#include "./algorithm.hpp"
#include "./cell_point.hpp"
#include "./distance_priority_queue.hpp"

namespace Algorithms {
    class Dijkstra : public GraphSearchAlgorithm {
    private:
        DistanceQueue cells;
        int distance[GRID_SIZE][GRID_SIZE];

    public:
        static constexpr int MAX_DISTANCE = 10000;

        using GraphSearchAlgorithm::GraphSearchAlgorithm;

        void Prepare();
        void Step();
    };
}
