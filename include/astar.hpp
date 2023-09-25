#pragma once

#include <queue>
#include <vector>

#include "../include/cell_point.hpp"
#include "../include/algorithm.hpp"
#include "../include/distance_priority_queue.hpp"

class AStar : public Algorithm {
private:
    DistanceQueue cells;

    int gValue[GRID_SIZE][GRID_SIZE];
    bool prepared = false;

public:
    static constexpr int MAX_DISTANCE = 10000;

    using Algorithm::Algorithm;

    void Prepare();
    bool Step();
};

