#pragma once

#include "../include/algorithm.hpp"
#include "../include/cell_point.hpp"
#include "../include/distance_priority_queue.hpp"

class Dijkstra : public Algorithm {
private:
    DistanceQueue cells;

    int distance[GRID_SIZE][GRID_SIZE];
    bool prepared = false;

public:
    static constexpr int MAX_DISTANCE = 10000;

    using Algorithm::Algorithm;

    void Prepare();
    bool Step();
};

