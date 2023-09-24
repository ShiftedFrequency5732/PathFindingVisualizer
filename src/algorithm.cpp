#include "../include/algorithm.hpp"

Algorithm::Algorithm(Grid* grid) {
    if (grid) {
        this->grid = grid;

        this->visited = new CellState*[this->grid->getSize()];
        this->trace = new Point*[this->grid->getSize()];

        for (int i = 0; i < this->grid->getSize(); ++i) {
            this->visited[i] = new CellState[this->grid->getSize()];
            this->trace[i] = new Point[this->grid->getSize()];            

            for (int j = 0; j < this->grid->getSize(); ++j) {
                this->visited[i][j] = CellState::UNVISITED;
                this->trace[i][j] = Point(-1, -1);
            }
        }
    }

    this->finished = false;
}

bool Algorithm::IsDone() {
    return this->finished;
}

void Algorithm::GetPath() {
    Point invalid(-1, -1);

    Point current = this->grid->GetEndCell();
    while (this->trace[current.getI()][current.getJ()] != invalid) {
        current = this->trace[current.getI()][current.getJ()];
        if (current != this->grid->GetStartCell()) {
            this->grid->GetCell(current.getI(), current.getJ()).SetFillColor(ORANGE);
        }
    }

    this->finished = true;
}

void Algorithm::ResetGrid() {
    for(int i = 0; i < this->grid->getSize(); ++i) {
        for(int j = 0; j < this->grid->getSize(); ++j) {
            if(this->visited[i][j] != CellState::UNVISITED) {
                this->grid->GetCell(i, j).SetType(Cell::CellType::EMPTY);
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