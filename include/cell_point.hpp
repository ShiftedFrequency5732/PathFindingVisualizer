#pragma once

class CellPoint {
private:
    int i, j;

public:
    CellPoint(int i = 0, int j = 0);

    int GetI() const;
    int GetJ() const;

    friend bool operator == (const CellPoint& a, const CellPoint& b);
    friend bool operator != (const CellPoint& a, const CellPoint& b);
};
