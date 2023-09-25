#pragma once

#include <stack>

#include "./cell_point.hpp"
#include "./algorithm.hpp"

class DFS : public Algorithm {
private:
    std::stack<CellPoint> cells;

public:
    using Algorithm::Algorithm;

    void Prepare();
    bool Step();
};

