#include "../include/algorithm.hpp"
#include <iostream>

Algorithm::Algorithm(Grid* grid) {
    if (grid) {
        this->grid = grid;
        this->grid_size = this->grid->GetSize();

        this->visited = new CellState*[this->grid_size];
        this->trace = new CellPoint*[this->grid_size];

        for (int i = 0; i < this->grid_size; ++i) {
            this->visited[i] = new CellState[this->grid_size];
            this->trace[i] = new CellPoint[this->grid_size];            

            for (int j = 0; j < this->grid_size; ++j) {
                this->visited[i][j] = CellState::UNVISITED;
                this->trace[i][j] = CellPoint(-1, -1);
            }
        }
    }

    this->finished = false;
}

bool Algorithm::IsDone() {
    return this->finished;
}

void Algorithm::GetPath() {
    CellPoint curr = this->grid->GetEndCellPoint();
    while (this->trace[curr.I()][curr.J()].IsValid()) {
        curr = this->trace[curr.I()][curr.J()];
        if (curr != this->grid->GetStartCellPoint()) {
            this->grid->GetCell(curr.I(), curr.J()).SetFillColor(ORANGE);
        }
    }
    this->finished = true;
}

void Algorithm::Reset() {
    for (int i = 0; i < this->grid_size; ++i) {
        for (int j = 0; j < this->grid_size; ++j) {
            if (this->visited[i][j] != CellState::UNVISITED) {
                Cell& curr = this->grid->GetCell(i, j);
                if (curr.GetType() == Cell::CellType::EMPTY) {
                    curr.SetType(Cell::CellType::EMPTY);
                }
                this->visited[i][j] = CellState::UNVISITED;
                trace[i][j] = CellPoint(-1, -1);
            }
        }
    }
    this->Prepare();
}

Algorithm::~Algorithm() {
    for (int i = 0; i < this->grid->GetSize(); ++i) {
        delete[] this->visited[i];
        delete[] this->trace[i];
    }

    delete[] this->visited;
    delete[] this->trace;
}