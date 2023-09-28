#pragma once

#include <queue>

#include "./cell_point.hpp"

namespace Algorithms {
    // Pair of distance and CellPoint that will be stored in the priority queue.
    typedef std::pair<int, Algorithms::CellPoint> DistanceCell;

    class DistanceCellComparator {
    public:
        bool operator() (DistanceCell a, DistanceCell b) {
            // In case the 'a' has greater distance from the starting node than 'b'. Then we want it to come latter in the priority queue, after the 'b'.
            // We return true, because if we would use < instead and return it then, we would keep getting the pairs with maximum distance.
            // That is because by default the priority queue is maximum priority queue, and it thinks that we will use the <.
            // If you want to find the longest distance instead of the shortest, than change this to <.
            return (a.first > b.first);
        }
    };

    // Custom Priority Queue.
    typedef std::priority_queue<DistanceCell, std::vector<DistanceCell>, DistanceCellComparator> DistanceQueue;

    static inline void clear(DistanceQueue &cells) {
        // To clear the priority queue, create a new empty one, and swap the full one with it.
        DistanceQueue clean_queue;
        std::swap(cells, clean_queue);
    }
}
