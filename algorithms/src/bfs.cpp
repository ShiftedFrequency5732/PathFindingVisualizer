#include "../include/bfs.hpp"

namespace Algorithms {
    void BFS::Prepare() {
        // Clear the queue, and add the starting cell to the queue.
        this->cells = std::queue<CellPoint>();
        this->cells.push(this->map.GetStartCellPoint());
    }

    void BFS::Step() {
        if (!this->cells.empty()) {
            // If we have cells to visit, take one from the queue.
            CellPoint current_cell = this->cells.front();
            this->cells.pop();

            if (current_cell == this->map.GetEndCellPoint()) {
                // If we have found the end cell, set that we are done.
                this->finished = true;
                return;
            }

            // Mark that we visited this cell.
            this->states[current_cell.I()][current_cell.J()] = CellState::VISITED;

            if (this->map.GetCell(current_cell.I(), current_cell.J()).GetType() == Cell::CellType::EMPTY) {
                // If the current cell is empty cell, set its fill color to be blue to indicate that it has been processed.
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
                if (neighbor_cell.GetType() != Cell::CellType::WALL && this->states[neighbor.I()][neighbor.J()] == CellState::UNVISITED) {
                    // If the neighbor we found isn't a wall, and if it is unvisited, store that we can get to the neighbour through the current cell.
                    // Because we are dealing here with only unvisited cells (states: TO_VISIT and VISITED) are skipped, in the queue we won't have any duplicats.
                    this->trace[neighbor.I()][neighbor.J()] = current_cell;

                    // Mark that this cell will be visited in the future, and color it yellow if it is empty (isn't start / end cell).
                    this->states[neighbor.I()][neighbor.J()] = CellState::TO_VISIT;
                    if (neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                        neighbor_cell.SetFillColor(YELLOW);
                    }

                    // Push the neighobr to the queue.
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
