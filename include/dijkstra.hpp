#pragma once

#include "./algorithm.hpp"
#include "./cell_point.hpp"
#include "./distance_priority_queue.hpp"

class Dijkstra : public Algorithm {
private:
    DistanceQueue cells;

    int distance[GRID_SIZE][GRID_SIZE];
    bool prepared = false;

public:
    static constexpr int MAX_DISTANCE = 10000;

    using Algorithm::Algorithm;

    void Prepare();
    void Step();
};

