
#include "../include/astar.hpp"
#include <cmath>

namespace Algorithms {
    void AStar::Prepare() {
        // Clear the queue.
        clear(this->cells);

        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                // At the start, assume the distance from the starting node to all the other nodes is infinite.
                this->gValue[i][j] = AStar::MAX_DISTANCE;
            }
        }

        // Push the starting cell to the queue with the distance of zero, and set the distance to this starting node to be zero.
        // The distnace from the start to the start is zero obviously.
        cells.push({ 0, map.GetStartCellPoint() });
        this->gValue[map.GetStartCellPoint().I()][map.GetStartCellPoint().J()] = 0;
    }

    static int hValue(CellPoint p1, CellPoint p2) {
        // In this case, Manhattan distance as a Heuristic function will work better, as we only look at the 4 adjacent neighbors instead of 8.
        // If we would look at all the 8 neighbors, then the Euclidean distance would work better.

        // Euclidean Distance.
        // return sqrt(pow(p1.I() - p2.I(), 2) + pow(p1.J() - p2.J(), 2));

        // Manhattan Distance.
        return abs(p1.I() - p2.I()) + abs(p1.J() - p2.J());
    }

    void AStar::Step() {
        if (!cells.empty()) {
            CellPoint current_cell = cells.top().second;
            cells.pop();

            if (current_cell == this->map.GetEndCellPoint()) {
                // If we have found the end cell, set that we are done.
                this->finished = true;
                return;
            }

            if (this->states[current_cell.I()][current_cell.J()] == CellState::VISITED) {
                // If we have visited this cell, skip the current iteration of the algorithm.
                return;
            }

            // Mark that we visited this cell.
            states[current_cell.I()][current_cell.J()] = CellState::VISITED;

            if (map.GetCell(current_cell.I(), current_cell.J()).GetType() == Cell::CellType::EMPTY) {
                // If the current cell is empty cell, set its fill color to be blue to indicate that it has been processed.
                map.GetCell(current_cell.I(), current_cell.J()).SetFillColor(BLUE);
            }

            while (true) {
                // Go through all the neighbors of the current cell.
                CellPoint neighbor = current_cell.GetNextNeighbor();

                if (!neighbor.IsValid()) {
                    // If the current cell doesn't have any neighbors left, quit the loop.
                    break;
                }

                Cell& neighbor_cell = this->map.GetCell(neighbor.I(), neighbor.J());
                if (neighbor_cell.GetType() != Cell::CellType::WALL && states[neighbor.I()][neighbor.J()] != CellState::VISITED) {
                    if (gValue[neighbor.I()][neighbor.J()] > gValue[current_cell.I()][current_cell.J()] + 1) {
                        // If the neighbor we found isn't a wall, and if it is unvisited, and if we can get to the neighbor through the current cell with a shorter distance from the starting cell.
                        // Then store that new distance, and store the current cell as the previous cell of the neighbor. In context of A* the distance is the gValue.
                        gValue[neighbor.I()][neighbor.J()] = gValue[current_cell.I()][current_cell.J()] + 1;
                        trace[neighbor.I()][neighbor.J()] = current_cell;

                        // In case the neighboring cell is empty, color it yellow to indicate that it will be processed.
                        states[neighbor.I()][neighbor.J()] = CellState::TO_VISIT;
                        if (neighbor_cell.GetType() == Cell::CellType::EMPTY) {
                            neighbor_cell.SetFillColor(YELLOW);
                        }

                        // Push the neighboring cell to the priority queue. The main difference between Dijkstra's algorithm and A* is how the priority is calculated.
                        // It is calculated as f(n) = g(n) + h(n). Where g(n) is really just distance, and h(n) is the Heuristic value, n parameter is the node.
                        cells.push({ gValue[neighbor.I()][neighbor.J()] + hValue(neighbor, this->map.GetEndCellPoint()), neighbor });
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
