#pragma once

#include "../include/raylib.h"

class Cell {
public:
    enum class CellType { EMPTY = 0, WALL = 1, START = 2, END = 3 };

    Cell();

    void setType(CellType type);
    CellType getType() const;

    void setFillColor(Color fill);
    Color getFillColor() const;

private:
    CellType type;
    Color fill;
};
