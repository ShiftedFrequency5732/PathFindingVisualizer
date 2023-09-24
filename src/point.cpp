#include "../include/point.hpp"

Point::Point(int i, int j) {
    this->i = i;
    this->j = j;
}

int Point::getI() const {
    return this->i;
}

int Point::getJ() const {
    return this->j;
}

bool operator == (const Point& a, const Point& b) {
    return (a.i == b.i && a.j == b.j);
}

bool operator != (const Point& a, const Point& b) {
    return (a.i != b.i || a.j != b.j);
}
