
#include "../include/dfs.hpp"
#include <iostream>

namespace Algorithms {
    void DFS::Prepare() {
        // Clear the stack, and add the starting cell to the stack.
        this->cells = std::stack<CellPoint>();
        this->cells.push(map.GetStartCellPoint());
    }

    void DFS::Step() {
        if (!this->cells.empty()) {
            // If we have cells to visit, take one from the stack.
            CellPoint current_cell = this->cells.top();
            this->cells.pop();

            if (current_cell == this->map.GetEndCellPoint()) {
                // If we have found the end cell, set that we are done.
                this->finished = true;
                return;
            }

            // Mark that we visited this cell.
            this->states[current_cell.I()][current_cell.J()] = CellState::VISITED;

            if (this->map.GetCell(current_cell.I(), current_cell.J()).GetType() == Cell::CellType::EMPTY) {
                // If the current cell is an empty cell, set its fill color to be blue to indicate that it has been processed.
                this->map.GetCell(current_cell.I(), current_cell.J()).SetFillColor(BLUE);
            }

            while (true) {
                // Go through all the neighbors of the current cell.
                CellPoint neighbor = current_cell.GetNextNeighbor();

                if (!neighbor.IsValid()) {
                    // If the current cell doesn't have any neighbors left, quit the loop.
                    break;
                }

                Cell& neighbor_cell = this->map.GetCell(neighbor.I(), neighbor.J());
                if (neighbor_cell.GetType() != Cell::CellType::WALL && states[neighbor.I()][neighbor.J()] == CellState::UNVISITED) {
                    // If the neighbor we found isn't a wall, and if it is unvisited, store that we can get to the neighbour through the current cell.
                    this->trace[neighbor.I()][neighbor.J()] = current_cell;

                    // Mark that this cell will be visited in the future, and color it yellow if it is empty (isn't start / end cell).
                    this->states[neighbor.I()][neighbor.J()] = CellState::TO_VISIT;
                    if (neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                        neighbor_cell.SetFillColor(YELLOW);
                    }

                    // Push it to the stack.
                    this->cells.push(neighbor);
                }
            }

            // As we didn't find the end cell, return and try again.
            return;
        }

        // In case the queue is empty, algorithm finished running.
        this->finished = true;
    }
}
