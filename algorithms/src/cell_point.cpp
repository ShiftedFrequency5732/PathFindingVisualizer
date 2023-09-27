#include "../include/cell_point.hpp"
#include "../../main/include/config.hpp"

using Constants::GRID_SIZE;

CellPoint::CellPoint(int i, int j) {
    this->head = 0;
    this->i = i;
    this->j = j;
}

int CellPoint::I() const {
    return this->i;
}

int CellPoint::J() const {
    return this->j;
}

bool CellPoint::IsValid() {
    // The CellPoint is valid if it would be in the bounds of the grid.
    return (this->i >= 0 && this->i < GRID_SIZE && this->j >= 0 && this->j < GRID_SIZE);
}

CellPoint CellPoint::GetNextNeighbor() {
    CellPoint points[] = { CellPoint(this->i - 1, this->j), CellPoint(this->i + 1, this->j), CellPoint(this->i, this->j - 1), CellPoint(this->i, this->j + 1) };

    while (this->head < 4) {
        // Pick the first neighbor we didn't that is valid. The head points to the neighbor that we can pick if it is valid.
        if (points[this->head].IsValid()) {
            return points[this->head++];
        }
        ++this->head;
    }

    // Return invalid CellPoint if we can't pick anything.
    return CellPoint(-1, -1);
}

bool operator == (const CellPoint& a, const CellPoint& b) {
    return (a.i == b.i && a.j == b.j);
}

bool operator != (const CellPoint& a, const CellPoint& b) {
    return (a.i != b.i || a.j != b.j);
}

