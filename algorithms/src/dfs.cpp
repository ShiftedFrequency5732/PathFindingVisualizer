
#include "../include/dfs.hpp"
#include <iostream>

namespace Algorithms {
    static void clear(std::stack<CellPoint> &cells) {
        // Clear the stack by swapping the passed one with the empty one.
        std::stack<CellPoint> clean_queue;
        std::swap(cells, clean_queue);
    }

    void DFS::Prepare() {
        // Clear the stack, and add the starting cell to the stack.
        clear(this->cells);
        if (this->map) {
            cells.push(map->GetStartCellPoint());
        }
    }

    void DFS::Step() {
        if (!cells.empty()) {
            CellPoint current_cell = cells.top();
            cells.pop();

            if (current_cell == this->map->GetEndCellPoint()) {
                // If we have found the end cell, set that we are done.
                this->finished = true;
                return;
            }

            while (this->visited[current_cell.I()][current_cell.J()] == CellState::VISITED) {
                // If we took out from the stack the cell that we have already visited, try taking another one. If we couldn't find any, that means we have visited all the cells.
                // Many cells can share neighbors, because of that there would be many empty steps in the process of running this algorithm.
                // We could have ignored the neighbors that are in the state of TO_VISIT as well instead, in the loop below.
                if (cells.empty()) {
                    this->finished = true;
                    return;
                }
                current_cell = cells.top();
                cells.pop();
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
                    if (neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                        neighbor_cell.SetFillColor(YELLOW);
                    }

                    // Push it to the stack.
                    cells.push(neighbor);
                }
            }

            // As we didn't find the end cell, return and try again.
            return;
        }

        // In case the queue is empty, algorithm finished running.
        this->finished = true;
    }
}
