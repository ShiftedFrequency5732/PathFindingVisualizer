#pragma once

class Point {
private:
    int i, j;

public:
    Point(int i = 0, int j = 0);

    int getI() const;
    int getJ() const;

    friend bool operator == (const Point& a, const Point& b);
    friend bool operator != (const Point& a, const Point& b);
};
