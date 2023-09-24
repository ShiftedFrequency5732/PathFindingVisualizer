#include "../include/cell.hpp"

Cell::Cell() {
    // Default values.
    this->type = CellType::EMPTY;
    this->fill = BLACK;
}

void Cell::SetType(CellType type) {
    this->type = type;

    // If you change the type of the cell, you also change its fill color.
    switch (this->type) {
        case CellType::WALL:
            this->fill = WHITE;
            break;

        case CellType::START:
            this->fill = GREEN;
            break;

        case CellType::END:
            this->fill = RED;
            break;

        default:
            this->fill = BLACK;
            break;
    }
}

Cell::CellType Cell::GetType() const {
    return this->type;
}

void Cell::SetFillColor(Color fill) {
    this->fill = fill;
}

Color Cell::GetFillColor() const {
    return this->fill;
}
