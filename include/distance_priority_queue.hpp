#pragma once

#include <queue>
#include "../include/cell_point.hpp"

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
