#include "../include/grid.hpp"

#include <algorithm>
#include <cmath>

Grid::Grid(int grid_size) {
    // Remember the grid size.
    this->grid_size = grid_size;

    // Allocate the matrix of cells.
    this->matrix = new Cell*[grid_size];
    for (int i = 0; i < grid_size; ++i) {
        this->matrix[i] = new Cell[grid_size];
    }

    // At start we do not have any start and end cells.
    this->start_cell = Point(-1, -1);
    this->end_cell = Point(-1, -1);
}

void Grid::SetMargin(int margin) {
    this->margin = margin;
}

void Grid::SetCellSize(int cell_width, int cell_height) {
    this->cell_width = cell_width;
    this->cell_height = cell_height;
}

void Grid::SetWindowSize(int window_width, int window_height) {
    this->window_width = window_width;
    this->window_height = window_height;
}

void Grid::Draw() {
    // Draw the matrix with margins between the cells.
    for (int i = 0; i < this->grid_size; ++i) {
        for (int j = 0; j < this->grid_size; ++j) {
            DrawRectangle(j * this->cell_width + this->margin, i * this->cell_height + this->margin, this->cell_width - this->margin, this->cell_height - this->margin, matrix[i][j].GetFillColor());
        }
    }
}

void Grid::HandleMouseEvents() {
    this->MousePickStartOrEndCell();
    this->MouseDrawWallOrEmptyCells();
}

void Grid::MousePickStartOrEndCell() {
    if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_E)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 curr = { (float) GetMouseX(), (float) GetMouseY() };

        // Map the mouse position to the cell of the matrix.
        int new_i = curr.y / cell_height;
        int new_j = curr.x / cell_width;

        if (matrix[new_i][new_j].GetType() == Cell::CellType::EMPTY) {
            // If the user is holding S, the cell we will work with is start, otherwise he is holding E, then we will work with the end cell.
            Cell::CellType type = IsKeyDown(KEY_S) ? Cell::CellType::START : Cell::CellType::END;
            Point& ref_cell = IsKeyDown(KEY_S) ? start_cell : end_cell;

            if (ref_cell != Point(-1, -1)) {
                // In case we set the start or the end cell in the past remove it. We want to have only one start and end cell.
                matrix[ref_cell.getI()][ref_cell.getJ()].SetType(Cell::CellType::EMPTY);
            }

            // Remember the new position of the cell, and set its type in the matrix.
            ref_cell = Point(new_i, new_j);
            matrix[new_i][new_j].SetType(type);
        }
    }
}

static bool in_bounds(Vector2 pos, int x_max, int y_max) {
    return (pos.x >= 0 && pos.x <= x_max && pos.y >= 0 && pos.y <= y_max);
}

void Grid::MouseDrawWallOrEmptyCells() {
    if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_N)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        // If the user is holding W, we will place walls on the empty cells, otherwise we will place empty cells on the wall cells.
        Cell::CellType type = IsKeyDown(KEY_W) ? Cell::CellType::WALL : Cell::CellType::EMPTY;
        Cell::CellType opposite_type = (type == Cell::CellType::WALL) ? Cell::CellType::EMPTY : Cell::CellType::WALL;

        // Remember the previous mouse position as well as the current one. Position on one frame can be at (0, 0), and on the next frame at (1000, 1000), due to the target FPS.
        // We want to fill all the cells in between these two positions, so that we get the continuous line.
        this->mouse_prev = mouse_curr;
        this->mouse_curr = { (float)GetMouseX(), (float)GetMouseY() };

        if (in_bounds(mouse_prev, window_width, window_height) && in_bounds(mouse_curr, window_width, window_height)) {
            // Calculate the slope of the line between the previous and current mouse position.
            float x_distance = mouse_curr.x - mouse_prev.x;
            float y_distance = mouse_curr.y - mouse_prev.y;
            float slope = y_distance / x_distance;

            if (std::isnan(slope)) {
                // If the slope is NaN, that means we divided zero with zero, the previous and current mouse positions are equal.
                int new_i = mouse_curr.y / cell_height, new_j = mouse_curr.x / cell_width;
                if (matrix[new_i][new_j].GetType() == opposite_type) {
                    matrix[new_i][new_j].SetType(type);
                }
            }
            else if (abs(x_distance) > abs(y_distance)) {
                int x_min = std::min(mouse_prev.x, mouse_curr.x); 
                int x_max = std::max(mouse_prev.x, mouse_curr.x);

                // If slope is in range [-1, 1], we will use the y = slope * (x - x0) + y0, to find the y.
                for (int x = x_min; x <= x_max; ++x) {
                    int y = slope * (x - mouse_prev.x) + mouse_prev.y;
                    int new_i = y / cell_height, new_j = x / cell_width;
                    if (matrix[new_i][new_j].GetType() == opposite_type) {
                        matrix[new_i][new_j].SetType(type);
                    }
                }
            }
            else {
                int y_min = std::min(mouse_prev.y, mouse_curr.y);
                int y_max = std::max(mouse_prev.y, mouse_curr.y);

                // If the slope is not in the range [-1, 1], we will use x = (y - y0) / slope + x0, to find the x.
                for (int y = y_min; y <= y_max; ++y) {
                    int x = (y - mouse_prev.y) / slope + mouse_prev.x;
                    int new_i = y / cell_height, new_j = x / cell_width;
                    if (matrix[new_i][new_j].GetType() == opposite_type) {
                        matrix[new_i][new_j].SetType(type);
                    }
                }
            }
        }
    }
    else {
        // If the user didn't do anything, reset the previous and current mouse positions.
        this->mouse_prev = { -1, -1 };
        this->mouse_curr = { -1, -1 };
    }
}

Grid::~Grid() {
    // Deallocate the matrix.
    for (int i = 0; i < this->grid_size; ++i) {
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
}
