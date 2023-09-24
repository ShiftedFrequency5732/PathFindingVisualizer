#pragma once

#include <queue>
#include <vector>

#include "../include/cell_point.hpp"
#include "../include/algorithm.hpp"
#include "../include/distance_priority_queue.hpp"

class AStar : public Algorithm {
private:
    DistanceQueue cells;

    int** gValue;
    bool prepared = false;

public:
    AStar(Grid* grid);

    void Prepare();
    bool Step();
};