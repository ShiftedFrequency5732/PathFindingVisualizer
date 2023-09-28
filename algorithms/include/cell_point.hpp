#pragma once

namespace Algorithms {
    class CellPoint {
    private:
        int i, j;
        mutable int head;

    public:
        CellPoint(int i = 0, int j = 0);

        int I() const;
        int J() const;

        bool IsValid() const;
        CellPoint GetNextNeighbor() const;

        friend bool operator == (const CellPoint& a, const CellPoint& b);
        friend bool operator != (const CellPoint& a, const CellPoint& b);
    };
}
