#include "../include/dijkstra.hpp"
#include <iostream>

Dijkstra::Dijkstra(Grid* grid) : Algorithm(grid) {
    this->distance = new int*[this->grid_size];
    for(int i = 0; i < this->grid_size; ++i) {
        this->distance[i] = new int[this->grid_size];
    }
}

static void clear(DistanceQueue &cells) {
    DistanceQueue clean_queue;
    std::swap(cells, clean_queue);
}

void Dijkstra::Prepare() {
    clear(this->cells);
    cells.push({ 0, grid->GetStartCellPoint() });
    for(int i = 0; i < this->grid_size; ++i) {
        for(int j = 0; j < this->grid_size; ++j) {
            this->distance[i][j] = 100000;
        }
    }
    this->distance[grid->GetStartCellPoint().I()][grid->GetStartCellPoint().J()] = 0;
}

bool Dijkstra::Step() {
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
                if (distance[neighbor.I()][neighbor.J()] > distance[cell.I()][cell.J()] + 1) {
                    distance[neighbor.I()][neighbor.J()] = distance[cell.I()][cell.J()] + 1;
                    trace[neighbor.I()][neighbor.J()] = cell;
                    visited[neighbor.I()][neighbor.J()] = CellState::TOVISIT;
                    if(neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                        neighbor_cell.SetFillColor(YELLOW);
                    }
                    cells.push({ distance[neighbor.I()][neighbor.J()], neighbor });
                }
            }
        }

        return false;
    }

    return true;
}