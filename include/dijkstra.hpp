#pragma once

#include <queue>
#include <vector>

#include "../include/cell_point.hpp"
#include "../include/algorithm.hpp"

typedef std::pair<int, CellPoint> DistanceCell;

class DistanceCellComparator {
public:
    bool operator()(DistanceCell a, DistanceCell b) {
        if(a.first > b.first) {
            return true;
        }
        return false;
    }
};

typedef std::priority_queue<DistanceCell, std::vector<DistanceCell>, DistanceCellComparator> DistanceQueue;

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