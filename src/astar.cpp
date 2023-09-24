
#include "../include/astar.hpp"
#include <cmath>

AStar::AStar(Grid* grid) : Algorithm(grid) {
    this->gValue = new int*[this->grid_size];
    for(int i = 0; i < this->grid_size; ++i) {
        this->gValue[i] = new int[this->grid_size];
    }
}

static void clear(DistanceQueue &cells) {
    DistanceQueue clean_queue;
    std::swap(cells, clean_queue);
}

void AStar::Prepare() {
    clear(this->cells);
    cells.push({ 0, grid->GetStartCellPoint() });
    for(int i = 0; i < this->grid_size; ++i) {
        for(int j = 0; j < this->grid_size; ++j) {
            this->gValue[i][j] = 100000;
        }
    }
    this->gValue[grid->GetStartCellPoint().I()][grid->GetStartCellPoint().J()] = 0;
}

static int hValue(CellPoint p1, CellPoint p2) {
    return sqrt(pow(p1.I() - p2.I(), 2) + pow(p1.J() - p2.J(), 2));
    // return abs(p1.I() - p2.I()) + abs(p1.J() - p2.J());
}

bool AStar::Step() {
    if (!cells.empty()) {
        CellPoint cell = cells.top().second;
        cells.pop();

        if (cell == this->grid->GetEndCellPoint()) {
            return true;
        }

        if (this->visited[cell.I()][cell.J()] == CellState::VISITED) {
            return false;
        }

        visited[cell.I()][cell.J()] = CellState::VISITED;

        if (grid->GetCell(cell.I(), cell.J()).GetType() == Cell::CellType::EMPTY) {
            grid->GetCell(cell.I(), cell.J()).SetFillColor(BLUE);
        }

        while (true) {
            CellPoint neighbor = cell.GetNextNeighbor();
            if (!neighbor.IsValid()) {
                break;
            }
            Cell& neighbor_cell = this->grid->GetCell(neighbor.I(), neighbor.J());

            if (neighbor_cell.GetType() != Cell::CellType::WALL && visited[neighbor.I()][neighbor.J()] == CellState::UNVISITED) {
                if (gValue[neighbor.I()][neighbor.J()] > gValue[cell.I()][cell.J()] + 1) {
                    gValue[neighbor.I()][neighbor.J()] = gValue[cell.I()][cell.J()] + 1;
                    trace[neighbor.I()][neighbor.J()] = cell;
                    visited[neighbor.I()][neighbor.J()] = CellState::TOVISIT;
                    if(neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                        neighbor_cell.SetFillColor(YELLOW);
                    }
                    cells.push({ gValue[neighbor.I()][neighbor.J()] + hValue(neighbor, this->grid->GetEndCellPoint()), neighbor });
                }
            }
        }

        return false;
    }

    return true;
}