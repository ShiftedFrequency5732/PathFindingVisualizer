#pragma once

#include <queue>
#include <vector>

#include "../include/cell_point.hpp"
#include "../include/algorithm.hpp"
#include "../include/distance_priority_queue.hpp"

class Dijkstra : public Algorithm {
private:
    DistanceQueue cells;

    int** distance;
    bool prepared = false;

public:
    Dijkstra(Grid* grid);

    void Prepare();
    bool Step();
};