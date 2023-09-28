#pragma once

#include "../../raylib/include/raylib.h"

namespace Algorithms {
    class Cell {
    public:
        enum class CellType { EMPTY, WALL, START, END };

        Cell();

        void SetType(CellType type);
        CellType GetType() const;

        void SetFillColor(Color fill);
        Color GetFillColor() const;

    private:
        CellType type;
        Color fill;
    };
}
