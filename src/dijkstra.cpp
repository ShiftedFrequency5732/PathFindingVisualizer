#include "../include/dijkstra.hpp"
#include <iostream>

void Dijkstra::Prepare() {
    // Clear the queue.
    clear(this->cells);

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            // At the start, assume the distance from the starting node to all the other nodes is infinite.
            this->distance[i][j] = Dijkstra::MAX_DISTANCE;
        }
    }

    if (this->map) {
        // Push the starting cell to the queue with the distance of zero, and set the distance to this starting node to be zero.
        // The distnace from the start to the start is zero obviously.
        cells.push({ 0, map->GetStartCellPoint() });
        this->distance[map->GetStartCellPoint().I()][map->GetStartCellPoint().J()] = 0;
    }
}

bool Dijkstra::Step() {
    if (!cells.empty()) {
        CellPoint current_cell = cells.top().second;
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
                if (distance[neighbor.I()][neighbor.J()] > distance[current_cell.I()][current_cell.J()] + 1) {
                    // If the neighbor we found isn't a wall, and if it is unvisited, and if we can get to the neighbor through the current cell with a shorter distance from the starting cell.
                    // Then store that new distance, and store the current cell as the previous cell of the neighbor.
                    distance[neighbor.I()][neighbor.J()] = distance[current_cell.I()][current_cell.J()] + 1;
                    trace[neighbor.I()][neighbor.J()] = current_cell;

                    // In case the neighboring cell is empty, color it yellow to indicate that it will be processed.
                    visited[neighbor.I()][neighbor.J()] = CellState::TO_VISIT;
                    if (neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                        neighbor_cell.SetFillColor(YELLOW);
                    }

                    // Push it to the queue.
                    cells.push({ distance[neighbor.I()][neighbor.J()], neighbor });
                }
            }
        }

        // As we didn't find the end cell, return false, that we didn't finish.
        return false;
    }

    // In case the queue is empty, algorithm finished running.
    return true;
}

