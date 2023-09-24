#pragma once

#include <stack>
#include "../include/cell_point.hpp"
#include "../include/algorithm.hpp"

class DFS : public Algorithm {
private:
    std::stack<CellPoint> cells;
    bool prepared = false;

public:
    using Algorithm::Algorithm;

    void Prepare();
    bool Step();
};