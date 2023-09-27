#include "../include/algorithm.hpp"

namespace Algorithms {
    GraphSearchAlgorithm::GraphSearchAlgorithm(Grid* map) {
        this->map = map;

        // Initialize the trace matrix, invalid CellPoints will indicate whether there is a previous cell point to visit or not.
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                this->trace[i][j] = CellPoint(-1, -1);
            }
        }

        // At the start, we didn't run the algorithm obviously, so it is not finished.
        this->finished = false;
    }

    bool GraphSearchAlgorithm::IsDone() {
        return this->finished;
    }

    void GraphSearchAlgorithm::GetPath() {
        if (this->map) {
            CellPoint curr = this->map->GetEndCellPoint();

            while (this->trace[curr.I()][curr.J()].IsValid()) {
                curr = this->trace[curr.I()][curr.J()];
                if (curr != this->map->GetStartCellPoint()) {
                    // Get the previous node of the current end node to visit in order to reach the current end node, color it orange if it isn't the start cell.
                    this->map->GetCell(curr.I(), curr.J()).SetFillColor(ORANGE);
                }
            }
        }
    }

    void GraphSearchAlgorithm::Reset() {
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (this->visited[i][j] != CellState::UNVISITED) {
                    Cell& curr = this->map->GetCell(i, j);
                    if (curr.GetType() == Cell::CellType::EMPTY) {
                        // If we found a cell that we visited in the past, reset its color through type.
                        curr.SetType(Cell::CellType::EMPTY);
                    }
                }

                // Reset the visited and trace matrix.
                this->visited[i][j] = CellState::UNVISITED;
                trace[i][j] = CellPoint(-1, -1);
            }
        }

        // Preapre the algorithm for the future run.
        this->Prepare();
        this->finished = false;
    }
}

