#include "../include/dijkstra.hpp"

namespace Algorithms {
    void Dijkstra::Prepare() {
        // Clear the queue.
        this->cells = DistanceQueue();

        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                // At the start, assume the distance from the starting node to all the other nodes is infinite.
                this->distance[i][j] = Dijkstra::MAX_DISTANCE;
            }
        }

        // The distnace from the start to the start is zero obviously.
        this->distance[map.GetStartCellPoint().I()][map.GetStartCellPoint().J()] = 0;

        // Push the starting cell to the queue with the distance of zero.
        cells.push({ 0, map.GetStartCellPoint() });
    }

    void Dijkstra::Step() {
        if (!this->cells.empty()) {
            // Take the cell with the least distance from the starting node from the queue.
            CellPoint current_cell = this->cells.top().second;
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
                    if (distance[neighbor.I()][neighbor.J()] > distance[current_cell.I()][current_cell.J()] + 1) {
                        // If the neighbor we found isn't a wall, and if it is unvisited, and if we can get to the neighbor through the current cell with a shorter distance than from the starting cell.
                        // Then store that new distance, and store the current cell as the previous (parent) cell of the neighbor.
                        this->distance[neighbor.I()][neighbor.J()] = this->distance[current_cell.I()][current_cell.J()] + 1;
                        this->trace[neighbor.I()][neighbor.J()] = current_cell;

                        // In case the neighboring cell is empty, color it yellow to indicate that it will be processed.
                        this->states[neighbor.I()][neighbor.J()] = CellState::TO_VISIT;
                        if (neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                            neighbor_cell.SetFillColor(YELLOW);
                        }

                        // Push the neighobr to the queue.
                        this->cells.push({ distance[neighbor.I()][neighbor.J()], neighbor });
                    }
                }
            }

            // As we didn't find the end cell, return and try again.
            return;
        }

        // In case the queue is empty, algorithm finished running.
        this->finished = true;
    }
}
