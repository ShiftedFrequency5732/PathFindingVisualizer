#include "../include/cell_point.hpp"

CellPoint::CellPoint(int i, int j) {
    this->i = i;
    this->j = j;
}

int CellPoint::GetI() const {
    return this->i;
}

int CellPoint::GetJ() const {
    return this->j;
}

bool operator == (const CellPoint& a, const CellPoint& b) {
    return (a.i == b.i && a.j == b.j);
}

bool operator != (const CellPoint& a, const CellPoint& b) {
    return (a.i != b.i || a.j != b.j);
}
