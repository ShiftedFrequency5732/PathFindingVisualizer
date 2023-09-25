#include "../include/bfs.hpp"
#include <iostream>

static void clear(std::queue<CellPoint> &cells) {
    // Clear the queue, by swapping the full one with the new empty one, the full one will get destroyed as a local variable of this funciton.
    std::queue<CellPoint> clean_queue;
    std::swap(cells, clean_queue);
}

void BFS::Prepare() {
    // Clear the queue, and add the starting cell to the queue.
    clear(this->cells);
    if (this->map) {
        cells.push(this->map->GetStartCellPoint());
    }
}

bool BFS::Step() {
    if (!cells.empty()) {
        CellPoint current_cell = cells.front();
        cells.pop();

        if (current_cell == this->map->GetEndCellPoint()) {
            // Return true that we have found a path.
            return true;
        }

        if (this->visited[current_cell.I()][current_cell.J()] == CellState::VISITED) {
            // If we have visited this cell, skip the current iteration of the algorithm.
            return false;
        }

        // Mark that we visited this cell.
        visited[current_cell.I()][current_cell.J()] = CellState::VISITED;

        if (map->GetCell(current_cell.I(), current_cell.J()).GetType() == Cell::CellType::EMPTY) {
            // If the current cell is empty cell, set its fill color to be blue to indicate that it has been processed.
            map->GetCell(current_cell.I(), current_cell.J()).SetFillColor(BLUE);
        }

        while (true) {
            // Go through all the neighbors of the current cell.
            CellPoint neighbor = current_cell.GetNextNeighbor();

            if (!neighbor.IsValid()) {
                // If the current cell doesn't have any neighbors left, quit the loop.
                break;
            }

            Cell& neighbor_cell = this->map->GetCell(neighbor.I(), neighbor.J());
            if (neighbor_cell.GetType() != Cell::CellType::WALL && visited[neighbor.I()][neighbor.J()] != CellState::VISITED) {
                // If the neighbor we found isn't a wall, and if it is unvisited, store that we can get to the neighbour through the current cell.
                trace[neighbor.I()][neighbor.J()] = current_cell;

                // Mark that this cell will be visited in the future, and color it yellow if it is empty (isn't start / end cell).
                visited[neighbor.I()][neighbor.J()] = CellState::TO_VISIT;
                if(neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                    neighbor_cell.SetFillColor(YELLOW);
                }

                // Push it to the queue.
                cells.push(neighbor);
            }
        }

        // As we didn't find the end cell, return false, that we didn't finish.
        return false;
    }

    // In case the queue is empty, algorithm finished running.
    return true;
}

