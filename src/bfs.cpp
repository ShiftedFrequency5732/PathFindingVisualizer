#include "../include/bfs.hpp"
#include <iostream>

void BFS::Prepare() {
    if(!prepared) {
        cells.push(grid->GetStartCellPoint());
        prepared = true;
    }
}

bool BFS::Step() {
    if (!cells.empty()) {
        CellPoint cell = cells.front();
        cells.pop();

        if (cell == this->grid->GetEndCellPoint()) {
            return false;
        }

        if (this->visited[cell.I()][cell.J()] == CellState::VISITED) {
            return true;
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
                cells.push(neighbor);
                trace[neighbor.I()][neighbor.J()] = cell;
                visited[neighbor.I()][neighbor.J()] = CellState::TOVISIT;
                if(neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                    neighbor_cell.SetFillColor(YELLOW);
                }
            }
        }

        return true;
    }

    return false;
}