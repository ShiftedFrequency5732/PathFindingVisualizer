
#include "../include/dfs.hpp"
#include <iostream>

static void clear(std::stack<CellPoint> &cells) {
    std::stack<CellPoint> clean_queue;
    std::swap(cells, clean_queue);
}

void DFS::Prepare() {
    clear(this->cells);
    cells.push(grid->GetStartCellPoint());
}

bool DFS::Step() {
    if (!cells.empty()) {
        CellPoint cell = cells.top();
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

            if (neighbor_cell.GetType() != Cell::CellType::WALL && visited[neighbor.I()][neighbor.J()] != CellState::VISITED) {
                trace[neighbor.I()][neighbor.J()] = cell;
                visited[neighbor.I()][neighbor.J()] = CellState::TOVISIT;
                if(neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                    neighbor_cell.SetFillColor(YELLOW);
                }
                cells.push(neighbor);
            }
        }

        return false;
    }

    return true;
}