#include "../include/algorithm.hpp"

Algorithm::Algorithm(Grid* grid) {
    if (grid) {
        this->grid = grid;

        this->visited = new CellState*[this->grid->getSize()];
        this->trace = new CellPoint*[this->grid->getSize()];

        for (int i = 0; i < this->grid->getSize(); ++i) {
            this->visited[i] = new CellState[this->grid->getSize()];
            this->trace[i] = new CellPoint[this->grid->getSize()];            

            for (int j = 0; j < this->grid->getSize(); ++j) {
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
    CellPoint invalid(-1, -1);

    CellPoint curr = this->grid->GetEndCellPoint();
    while (this->trace[curr.GetI()][curr.GetJ()] != invalid) {
        curr = this->trace[curr.GetI()][curr.GetJ()];
        if (curr != this->grid->GetStartCellPoint()) {
            this->grid->GetCell(curr.GetI(), curr.GetJ()).SetFillColor(ORANGE);
        }
    }

    this->finished = true;
}

void Algorithm::ResetGrid() {
    for (int i = 0; i < this->grid->getSize(); ++i) {
        for (int j = 0; j < this->grid->getSize(); ++j) {
            if (this->visited[i][j] != CellState::UNVISITED) {
                Cell curr = this->grid->GetCell(i, j);
                if (curr.GetType() == Cell::CellType::EMPTY) {
                    curr.SetType(Cell::CellType::EMPTY);
                }
                this->visited[i][j] = CellState::UNVISITED;
            }
        }
    }
}

Algorithm::~Algorithm() {
    for (int i = 0; i < this->grid->getSize(); ++i) {
        delete[] this->visited[i];
        delete[] this->trace[i];
    }

    delete[] this->visited;
    delete[] this->trace;
}