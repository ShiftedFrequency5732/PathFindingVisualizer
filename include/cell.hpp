#pragma once

#include "../include/raylib.h"

class Cell {
public:
    enum class CellType { EMPTY = 0, WALL = 1, START = 2, END = 3 };

    Cell();

    void SetType(CellType type);
    CellType GetType() const;

    void SetFillColor(Color fill);
    Color GetFillColor() const;

private:
    CellType type;
    Color fill;
};
