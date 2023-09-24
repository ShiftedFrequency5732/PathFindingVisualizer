#pragma once

class CellPoint {
private:
    int i, j;
    int head;

public:
    CellPoint(int i = 0, int j = 0);

    int I() const;
    int J() const;

    bool IsValid();
    CellPoint GetNextNeighbor();

    friend bool operator == (const CellPoint& a, const CellPoint& b);
    friend bool operator != (const CellPoint& a, const CellPoint& b);
};
