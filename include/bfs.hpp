#pragma once

#include <queue>

#include "../include/cell_point.hpp"
#include "../include/algorithm.hpp"

class BFS : public Algorithm {
private:
    std::queue<CellPoint> cells;

public:
    using Algorithm::Algorithm;

    void Prepare();
    bool Step();
};

