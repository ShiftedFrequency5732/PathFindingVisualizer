#include "../include/cell.hpp"

Cell::Cell() {
    // Default values.
    this->type = CellType::EMPTY;
    this->fill = BLACK;
}

void Cell::setType(CellType type) {
    this->type = type;

    // If you change the type, you also change the fill color.
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

Cell::CellType Cell::getType() const {
    return this->type;
}

void Cell::setFillColor(Color fill) {
    this->fill = fill;
}

Color Cell::getFillColor() const {
    return this->fill;
}
